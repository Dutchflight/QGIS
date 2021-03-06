# -*- coding: utf-8 -*-

"""
***************************************************************************
    EditScriptAction.py
    ---------------------
    Date                 : August 2012
    Copyright            : (C) 2012 by Victor Olaya
    Email                : volayaf at gmail dot com
***************************************************************************
*                                                                         *
*   This program is free software; you can redistribute it and/or modify  *
*   it under the terms of the GNU General Public License as published by  *
*   the Free Software Foundation; either version 2 of the License, or     *
*   (at your option) any later version.                                   *
*                                                                         *
***************************************************************************
"""

__author__ = 'Victor Olaya'
__date__ = 'April 2014'
__copyright__ = '(C) 201, Victor Olaya'

# This will get replaced with a git SHA1 when you do a git archive

__revision__ = '$Format:%H$'

import os

from qgis.PyQt.QtWidgets import QFileDialog, QMessageBox
from qgis.PyQt.QtCore import QFileInfo

from qgis.core import QgsApplication, QgsSettings

from processing.script.ScriptAlgorithm import ScriptAlgorithm
from processing.gui.ToolboxAction import ToolboxAction
from processing.script.WrongScriptException import WrongScriptException
from processing.script.ScriptUtils import ScriptUtils

pluginPath = os.path.split(os.path.dirname(__file__))[0]


class AddScriptFromFileAction(ToolboxAction):

    def __init__(self):
        self.name, self.i18n_name = self.trAction('Add script from file')
        self.group, self.i18n_group = self.trAction('Tools')

    def getIcon(self):
        return QgsApplication.getThemeIcon("/processingScript.svg")

    def execute(self):
        settings = QgsSettings()
        lastDir = settings.value('Processing/lastScriptsDir', '')
        filenames, selected_filter = QFileDialog.getOpenFileNames(self.toolbox,
                                                                  self.tr('Script files', 'AddScriptFromFileAction'), lastDir,
                                                                  self.tr('Script files (*.py *.PY)', 'AddScriptFromFileAction'))
        if filenames:
            validAlgs = 0
            wrongAlgs = []
            for filename in filenames:
                try:
                    settings.setValue('Processing/lastScriptsDir',
                                      QFileInfo(filename).absoluteDir().absolutePath())
                    script = ScriptAlgorithm(filename)
                    destFilename = os.path.join(ScriptUtils.scriptsFolders()[0], os.path.basename(filename))
                    with open(destFilename, 'w') as f:
                        f.write(script.script)
                    validAlgs += 1
                except WrongScriptException:
                    wrongAlgs.append(os.path.basename(filename))
            if validAlgs:
                QgsApplication.processingRegistry().providerById('script').refreshAlgorithms()
            if wrongAlgs:
                QMessageBox.warning(self.toolbox,
                                    self.tr('Error reading scripts', 'AddScriptFromFileAction'),
                                    self.tr('The following files do not contain a valid script:\n-', 'AddScriptFromFileAction') +
                                    "\n-".join(wrongAlgs))
