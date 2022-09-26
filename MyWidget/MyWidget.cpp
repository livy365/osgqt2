#include "MyWidget.h"
#include "ui_mywidget.h"
#include"nji.h"
#include <osgViewer/Viewer>
#include <osg/Node>
#include <osgDB/ReadFile>
#include <osgGA/TrackballManipulator>
#include <QResizeEvent>
#include <osg/StateSet>
#include <osgModeling/BoolOperator>
#include <osgUtil/TriStripVisitor>
#include <osg/ShapeDrawable>
#include <osgModeling/Extrude>
#include <osgModeling/Lathe>
#include <osgModeling/Nurbs>


MyWidget::MyWidget(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MyWidget)
{
    ui->setupUi(this);
    _pOsgQOpenGLWidget = new osgQOpenGLWidget(ui->centralWidget);
   // _pOsgQOpenGLWidget->setGeometry(ui->centralWidget->geometry());
   
	
		

    connect(_pOsgQOpenGLWidget, SIGNAL(initialized()), this, SLOT(initWindow()));
}

MyWidget::~MyWidget()
{
    delete ui;
    if (_pOsgQOpenGLWidget != NULL)
        delete _pOsgQOpenGLWidget;
}

void MyWidget::resizeEvent(QResizeEvent* ev)
{

  //  ui->centralWidget->setGeometry(0, 0, ev->size().width(), ev->size().height());
    _pOsgQOpenGLWidget->setGeometry(0, 0, ev->size().width(), ev->size().height());
    
}

osg::ref_ptr<osg::Geometry> createFirstOperator()
{
#if 0
    osg::ref_ptr<osgModeling::Curve> profile = new osgModeling::Curve;
    profile->addPathPoint(osg::Vec3(-0.2f, 0.0f, 0.0f));
    profile->addPathPoint(osg::Vec3(-0.2f, 0.0f, 2.0f));
    osg::ref_ptr<osgModeling::Lathe> geom = new osgModeling::Lathe;
    geom->setGenerateParts(osgModeling::Model::ALL_PARTS);
    geom->setLatheSegments(16);
    geom->setLatheOrigin(osg::Vec3(0.0f, 0.0f, -0.8f));
    geom->setLatheAxis(osg::Vec3(0.0f, 0.0f, 1.0f));
    geom->setProfile(profile.get());
    geom->update();
#else
    double cp[5][3] = {
        {1.0f,0.0f,1.0f}, {-1.0f,0.0f,1.0f}, {-1.0f,0.0f,-1.0f},
        {1.0f,0.0f,-1.0f}, {1.0f,0.0f,1.0f} };
    osg::ref_ptr<osgModeling::Curve> profile = new osgModeling::Curve;
    profile->setPath(15, &cp[0][0]);
    osg::ref_ptr<osgModeling::Extrude> geom = new osgModeling::Extrude;
    geom->setGenerateParts(osgModeling::Model::ALL_PARTS);
    geom->setExtrudeDirection(osg::Vec3(0.0f, 1.0f, 0.0f));
    geom->setExtrudeLength(1.0f);
    geom->setProfile(profile.get());
    geom->update();
#endif
    return geom.get();
}

osg::ref_ptr<osg::Geometry> createSecondOperator()
{
#if 1
    double r = 0.5f;
    double knotsU[12] = { 0, 0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 4 };
    double knotsV[8] = { 0, 0, 0, 1, 1, 2, 2, 2 };
    double ctrlAndWeightPts[9][5][4] = {
        {{0,0,r,1}, { r, 0,r,1}, { r, 0,0,2}, { r, 0,-r,1}, {0,0,-r,1}},
        {{0,0,r,1}, { r,-r,r,1}, { r,-r,0,2}, { r,-r,-r,1}, {0,0,-r,1}},
        {{0,0,r,2}, { 0,-r,r,2}, { 0,-r,0,4}, { 0,-r,-r,2}, {0,0,-r,2}},
        {{0,0,r,1}, {-r,-r,r,1}, {-r,-r,0,2}, {-r,-r,-r,1}, {0,0,-r,1}},
        {{0,0,r,1}, {-r, 0,r,1}, {-r, 0,0,2}, {-r, 0,-r,1}, {0,0,-r,1}},
        {{0,0,r,1}, {-r, r,r,1}, {-r, r,0,2}, {-r, 1,-r,1}, {0,0,-r,1}},
        {{0,0,r,2}, { 0, r,r,2}, { 0, r,0,4}, { 0, r,-r,2}, {0,0,-r,2}},
        {{0,0,r,1}, { r, r,r,1}, { r, r,0,2}, { r, r,-r,1}, {0,0,-r,1}},
        {{0,0,r,1}, { r, 0,r,1}, { r, 0,0,2}, { r, 0,-r,1}, {0,0,-r,1}} };
    osg::ref_ptr<osgModeling::NurbsSurface> geom = new osgModeling::NurbsSurface(
        12, &knotsU[0], 8, &knotsV[0], 20, 4, &ctrlAndWeightPts[0][0][0], 3, 3, 16, 16);
#else
    double cp[5][3] = {
        {0.5f,1.0f,0.0f}, {-0.5f,0.0f,0.0f}, {0.5f,-1.0f,0.0f},
        {1.5f,0.0f,0.0f}, {0.5f,1.0f,0.0f} };
    osg::ref_ptr<osgModeling::Curve> profile = new osgModeling::Curve;
    profile->setPath(15, &cp[0][0]);
    osg::ref_ptr<osgModeling::Extrude> geom = new osgModeling::Extrude;
    geom->setGenerateParts(osgModeling::Model::ALL_PARTS);
    geom->setExtrudeLength(2.0f);
    geom->setProfile(profile.get());
    geom->update();
#endif
    return geom.get();
}

osg::ref_ptr<osg::Node> createBoolean()
{
    // A boolean operation requires input Model instances because it uses the BSP tree to finish the work.
    // We could generate Model objects both from Geometry instances or derived classes (e.g. Extrude, Lathe).
    osg::ref_ptr<osgModeling::Model> model1 = new osgModeling::Model(*createFirstOperator());
    osg::ref_ptr<osgModeling::Model> model2 = new osgModeling::Model(*createSecondOperator());

    // Choose boolean method: Intersection, Union or Difference.
    osg::ref_ptr<osgModeling::BoolOperator> boolOp = new osgModeling::BoolOperator;
    boolOp->setMethod(osgModeling::BoolOperator::BOOL_INTERSECTION);
    boolOp->setOperands(model1.get(), model2.get());

    // Calculate and output the result into a new geometry.
    // Be careful, it may cost long time or even crash if you input a too complex model.
    osg::ref_ptr<osg::Geometry> result = new osg::Geometry;
    boolOp->output(result.get());

    // A triangle strip generator should be used here, otherwise too many independent triangles may cause the graphics system crash. 
    osgUtil::TriStripVisitor tsv;
    tsv.stripify(*result);

    osg::ref_ptr<osg::Geode> geode = new osg::Geode;
    geode->addDrawable(result.get());
    return geode;
}


osg::ref_ptr<osg::Geometry> sph(float radius, osg::Vec3 centre)
{
	// 创建一个用于保存几何信息的对象
	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;
    osg::ref_ptr<osg::Sphere> cy1=new osg::Sphere;
    cy1->setCenter(centre);
    cy1->setRadius(radius);
    osg::ref_ptr<osg::ShapeDrawable> sd6 = new osg::ShapeDrawable(cy1);
    sd6->setColor(osg::Vec4(1, 1, 0, 0.5));
    geom = sd6;
	return geom.get();
}

osg::ref_ptr<osg::Geometry> cy(int radius, osg::Vec3 centre,float h)
{
    // 创建一个用于保存几何信息的对象
    osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;
    osg::ref_ptr<osg::Sphere> cy1 = new osg::Sphere;
    cy1->setCenter(centre);
    cy1->setRadius(radius);
    osg::ref_ptr<osg::ShapeDrawable> sd6 = new osg::ShapeDrawable(cy1);
    sd6->setColor(osg::Vec4(1, 1, 1, 0.5));
    geom = sd6;
    return geom.get();
}


osg::ref_ptr<osg::Geometry> Createboolean(osgModeling::BoolOperator::Method mMethod, osg::ref_ptr<osg::Geometry> mGeometry1, osg::ref_ptr<osg::Geometry> mGeometry2)
{
    osg::ref_ptr<osgModeling::BoolOperator> mBoolOperator = new osgModeling::BoolOperator(mMethod);
    osg::ref_ptr<osgModeling::Model> mModel1 = new osgModeling::Model(*mGeometry1);
    osg::ref_ptr<osgModeling::Model> mModel2 = new osgModeling::Model(*mGeometry2);
    mBoolOperator->setOperands(mModel1, mModel2);
    osg::ref_ptr<osg::Geometry> mGeom = new osg::Geometry;

    mBoolOperator->output(mGeom);
    // A triangle strip generator should be used here, otherwise too many independent triangles may cause the graphics system crash. llllll
    osgUtil::TriStripVisitor tsv;
    tsv.stripify(*mGeom);
    return mGeom;

}


void MyWidget::initWindow()
{
    osgViewer::Viewer* pViewer = _pOsgQOpenGLWidget->getOsgViewer();
    pViewer->setCameraManipulator(new osgGA::TrackballManipulator);

    osg::ref_ptr<osg::Group> root = new osg::Group;
    root->addChild(createBoolean().get());

	pViewer->setSceneData(root.get());
}

