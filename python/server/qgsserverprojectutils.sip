/***************************************************************************
                              qgsserverprojectutils.sip
                              -------------------------
  begin                : December 19, 2016
  copyright            : (C) 2016 by Paul Blottiere
  email                : paul dot blottiere at oslandia dot com
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

%ModuleHeaderCode
#include "qgsserverprojectutils.h"
%End

/** \ingroup server
 * The QgsServerProjectUtils namespace provides a way to retrieve specific
 * entries from a QgsProject.
 * @note added in QGIS 3.0
 */
namespace QgsServerProjectUtils
{

    /** Returns if owsService capabilities are enabled.
      * @param project the QGIS project
      * @return if owsService capabilities are enabled.
      */
    bool owsServiceCapabilities( const QgsProject &project );

    /** Returns the owsService title defined in project.
      * @param project the QGIS project
      * @return the owsService title if defined in project.
      */
    QString owsServiceTitle( const QgsProject &project );

    /** Returns the owsService abstract defined in project.
      * @param project the QGIS project
      * @return the owsService abstract if defined in project.
      */
    QString owsServiceAbstract( const QgsProject &project );

    /** Returns the owsService keywords defined in project.
      * @param project the QGIS project
      * @return the owsService keywords if defined in project.
      */
    QStringList owsServiceKeywords( const QgsProject &project );

    /** Returns the owsService online resource defined in project.
      * @param project the QGIS project
      * @return the owsService online resource if defined in project.
      */
    QString owsServiceOnlineResource( const QgsProject &project );

    /** Returns the owsService contact organization defined in project.
      * @param project the QGIS project
      * @return the owsService contact organization if defined in project.
      */
    QString owsServiceContactOrganization( const QgsProject &project );

    /** Returns the owsService contact position defined in project.
      * @param project the QGIS project
      * @return the owsService contact position if defined in project.
      */
    QString owsServiceContactPosition( const QgsProject &project );

    /** Returns the owsService contact person defined in project.
      * @param project the QGIS project
      * @return the owsService contact person if defined in project.
      */
    QString owsServiceContactPerson( const QgsProject &project );

    /** Returns the owsService contact mail defined in project.
      * @param project the QGIS project
      * @return the owsService contact mail if defined in project.
      */
    QString owsServiceContactMail( const QgsProject &project );

    /** Returns the owsService contact phone defined in project.
      * @param project the QGIS project
      * @return the owsService contact phone if defined in project.
      */
    QString owsServiceContactPhone( const QgsProject &project );

    /** Returns the owsService fees defined in project.
      * @param project the QGIS project
      * @return the owsService fees if defined in project.
      */
    QString owsServiceFees( const QgsProject &project );

    /** Returns the owsService access constraints defined in project.
      * @param project the QGIS project
      * @return the owsService access constraints if defined in project.
      */
    QString owsServiceAccessConstraints( const QgsProject &project );

    /** Returns the maximum width for WMS images defined in a QGIS project.
      * @param project the QGIS project
      * @return width if defined in project, -1 otherwise.
      */
    int wmsMaxWidth( const QgsProject &project );

    /** Returns the maximum height for WMS images defined in a QGIS project.
      * @param project the QGIS project
      * @return height if defined in project, -1 otherwise.
      */
    int wmsMaxHeight( const QgsProject &project );

    /** Returns if layer ids are used as name in WMS.
      * \param project the QGIS project
      * \returns if layer ids are used as name.
      */
    bool wmsUseLayerIds( const QgsProject &project );

    /** Returns if the info format is SIA20145.
      * \param project the QGIS project
      * \returns if the info format is SIA20145.
      */
    bool wmsInfoFormatSia2045( const QgsProject &project );

    /** Returns if Inspire is activated.
      * \param project the QGIS project
      * \returns if Inspire is activated.
      */
    bool wmsInspireActivated( const QgsProject &project );

    /** Returns the Inspire language.
      * \param project the QGIS project
      * \returns the Inspire language if defined in project.
      */
    QString wmsInspireLanguage( const QgsProject &project );

    /** Returns the Inspire metadata URL.
      * \param project the QGIS project
      * \returns the Inspire metadata URL if defined in project.
      */
    QString wmsInspireMetadataUrl( const QgsProject &project );

    /** Returns the Inspire metadata URL type.
      * \param project the QGIS project
      * \returns the Inspire metadata URL type if defined in project.
      */
    QString wmsInspireMetadataUrlType( const QgsProject &project );

    /** Returns the Inspire temporal reference.
      * \param project the QGIS project
      * \returns the Inspire temporal reference if defined in project.
      */
    QString wmsInspireTemporalReference( const QgsProject &project );

    /** Returns the Inspire metadata date.
      * \param project the QGIS project
      * \returns the Inspire metadata date if defined in project.
      */
    QString wmsInspireMetadataDate( const QgsProject &project );

    /** Returns the restricted composer list.
      * \param project the QGIS project
      * \returns the restricted composer list if defined in project.
      */
    QStringList wmsRestrictedComposers( const QgsProject &project );

    /** Returns the WMS ervice url defined in a QGIS project.
      * @param project the QGIS project
      * @return url if defined in project, an empty string otherwise.
      */
    QString wmsServiceUrl( const QgsProject &project );

    /** Returns the WMS root layer name defined in a QGIS project.
      * \param project the QGIS project
      * \returns root layer name if defined in project, an empty string otherwise.
      */
    QString wmsRootName( const QgsProject &project );

    /** Returns the restricted layer name list.
      * \param project the QGIS project
      * \returns the restricted layer name list if defined in project.
      */
    QStringList wmsRestrictedLayers( const QgsProject &project );

    /** Returns the WMS output CRS list.
      * \param project the QGIS project
      * \returns the WMS output CRS list.
      */
    QStringList wmsOutputCrsList( const QgsProject &project );

    /** Returns the WMS Extent restriction.
      * \param project the QGIS project
      * \returns the WMS Extent restriction.
      */
    QgsRectangle wmsExtent( const QgsProject &project );

    /** Returns the WFS service url defined in a QGIS project.
      * @param project the QGIS project
      * @return url if defined in project, an empty string otherwise.
      */
    QString wfsServiceUrl( const QgsProject &project );

    /** Returns the Layer ids list defined in a QGIS project as published in WFS.
      * @param project the QGIS project
      * @return the Layer ids list.
      */
    QStringList wfsLayerIds( const QgsProject &project );

    /** Returns the Layer precision defined in a QGIS project for the WFS GetFeature.
      * @param project the QGIS project
      * @param layerId the layer id in the project
      * @return the layer precision for WFS GetFeature.
      */

    int wfsLayerPrecision( const QgsProject &project, const QString &layerId );

    /** Returns the Layer ids list defined in a QGIS project as published as WFS-T with update capabilities.
      * @param project the QGIS project
      * @return the Layer ids list.
      */
    QStringList wfstUpdateLayerIds( const QgsProject &project );

    /** Returns the Layer ids list defined in a QGIS project as published as WFS-T with insert capabilities.
      * @param project the QGIS project
      * @return the Layer ids list.
       */
    QStringList wfstInsertLayerIds( const QgsProject &project );

    /** Returns the Layer ids list defined in a QGIS project as published as WFS-T with delete capabilities.
      * @param project the QGIS project
      * @return the Layer ids list.
      */
    QStringList wfstDeleteLayerIds( const QgsProject &project );

    /** Returns the WCS service url defined in a QGIS project.
      * @param project the QGIS project
      * @return url if defined in project, an empty string otherwise.
      */
    QString wcsServiceUrl( const QgsProject &project );

    /** Returns the Layer ids list defined in a QGIS project as published in WCS.
      * @param project the QGIS project
      * @return the Layer ids list.
      */
    QStringList wcsLayers( const QgsProject &project );
};
