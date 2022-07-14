#include <thread>
#include "lathe.h"
#include "ui_lathe.h"
#include"sports.h"
#include"events.h"
#include"text.h"
//#include"updatenode.h"
//#include"VertexExtractor.h"
#include"turn_off.h"
#include"color.h"
#include <QMessageBox>
#include <QResizeEvent>
#include <QFileDialog>
#include <osgViewer/Viewer>
#include <osg/Node>
#include <osgDB/ReadFile>
#include <osgGA/TrackballManipulator>

#include <osgViewer/CompositeViewer>
#include <osg/ref_ptr>
#include <osg/Geode> 
#include <osg/Geometry>
#include <osg/Group>
#include <osg/MatrixTransform>
#include <osg/ShapeDrawable>


extern std::string outfile;
#define PI 3.14159265358979323846264338 
void finalmodel(osg::Node* node);
int readtext(std::string file, bool first, bool last);
zshift* zs = new zshift;
xshift* xs = new xshift;
yshift* ys = new yshift;
ashift* as = new ashift;
cshift* cs = new cshift;
osg::ref_ptr < osg::MatrixTransform >basicaxis= new osg::MatrixTransform;
//updatenode* update;
//osg::ref_ptr<osg::Node> stock;
osg::ref_ptr<osg::Switch> stockswitch = new osg::Switch;

lathe::lathe(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::lathe)
{
    ui->setupUi(this);
    //_pOsgQOpenGLWidget = new osgQOpenGLWidget(this);
   // _pOsgQOpenGLWidget->setGeometry(this->geometry());

    code = new code_configure;
    output_1 = new output_configure();
    knife_1 = new knife_configure();
    model_1 = new model_configure();

    tankWorldCoords = new transformAccumulator();


    _pOsgQOpenGLWidget = new osgQOpenGLWidget(ui->widget);
    _pOsgQOpenGLWidget->setGeometry(ui->widget->geometry());
    _pOsgQOpenGLWidget->setFocusPolicy(Qt::StrongFocus);
    ui->progressBar->hide();
    connect(_pOsgQOpenGLWidget, SIGNAL(initialized()), this, SLOT(initWindow()));
    connect(ui->startButton, SIGNAL(clicked()), this, SLOT(start()));
    connect(ui->outButton, SIGNAL(clicked()), this, SLOT(out()));
    connect(ui->finalButton, SIGNAL(clicked()), this, SLOT(finalm()));
    connect(ui->pauseButton, SIGNAL(clicked()), this, SLOT(pause()));
    connect(ui->actionstart, SIGNAL(triggered()), this, SLOT(start()));
    connect(ui->actionoutput_2, SIGNAL(triggered()), this, SLOT(out()));
    connect(ui->actionfinalmodel, SIGNAL(triggered()), this, SLOT(finalm()));
    connect(ui->actionpause, SIGNAL(triggered()), this, SLOT(pause()));
   // connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(change_model()));
    connect(ui->actionknife, SIGNAL(triggered()), this, SLOT(knife_action()));
    connect(ui->actionoutput, SIGNAL(triggered()), this, SLOT(output_action()));
    connect(ui->actioncodefile, SIGNAL(triggered()), this, SLOT(code_action()));
    connect(ui->actionmodelfile, SIGNAL(triggered()), this, SLOT(model_action()));
    connect(this, SIGNAL(open()), this, SLOT(setprogressOn()));
    connect(this, SIGNAL(set(double)), this, SLOT(setprogress(double)));
    connect(this, SIGNAL(closeit()), this, SLOT(setprogressOff()));

    connect(ui->followButton, SIGNAL(clicked()), this, SLOT(follow()));
    connect(ui->modelButton, SIGNAL(clicked()), this, SLOT(model()));
    connect(ui->yplus, SIGNAL(clicked()), this, SLOT(yplus()));
    connect(ui->yminus, SIGNAL(clicked()), this, SLOT(yminus()));
    connect(ui->aplus, SIGNAL(clicked()), this, SLOT(aplus()));
    connect(ui->aminus, SIGNAL(clicked()), this, SLOT(aminus()));
    connect(ui->cplus, SIGNAL(clicked()), this, SLOT(cplus()));
    connect(ui->cminus, SIGNAL(clicked()), this, SLOT(cminus()));


}

lathe::~lathe()
{
    delete ui;
    if (_pOsgQOpenGLWidget != NULL)
        delete _pOsgQOpenGLWidget;
}

void lathe::emitprogress(double va)
{
    emit set(va);
}
void lathe::emitprogressOn()
{
    emit open();
}
void lathe::emitprogressOff()
{
    emit closeit();
}

void lathe::setprogress(double va)
{
      ui->progressBar->setValue(va);
}
void lathe::setprogressOn()
{
 
   ui->progressBar->show();
}
void lathe::setprogressOff()
{
    
    ui->progressBar->hide();
    QMessageBox::information(this, "success", "success", QMessageBox::Ok);
}
void lathe::follow() {


tankWorldCoords->attachToGroup(stockswitch);
followTank=new followNodeMatrixManipulator(tankWorldCoords);

pViewer->setCameraManipulator(followTank);



}
void lathe::model() 
{
    pViewer->setCameraManipulator(new osgGA::TrackballManipulator);
}


void lathe::start()
{
    ui->progressBar->show();
    ys->start();
    xs->start();
    zs->start();
    as->start();
    cs->start();
}
void lathe::yplus()
{
    ys->plus();
}

void lathe::yminus()
{
    ys->minus();
}
void lathe::aplus()
{
    as->plus();
}

void lathe::aminus()
{
    as->minus();
}
void lathe::cplus()
{
    cs->plus();
}

void lathe::cminus()
{
    cs->minus();
}

void lathe::pause()
{
    ys->pause();
    xs->pause();
    zs->pause();
    as->pause();
    cs->pause();
}
void lathe::out()
{
    osgDB::writeNodeFile(*stock, outfile);

}
void lathe::finalm()
{ 
    std::thread yy(finalmodel, stock); 
    yy.detach();

}
void lathe::knife_action()
{
    
    knife_1->show();
}
void lathe::output_action()
{
    
    output_1->show();
}

void lathe::code_action()
{
   
    code->show();
}
void lathe::model_action()
{
    model_1->show();
}
/*void change_model(string file)

{
   // QString qfile = QFileDialog::getOpenFileName(this, "Select files", "C:/Users/Administrator/Deskop", "STL(*.stl)");
   // string file = qfile.toStdString();

    if (!update)delete update;
    update = new updatenode;
    turn_off invalidgeo(stockswitch);
    stockswitch->accept(invalidgeo);
    stock = osgDB::readNodeFile(file);
    stockswitch->addChild(stock, true);
    
    stock->setUpdateCallback(update);
}*/

void lathe::resizeEvent(QResizeEvent* ev)
{
    ui->widget->setGeometry(0, 0, ev->size().width() - 100, ev->size().height());
    _pOsgQOpenGLWidget->setGeometry(ui->widget->geometry());
    ui->startButton->move(ev->size().width() - 90, 30);
    ui->pauseButton->move(ev->size().width() - 90, 90);
    ui->finalButton->move(ev->size().width() - 90, 150);
    ui->outButton->move(ev->size().width() - 90, 210);
    ui->followButton->move(ev->size().width() - 90, 270);
    ui->modelButton->move(ev->size().width() - 90, 330);
    ui->progressBar->move(ev->size().width() - 90, ev->size().height()-110);


}


/*osg::ref_ptr<osg::StateSet> createTexture1DState()
{
    osg::ref_ptr<osg::Image> image = osgDB::readImageFile("y_wall.jpg");

    //创建二维纹理
    osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D;
    //设置边界处理
    texture->setWrap(osg::Texture2D::WRAP_S, osg::Texture2D::REPEAT);
    texture->setWrap(osg::Texture2D::WRAP_T, osg::Texture2D::REPEAT);
    //设置滤波
    texture->setFilter(osg::Texture::MIN_FILTER, osg::Texture::LINEAR);
    texture->setFilter(osg::Texture::MAG_FILTER, osg::Texture::NEAREST);
    //设置贴图
    texture->setImage(image.get());

    //设置自动纹理坐标，并指定相关的平面
    osg::ref_ptr<osg::TexGen> texgen = new osg::TexGen;
    texgen->setMode(osg::TexGen::OBJECT_LINEAR);
    texgen->setPlane(osg::TexGen::S, osg::Plane(0.0f, 0.0f, 1.0f, 0.0f));

    //创建属性集
    osg::ref_ptr<osg::StateSet> stateset = new osg::StateSet;

    //启用二维纹理
    stateset->setTextureAttribute(0, texture.get(), osg::StateAttribute::OVERRIDE);
    stateset->setTextureMode(0, GL_TEXTURE_2D, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);

    //启用纹理坐标生成器
    stateset->setTextureAttribute(0, texgen.get(), osg::StateAttribute::OVERRIDE);
    stateset->setTextureMode(0, GL_TEXTURE_GEN_S, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
    stateset->setTextureMode(0, GL_TEXTURE_GEN_T, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);

    return stateset.get();
}*/






void lathe::initWindow()
{

   // readtext("code.txt",true,true);

    

    pViewer = _pOsgQOpenGLWidget->getOsgViewer();
    pViewer->setCameraManipulator(new osgGA::TrackballManipulator); 
    pViewer->addEventHandler(new events);
    osg::ref_ptr<osg::Group> rpGroup = new osg::Group;
    TexCoordGenerator y3;
    osg::ref_ptr<osg::Node>lathe_main = osgDB::readNodeFile("base-01.stl");
    osg::ref_ptr<osg::Node>ei3 = osgDB::readNodeFile("Enclosure Inside-03.stl");
    lathe_main->accept(y3);



    rpGroup->addChild(ei3.get());
    rpGroup->addChild(lathe_main.get());
   
    
    osg::ref_ptr < osg::MatrixTransform >Xaxis = new osg::MatrixTransform;
    osg::ref_ptr < osg::MatrixTransform >Xbasicaxis = new osg::MatrixTransform;
    Xbasicaxis->setMatrix(osg::Matrix::translate(osg::Vec3(200, 143.9116, 0)));
    Xbasicaxis->addChild(Xaxis);
    rpGroup->addChild(Xbasicaxis);
    Xaxis->setDataVariance(osg::Object::DYNAMIC);
    //Xaxis->setUpdateCallback(Z);
    Xaxis->setUpdateCallback(xs);
    osg::ref_ptr<osg::Node> Xnode = osgDB::readNodeFile("x-01.stl");
    Xaxis->addChild(Xnode.get());

   
   
    osg::ref_ptr < osg::MatrixTransform >Zaxis = new osg::MatrixTransform;
    Xaxis->addChild(Zaxis);
    Zaxis->setDataVariance(osg::Object::DYNAMIC);
    //Xaxis->setUpdateCallback(Z);
    Zaxis->setUpdateCallback(zs);
    osg::ref_ptr<osg::Node> Znode = osgDB::readNodeFile("z-01.stl");
    Zaxis->addChild(Znode.get());
    osg::ref_ptr<osg::Node> Znode2 = osgDB::readNodeFile("z-02.stl");
    Zaxis->addChild(Znode2.get());



    osg::ref_ptr<osg::Cylinder> cy1;
    cy1 = new osg::Cylinder;
    
    cy1->setCenter(osg::Vec3(0, 0, 0));
    cy1->setHeight(150);
    cy1->setRadius(2);
    osg::ref_ptr<osg::ShapeDrawable> sd6 = new osg::ShapeDrawable(cy1);
    sd6->setColor(osg::Vec4(1, 1, 0, 0.5));
    osg::ref_ptr<osg::Geode> knife = new osg::Geode;
    osg::ref_ptr<osg::StateSet>knifestate = knife->getOrCreateStateSet();
    knifestate->setMode(GL_BLEND, osg::StateAttribute::ON |
        osg::StateAttribute::PROTECTED);
    knifestate->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
    knife->addDrawable(sd6.get());

    Zaxis->addChild(knife);

    //tankWorldCoords->attachToGroup(Zaxis);
    //followTank=new followNodeMatrixManipulator(tankWorldCoords);
   

    osg::ref_ptr < osg::MatrixTransform >Yaxis = new osg::MatrixTransform;
    rpGroup->addChild(Yaxis.get());
    Yaxis->setDataVariance(osg::Object::DYNAMIC);
    //Yaxis->setUpdateCallback(Z);
    Yaxis->setUpdateCallback(ys);
    osg::ref_ptr<osg::Node> Ynode = osgDB::readNodeFile("y-01.stl");
    Yaxis->addChild(Ynode.get());
    osg::ref_ptr<osg::Node> Ynode2 = osgDB::readNodeFile("y-02.stl");
    Yaxis->addChild(Ynode2.get());
    osg::ref_ptr<osg::Node> Ynode3 = osgDB::readNodeFile("y-03.stl");
    Yaxis->addChild(Ynode3.get());
    
    Ynode3->accept(y3);

    osg::ref_ptr<osg::Node> Ynode4 = osgDB::readNodeFile("y-04.stl");
    Yaxis->addChild(Ynode4.get());

    osg::ref_ptr < osg::MatrixTransform >Aaxis = new osg::MatrixTransform;
    Yaxis->addChild(Aaxis.get());
    Aaxis->setDataVariance(osg::Object::DYNAMIC);
    Aaxis->setUpdateCallback(as);
    osg::ref_ptr<osg::Node> Anode = osgDB::readNodeFile("a-01.stl");
    Aaxis->addChild(Anode.get());

    osg::ref_ptr < osg::MatrixTransform >Caxis = new osg::MatrixTransform;
    Aaxis->addChild(Caxis.get());
    Caxis->setDataVariance(osg::Object::DYNAMIC);
    Caxis->setUpdateCallback(cs);
    osg::ref_ptr<osg::Node> Cnode = osgDB::readNodeFile("c.stl");
    
   


    Caxis->addChild(Cnode.get());
    osg::ref_ptr<osg::Node> fnode = osgDB::readNodeFile("fixture-01.stl");
    osg::ref_ptr<osg::Node> fnode2 = osgDB::readNodeFile("fixture-02.stl");
    osg::ref_ptr<osg::Node> fnode3 = osgDB::readNodeFile("fixture-03.stl");
    osg::ref_ptr<osg::Node> fnode4 = osgDB::readNodeFile("fixture-04.stl");
    Caxis->addChild(fnode.get());
    Caxis->addChild(fnode2.get());
    Caxis->addChild(fnode3.get());
    Caxis->addChild(fnode4.get());


    
    Caxis->addChild(stockswitch);

   
   // stockswitch->addChild(stock,true);
   
    rpGroup->addChild(basicaxis);
   

 //   updatenode* update = new updatenode;
    
 //   stock->setUpdateCallback(update);
    pViewer->setSceneData(rpGroup.get());


}

