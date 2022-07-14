#include "model_configure.h"
#include"turn_off.h"
#include"updatenode.h"
#include <QFileDialog>
#include <thread>
#include <QMessageBox>
#include <osgDB/ReadFile>
#include "lathe.h"
#include "ClassfollowNode.h"
//extern lathe* w1;
updatenode* update_node;
osg::ref_ptr<osg::Node> stock;

model_configure::model_configure(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.label->hide();
	connect(ui.selectButton, SIGNAL(clicked()), this, SLOT(chose()));
	connect(ui.OKButton, SIGNAL(clicked()), this, SLOT(ok()));
	connect(ui.deleteButton, SIGNAL(clicked()), this, SLOT(del()));
	connect(this, SIGNAL(finish_signal()), this, SLOT(finished()));
}

model_configure::~model_configure()
{
}
void model_configure::emitfinished()
{
	emit  finish_signal();
}

void model_configure::chose()
{
	QStringList _lFileNames;
	_lFileNames.append(QFileDialog::getOpenFileNames(this, "Select  files", "C:/Users/Administrator/Deskop", "stl(*.stl)"));

	for (auto file : _lFileNames)
	{
		ui.mode_list->addItem(file);
	}

}

osg::ref_ptr<osg::LightSource> pLightSource() {

	osg::ref_ptr<osg::LightSource> pLightSource = new osg::LightSource;
	osg::ref_ptr<osg::Light> light = new osg::Light;
	light->setAmbient(osg::Vec4(.1f, .1f, .1f, 1.f));
	light->setDiffuse(osg::Vec4(.8f, .8f, .8f, 1.f));
	light->setSpecular(osg::Vec4(.8f, .8f, .8f, 1.f));
	light->setPosition(osg::Vec4(0.f, -100.f, 200.f, 0.0f));
	//light->setDirection(osg::Vec3(0.f, 0.f, 01.f));

	// 设置散射光颜色: 红光/白光
	light->setDiffuse(osg::Vec4(1.0, 1.0, 1.0, 1.0));
	// 设置常量衰减指数
	light->setConstantAttenuation(1.0);
	// 设置线行衰减指数
	light->setLinearAttenuation(0.0);
	// 设置二次衰减指数
	light->setQuadraticAttenuation(0.0);

	pLightSource->setLight(light.get());

	return pLightSource;
}

osg::Camera* creatBirdsEye(const osg::BoundingSphere& bs)
{
	osg::ref_ptr<osg::Camera> camera = new osg::Camera;//定义一个相机节点
	camera->setClearMask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//清除它的颜色和深度缓存，
																 //这意味着这个相机渲染子场景时会覆盖之前任何相机的渲染数据
	camera->setReferenceFrame(osg::Transform::ABSOLUTE_RF);//设置相机的参考坐标系，设置为ABSOLUTE_RF意味着相机的所有变换矩阵和观察/投影矩阵的设置
														  //都是相对于世界坐标的不会受到上一级矩阵的影响


	//根据包围球大小，设置相机的投影矩阵
	double viewDistance = 2.0 * bs.radius();
	double znear = viewDistance - bs.radius();
	double zfar = viewDistance + bs.radius();
	float top = bs.radius();
	float right = bs.radius();
	camera->setProjectionMatrixAsFrustum(-right, right, -top, top, znear, zfar);


	//根据模型的中心位置，设置相机的观察矩阵。
	osg::Vec3d upDirection(-1.0, 1.0, 1.0);
	osg::Vec3d viewDirection(1.0, -1.0, 1.0);
	osg::Vec3d center = bs.center();
	osg::Vec3d eyePoint = center + viewDirection * viewDistance;
	camera->setViewMatrixAsLookAt(eyePoint, center, upDirection);
	camera->setAllowEventFocus(false);
	camera->setViewport(0, 0, 570, 324);//设置窗口位置大小
	camera->setClearColor(osg::Vec4(0, 0.5, 1, 0));

	return camera.release();
}
void model_configure::change_model(std::string file)

{
	if (!update_node)delete update_node;
	update_node = new updatenode;
	turn_off invalidgeo(stockswitch);
	stockswitch->accept(invalidgeo);
	stock = osgDB::readNodeFile(file);

	stockswitch->addChild(stock, true);
	stock->setUpdateCallback(update_node);

	osg::ref_ptr<osg::LightSource> LightSource = pLightSource();
	

	osg::Camera* camera = creatBirdsEye(stock->getBound());
	//camera->setViewMatrixAsLookAt(osg::Vec3d (1.0, 1.0, 1.0)* 2.0 * stock->getBound().radius() +stock->getBound().center(), stock->getBound().center(), osg::Vec3d(-1.0, 1.0, 1.0));
	camera->addChild(stock);
	//stockswitch->addChild(camera);
    camera->addChild(LightSource.get());




	emitfinished();
}


void model_configure::ok()
{
	
	//cout << ui.mode_list->currentItem()->text().toStdString();
	if (ui.mode_list->currentItem())
	{
        
		
		ui.label->show();
		std::string file= ui.mode_list->currentItem()->text().toLocal8Bit().toStdString();
		//cout << ui.mode_list->currentItem()->text().toLocal8Bit().toStdString();

        std::thread yy(std::bind(&model_configure::change_model,this,file));
		yy.detach();

		
	}
	

}
void model_configure::del()
{

	ui.mode_list->takeItem(ui.mode_list->currentRow());

}

void model_configure::finished() {

	ui.label->hide();
	QMessageBox::information(this, "success", "success", QMessageBox::Ok);

}