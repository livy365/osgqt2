#include "MyWidget.h"
#include "ui_mywidget.h"
#include"nji.h"
#include <osgViewer/Viewer>
#include <osg/Node>
#include <osgDB/ReadFile>
#include <osgGA/TrackballManipulator>
#include <QResizeEvent>
#include <osg/TexGen>
#include <osg/Texture2D>
#include <osg/TexEnv>
#include <osg/StateSet>
#include <osg/Material>
#include <osgModeling/BoolOperator>
#include <osgUtil/TriStripVisitor>
#include <osg/ShapeDrawable>



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


osg::ref_ptr<osg::StateSet> createTexture2DState(osg::ref_ptr<osg::Image> image)
{
    //创建状态集对象
    osg::ref_ptr<osg::StateSet> stateset = new osg::StateSet();

    //创建二维纹理对象
    osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D();
    texture->setDataVariance(osg::Object::DYNAMIC);
    //设置贴图
    texture->setImage(image.get());

    texture->setFilter(osg::Texture::MIN_FILTER, osg::Texture::LINEAR_MIPMAP_LINEAR);
    texture->setFilter(osg::Texture::MAG_FILTER, osg::Texture::LINEAR);
    texture->setWrap(osg::Texture::WRAP_S, osg::Texture::REPEAT);
    texture->setWrap(osg::Texture::WRAP_T, osg::Texture::REPEAT);

    stateset->setTextureAttributeAndModes(0, texture.get(), osg::StateAttribute::ON);
    stateset->setMode(GL_RESCALE_NORMAL, osg::StateAttribute::ON |
        osg::StateAttribute::PROTECTED);
    stateset->setMode(GL_LIGHTING, osg::StateAttribute::OFF |
        osg::StateAttribute::PROTECTED);

    return stateset.get();
}


osg::ref_ptr<osg::Geometry> sph(int radius, osg::Vec3 centre)
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
    // A triangle strip generator should be used here, otherwise too many independent triangles may cause the graphics system crash. 
    osgUtil::TriStripVisitor tsv;
    tsv.stripify(*mGeom);
    return mGeom;

}


void MyWidget::initWindow()
{
    osgViewer::Viewer* pViewer = _pOsgQOpenGLWidget->getOsgViewer();
    pViewer->setCameraManipulator(new osgGA::TrackballManipulator);
	osg::ref_ptr<osg::Group> rpGroup = new osg::Group;
	osg::ref_ptr<osg::Geometry> one = sph(5, osg::Vec3(0, 0, 0));
	osg::ref_ptr<osg::Geometry> one1 = sph(5, osg::Vec3(0, 0, 30));
	osg::ref_ptr<osg::Geometry> one11 = Createboolean(osgModeling::BoolOperator::BOOL_UNION, one, one1);

	osg::ref_ptr<osg::Geometry> two = sph(5, osg::Vec3(20, 0, 0));
	osg::ref_ptr<osg::Geometry> two1 = sph(5, osg::Vec3(20, 0, 5));

	osg::ref_ptr<osg::Geode> geode = new osg::Geode;

	geode->addDrawable(two.get());
	geode->addDrawable(two1.get());

   // osg::ref_ptr<osg::Geode>geode = lathe_main->asGroup()->getChild(0)->asGeode();
   // osg::Geometry* geom = dynamic_cast<osg::Geometry*>(geode->getDrawable(0));
	rpGroup->addChild(one11);
	rpGroup->addChild(geode);
	
	pViewer->setSceneData(rpGroup.get());
}

