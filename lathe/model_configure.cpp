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

	// ����ɢ�����ɫ: ���/�׹�
	light->setDiffuse(osg::Vec4(1.0, 1.0, 1.0, 1.0));
	// ���ó���˥��ָ��
	light->setConstantAttenuation(1.0);
	// ��������˥��ָ��
	light->setLinearAttenuation(0.0);
	// ���ö���˥��ָ��
	light->setQuadraticAttenuation(0.0);

	pLightSource->setLight(light.get());

	return pLightSource;
}

osg::Camera* creatBirdsEye(const osg::BoundingSphere& bs)
{
	osg::ref_ptr<osg::Camera> camera = new osg::Camera;//����һ������ڵ�
	camera->setClearMask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//���������ɫ����Ȼ��棬
																 //����ζ����������Ⱦ�ӳ���ʱ�Ḳ��֮ǰ�κ��������Ⱦ����
	camera->setReferenceFrame(osg::Transform::ABSOLUTE_RF);//��������Ĳο�����ϵ������ΪABSOLUTE_RF��ζ����������б任����͹۲�/ͶӰ���������
														  //�����������������Ĳ����ܵ���һ�������Ӱ��


	//���ݰ�Χ���С�����������ͶӰ����
	double viewDistance = 2.0 * bs.radius();
	double znear = viewDistance - bs.radius();
	double zfar = viewDistance + bs.radius();
	float top = bs.radius();
	float right = bs.radius();
	camera->setProjectionMatrixAsFrustum(-right, right, -top, top, znear, zfar);


	//����ģ�͵�����λ�ã���������Ĺ۲����
	osg::Vec3d upDirection(-1.0, 1.0, 1.0);
	osg::Vec3d viewDirection(1.0, -1.0, 1.0);
	osg::Vec3d center = bs.center();
	osg::Vec3d eyePoint = center + viewDirection * viewDistance;
	camera->setViewMatrixAsLookAt(eyePoint, center, upDirection);
	camera->setAllowEventFocus(false);
	camera->setViewport(0, 0, 570, 324);//���ô���λ�ô�С
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