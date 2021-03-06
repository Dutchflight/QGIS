/***************************************************************************
     test_template.cpp
     --------------------------------------
    Date                 : Sun Sep 16 12:22:23 AKDT 2007
    Copyright            : (C) 2007 by Gary E. Sherman
    Email                : sherman at mrcc dot com
 ***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
#include "qgstest.h"
#include <QObject>
#include <QString>
#include <QStringList>
#include <QApplication>
#include <QFileInfo>
#include <QDir>
#include <QDesktopServices>

//qgis includes...
#include <qgsgeometry.h>
#include <qgsmaplayer.h>
#include <qgsvectordataprovider.h>
#include <qgsvectorlayer.h>
#include "qgsfeatureiterator.h"
#include <qgsapplication.h>
#include <qgsproviderregistry.h>
#include <qgsproject.h>
#include <qgssymbol.h>
#include <qgssinglesymbolrenderer.h>
//qgis test includes
#include "qgsrenderchecker.h"

class TestSignalReceiver : public QObject
{
    Q_OBJECT

  public:
    TestSignalReceiver()
      : QObject( 0 )
      , rendererChanged( false )
      , featureBlendMode( QPainter::CompositionMode( 0 ) )
      , transparency( 0 )
    {}
    bool rendererChanged;
    QPainter::CompositionMode featureBlendMode;
    int transparency;
  public slots:
    void onRendererChanged()
    {
      rendererChanged = true;
    }
    void onFeatureBlendModeChanged( const QPainter::CompositionMode blendMode )
    {
      featureBlendMode = blendMode;
    }
    void onLayerTransparencyChanged( int layerTransparency )
    {
      transparency = layerTransparency;
    }
};

/** \ingroup UnitTests
 * This is a unit test for the vector layer class.
 */
class TestQgsVectorLayer : public QObject
{
    Q_OBJECT
  public:
    TestQgsVectorLayer()
      : mTestHasError( false )
      , mpPointsLayer( 0 )
      , mpLinesLayer( 0 )
      , mpPolysLayer( 0 )
      , mpNonSpatialLayer( 0 )
    {}

  private:
    bool mTestHasError;
    QgsMapLayer *mpPointsLayer = nullptr;
    QgsMapLayer *mpLinesLayer = nullptr;
    QgsMapLayer *mpPolysLayer = nullptr;
    QgsVectorLayer *mpNonSpatialLayer = nullptr;
    QString mTestDataDir;
    QString mReport;

  private slots:

    void initTestCase(); // will be called before the first testfunction is executed.
    void cleanupTestCase(); // will be called after the last testfunction was executed.
    void init() {} // will be called before each testfunction is executed.
    void cleanup() {} // will be called after every testfunction.

    void QgsVectorLayerNonSpatialIterator();
    void QgsVectorLayerGetValues();
    void QgsVectorLayersetRenderer();
    void QgsVectorLayersetFeatureBlendMode();
    void QgsVectorLayersetLayerTransparency();
    void uniqueValues();
    void minimumValue();
    void maximumValue();
    void isSpatial();
    void testAddTopologicalPoints();
};

void TestQgsVectorLayer::initTestCase()
{
  mTestHasError = false;
  QgsApplication::init();
  QgsApplication::initQgis();
  QgsApplication::showSettings();

  //create some objects that will be used in all tests...

  //
  //create a non spatial layer that will be used in all tests...
  //
  QString myDataDir( TEST_DATA_DIR ); //defined in CmakeLists.txt
  mTestDataDir = myDataDir + '/';
  QString myDbfFileName = mTestDataDir + "nonspatial.dbf";
  QFileInfo myDbfFileInfo( myDbfFileName );
  mpNonSpatialLayer = new QgsVectorLayer( myDbfFileInfo.filePath(),
                                          myDbfFileInfo.completeBaseName(), QStringLiteral( "ogr" ) );
  // Register the layer with the registry
  QgsProject::instance()->addMapLayers(
    QList<QgsMapLayer *>() << mpNonSpatialLayer );
  //
  //create a point layer that will be used in all tests...
  //
  QString myPointsFileName = mTestDataDir + "points.shp";
  QFileInfo myPointFileInfo( myPointsFileName );
  mpPointsLayer = new QgsVectorLayer( myPointFileInfo.filePath(),
                                      myPointFileInfo.completeBaseName(), QStringLiteral( "ogr" ) );
  // Register the layer with the registry
  QgsProject::instance()->addMapLayers(
    QList<QgsMapLayer *>() << mpPointsLayer );

  //
  //create a poly layer that will be used in all tests...
  //
  QString myPolysFileName = mTestDataDir + "polys.shp";
  QFileInfo myPolyFileInfo( myPolysFileName );
  mpPolysLayer = new QgsVectorLayer( myPolyFileInfo.filePath(),
                                     myPolyFileInfo.completeBaseName(), QStringLiteral( "ogr" ) );
  // Register the layer with the registry
  QgsProject::instance()->addMapLayers(
    QList<QgsMapLayer *>() << mpPolysLayer );


  //
  // Create a line layer that will be used in all tests...
  //
  QString myLinesFileName = mTestDataDir + "lines.shp";
  QFileInfo myLineFileInfo( myLinesFileName );
  mpLinesLayer = new QgsVectorLayer( myLineFileInfo.filePath(),
                                     myLineFileInfo.completeBaseName(), QStringLiteral( "ogr" ) );
  // Register the layer with the registry
  QgsProject::instance()->addMapLayers(
    QList<QgsMapLayer *>() << mpLinesLayer );

  mReport += QLatin1String( "<h1>Vector Renderer Tests</h1>\n" );
}

void TestQgsVectorLayer::cleanupTestCase()
{
  QString myReportFile = QDir::tempPath() + "/qgistest.html";
  QFile myFile( myReportFile );
  if ( myFile.open( QIODevice::WriteOnly | QIODevice::Append ) )
  {
    QTextStream myQTextStream( &myFile );
    myQTextStream << mReport;
    myFile.close();
    //QDesktopServices::openUrl( "file:///" + myReportFile );
  }
  QgsApplication::exitQgis();
}

void TestQgsVectorLayer::QgsVectorLayerNonSpatialIterator()
{
  QgsFeature f;
  QgsAttributeList myList;
  myList << 0 << 1 << 2 << 3;
  int myCount = 0;
  QgsFeatureIterator fit = mpNonSpatialLayer->getFeatures( QgsFeatureRequest().setSubsetOfAttributes( myList ) );
  while ( fit.nextFeature( f ) )
  {
    qDebug( "Getting non-spatial feature from layer" );
    myCount++;
  }
  QVERIFY( myCount == 3 );
}

void TestQgsVectorLayer::QgsVectorLayerGetValues()
{
  QgsVectorLayer *layer = new QgsVectorLayer( QStringLiteral( "Point?field=col1:real" ), QStringLiteral( "layer" ), QStringLiteral( "memory" ) );
  QVERIFY( layer->isValid() );
  QgsFeature f1( layer->dataProvider()->fields(), 1 );
  f1.setAttribute( QStringLiteral( "col1" ), 1 );
  QgsFeature f2( layer->dataProvider()->fields(), 2 );
  f2.setAttribute( QStringLiteral( "col1" ), 2 );
  QgsFeature f3( layer->dataProvider()->fields(), 3 );
  f3.setAttribute( QStringLiteral( "col1" ), 3 );
  QgsFeature f4( layer->dataProvider()->fields(), 4 );
  f4.setAttribute( QStringLiteral( "col1" ), QVariant() );
  layer->dataProvider()->addFeatures( QgsFeatureList() << f1 << f2 << f3 << f4 );

  //make a selection
  QgsFeatureIds ids;
  ids << f2.id() << f3.id();
  layer->selectByIds( ids );

  bool ok;
  QList<QVariant> varList = layer->getValues( QStringLiteral( "col1" ), ok );
  QVERIFY( ok );
  QCOMPARE( varList.length(), 4 );
  QCOMPARE( varList.at( 0 ), QVariant( 1 ) );
  QCOMPARE( varList.at( 1 ), QVariant( 2 ) );
  QCOMPARE( varList.at( 2 ), QVariant( 3 ) );
  QCOMPARE( varList.at( 3 ), QVariant() );

  //check with selected features
  varList = layer->getValues( QStringLiteral( "col1" ), ok, true );
  QVERIFY( ok );
  QCOMPARE( varList.length(), 2 );
  QCOMPARE( varList.at( 0 ), QVariant( 2 ) );
  QCOMPARE( varList.at( 1 ), QVariant( 3 ) );

  int nulls = 0;
  QList<double> doubleList = layer->getDoubleValues( QStringLiteral( "col1" ), ok, false, &nulls );
  QVERIFY( ok );
  QCOMPARE( doubleList.length(), 3 );
  QCOMPARE( doubleList.at( 0 ), 1.0 );
  QCOMPARE( doubleList.at( 1 ), 2.0 );
  QCOMPARE( doubleList.at( 2 ), 3.0 );
  QCOMPARE( nulls, 1 );

  //check with selected features
  doubleList = layer->getDoubleValues( QStringLiteral( "col1" ), ok, true, &nulls );
  QVERIFY( ok );
  QCOMPARE( doubleList.length(), 2 );
  QCOMPARE( doubleList.at( 0 ), 2.0 );
  QCOMPARE( doubleList.at( 1 ), 3.0 );
  QCOMPARE( nulls, 0 );

  QList<QVariant> expVarList = layer->getValues( QStringLiteral( "tostring(col1) || ' '" ), ok );
  QVERIFY( ok );
  QCOMPARE( expVarList.length(), 4 );
  QCOMPARE( expVarList.at( 0 ).toString(), QString( "1 " ) );
  QCOMPARE( expVarList.at( 1 ).toString(), QString( "2 " ) );
  QCOMPARE( expVarList.at( 2 ).toString(), QString( "3 " ) );
  QCOMPARE( expVarList.at( 3 ), QVariant() );

  QList<double> expDoubleList = layer->getDoubleValues( QStringLiteral( "col1 * 2" ), ok, false, &nulls );
  QVERIFY( ok );
  QCOMPARE( expDoubleList.length(), 3 );
  QCOMPARE( expDoubleList.at( 0 ), 2.0 );
  QCOMPARE( expDoubleList.at( 1 ), 4.0 );
  QCOMPARE( expDoubleList.at( 2 ), 6.0 );
  QCOMPARE( nulls, 1 );

  delete layer;
}

void TestQgsVectorLayer::QgsVectorLayersetRenderer()
{
  QgsVectorLayer *vLayer = static_cast< QgsVectorLayer * >( mpPointsLayer );
  TestSignalReceiver receiver;
  QObject::connect( vLayer, SIGNAL( rendererChanged() ),
                    &receiver, SLOT( onRendererChanged() ) );
  QgsSingleSymbolRenderer *symbolRenderer = new QgsSingleSymbolRenderer( QgsSymbol::defaultSymbol( QgsWkbTypes::PointGeometry ) );

  QCOMPARE( receiver.rendererChanged, false );
  vLayer->setRenderer( symbolRenderer );
  QCOMPARE( receiver.rendererChanged, true );
  QCOMPARE( vLayer->renderer(), symbolRenderer );
}

void TestQgsVectorLayer::QgsVectorLayersetFeatureBlendMode()
{
  QgsVectorLayer *vLayer = static_cast< QgsVectorLayer * >( mpPointsLayer );
  TestSignalReceiver receiver;
  QObject::connect( vLayer, SIGNAL( featureBlendModeChanged( const QPainter::CompositionMode ) ),
                    &receiver, SLOT( onFeatureBlendModeChanged( const QPainter::CompositionMode ) ) );

  QCOMPARE( int( receiver.featureBlendMode ), 0 );
  vLayer->setFeatureBlendMode( QPainter::CompositionMode_Screen );
  QCOMPARE( receiver.featureBlendMode, QPainter::CompositionMode_Screen );
  QCOMPARE( vLayer->featureBlendMode(), QPainter::CompositionMode_Screen );
}

void TestQgsVectorLayer::QgsVectorLayersetLayerTransparency()
{
  QgsVectorLayer *vLayer = static_cast< QgsVectorLayer * >( mpPointsLayer );
  TestSignalReceiver receiver;
  QObject::connect( vLayer, SIGNAL( layerTransparencyChanged( int ) ),
                    &receiver, SLOT( onLayerTransparencyChanged( int ) ) );

  QCOMPARE( receiver.transparency, 0 );
  vLayer->setLayerTransparency( 50 );
  QCOMPARE( receiver.transparency, 50 );
  QCOMPARE( vLayer->layerTransparency(), 50 );
}

void TestQgsVectorLayer::uniqueValues()
{
  QgsVectorLayer *vLayer = static_cast< QgsVectorLayer * >( mpPointsLayer );

  //test with invalid field
  QList<QVariant> values;
  vLayer->uniqueValues( 1000, values );
  QCOMPARE( values.length(), 0 );
}

void TestQgsVectorLayer::minimumValue()
{
  QgsVectorLayer *vLayer = static_cast< QgsVectorLayer * >( mpPointsLayer );

  //test with invalid field
  QCOMPARE( vLayer->minimumValue( 1000 ), QVariant() );
}

void TestQgsVectorLayer::maximumValue()
{
  QgsVectorLayer *vLayer = static_cast< QgsVectorLayer * >( mpPointsLayer );

  //test with invalid field
  QCOMPARE( vLayer->maximumValue( 1000 ), QVariant() );
}

void TestQgsVectorLayer::isSpatial()
{
  QVERIFY( mpPointsLayer->isSpatial() );
  QVERIFY( mpPolysLayer->isSpatial() );
  QVERIFY( mpLinesLayer->isSpatial() );
  QVERIFY( !mpNonSpatialLayer->isSpatial() );
}

void TestQgsVectorLayer::testAddTopologicalPoints()
{
  // create a simple linestring layer

  QgsVectorLayer *layerLine = new QgsVectorLayer( "LineString?crs=EPSG:27700", "layer line", "memory" );
  QVERIFY( layerLine->isValid() );

  QgsPolyline line1;
  line1 << QgsPoint( 2, 1 ) << QgsPoint( 1, 1 ) << QgsPoint( 1, 3 );
  QgsFeature lineF1;
  lineF1.setGeometry( QgsGeometry::fromPolyline( line1 ) );

  layerLine->startEditing();
  layerLine->addFeature( lineF1 );
  QgsFeatureId fidLineF1 = lineF1.id();
  QCOMPARE( layerLine->featureCount(), ( long )1 );

  QCOMPARE( layerLine->undoStack()->index(), 1 );

  // outside of the linestring - nothing should happen
  layerLine->addTopologicalPoints( QgsPoint( 2, 2 ) );

  QCOMPARE( layerLine->undoStack()->index(), 1 );
  QCOMPARE( layerLine->getFeature( fidLineF1 ).geometry(), QgsGeometry::fromWkt( "LINESTRING(2 1, 1 1, 1 3)" ) );

  // add point at an existing vertex
  layerLine->addTopologicalPoints( QgsPoint( 1, 1 ) );

  QCOMPARE( layerLine->undoStack()->index(), 1 );
  QCOMPARE( layerLine->getFeature( fidLineF1 ).geometry(), QgsGeometry::fromWkt( "LINESTRING(2 1, 1 1, 1 3)" ) );

  // add point on segment of linestring
  layerLine->addTopologicalPoints( QgsPoint( 1, 2 ) );

  QCOMPARE( layerLine->undoStack()->index(), 2 );
  QCOMPARE( layerLine->getFeature( fidLineF1 ).geometry(), QgsGeometry::fromWkt( "LINESTRING(2 1, 1 1, 1 2, 1 3)" ) );

  delete layerLine;
}

QGSTEST_MAIN( TestQgsVectorLayer )
#include "testqgsvectorlayer.moc"
