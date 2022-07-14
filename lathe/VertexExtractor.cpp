#include <iostream>
#include <osg/Geometry>
#include <osg/Geode> 
#include <osg/Drawable>
#include <osg/Node>
#include <vector>
#include <string>
#include<fstream>
#include <osg/ref_ptr>
#include <osg/Group>
#include "lathe.h"
#define PI 3.14159265358979323846264338 
extern lathe* w1;
bool isitequal(osg::Vec3 a, osg::Vec3 b);
using namespace std;
double process=0;
void getposition(string file, std::vector<double> &strVec)
{
	using namespace std;
	ifstream text;
	text.open(file, ios::in);


	while (!text.eof())
	{
		string inbuf;
		//getline(text, inbuf, 'E');
		getline(text, inbuf, '\n');
		double num = std::stod(inbuf);

		strVec.push_back(num);
	}
}
void finalmodel(osg::Node* node) //重载apply方法，将调用场景功能图形中的每个节点，检查其名称是否符合输入的要求。如果符合的话，将保存节点的地址。

	{
	    w1->emitprogressOn();
		osg::ref_ptr<osg::Geode>geode = node->asGroup()->getChild(0)->asGeode();
		for (int i = 0; i < geode->getNumDrawables(); ++i)//获取数量，Return the number of Drawables currently attached to the Geode，
		{												 //在本人测试的数据中，数据中包含的Drawables数量都是1 
			osg::Geometry* geom = dynamic_cast<osg::Geometry*>(geode->getDrawable(i));

			if (!geom)
				continue;

			osg::Vec3Array* verts = dynamic_cast<osg::Vec3Array*>(geom->getVertexArray());//将当前geom的顶点数组保存到verts中，此时verts为指针。
			/*取verts第一行的值  verts->begin(),verts->at(0)，取verts第二行的值,verts->at(1),取verts第三行第一列的值,(*verts)[2][0]*/
			osg::Vec4Array* color = dynamic_cast<osg::Vec4Array*>(geom->getColorArray());
			std::vector<double> x, y, z, a, c;

			getposition("readx.txt", x);
			getposition("ready.txt", y);
			getposition("readz.txt", z);
			getposition("reada.txt", a);
			getposition("readc.txt", c);


			int size_v = verts->end() - verts->begin();//图像所包含的顶点个数


			for (int m = 0; m < x.size(); ++m)
			{
				osg::Matrix mx, my, mz, ma, mc;
				osg::Matrix mx1, my1, mz1, ma1, mc1;
				

				mx.makeTranslate(-osg::Vec3(x[m], 0, 0));
				mx1.makeTranslate(osg::Vec3(x[m], 0, 0));

				
				
				mz.makeTranslate(osg::Vec3(0, 0, -z[m]));
				mz1.makeTranslate(osg::Vec3(0, 0, z[m]));

		
				my.makeTranslate(osg::Vec3(0, -y[m], 0));
				my1.makeTranslate(osg::Vec3(0, y[m], 0));

				ma.makeRotate(-osg::DegreesToRadians(a[m]), osg::Vec3(1, 0, 0));
				ma1.makeRotate(osg::DegreesToRadians(a[m]), osg::Vec3(1, 0, 0));

				mc.makeRotate(-osg::DegreesToRadians(c[m]), osg::Vec3(0, 0, 1));
				mc1.makeRotate(osg::DegreesToRadians(c[m]), osg::Vec3(0, 0, 1));

				osg::Matrix mt = mc * ma * my * mx * mz;
				osg::Matrix mt1 = mz1 * mx1 * my1 * ma1 * mc1;


	                for (int k = 0; k < size_v; ++k)//对所有顶点坐标进行修改,不修改可省略此循环
		           	{


				  //std::cout << cc<<std::endl;
				  //c->push_back(osg::Vec4(1,1,0,1));
				          if (isitequal((*verts)[k] * mt, osg::Vec3f(0., 0., 0.)))
				          {
				


				   // c->at(k) = osg::Vec4(0, 1, 1, 1);
					//std::cout << "yes" << std::endl;

					//osg::Vec3 v (x, y, z);
				  //  std::cout << "(*verts)"<<i<<":" << (*verts)[i][0] << "  " << (*verts)[i][1] << "  " << (*verts)[i][2] << "          " << "(*verts)" << k<<":" << (*verts)[k][0] << "  " << (*verts)[k][1] << "  " << (*verts)[k][2] << std::endl;


                    
					         (*verts)[k] = osg::Vec3f(0., 0., 0.) * mt1;
					          color->at(k) = osg::Vec4(0, 1, 0, 0);
					//c->at(k) = osg::Vec4(0, 1, 0, 0);
					/*osg::Vec3Array* newverts = new osg::Vec3Array;
					for (int k = 0; k <= 360; k = k + 10)
					{
						double hk = (PI / 180) * (k);
						float x =  cos(hk) ;
						float y =  sin(hk) ;
					
						newverts->push_back(osg::Vec3(x+(*verts)[k].x(), y+(*verts)[k].y(), (*verts)[k].z()));

					}*/
					//verts->insert(verts->end(), newverts->begin(), newverts->end());
			             	}

				// std::cout << ((*verts)[k] * mt)[0]<<" " << ((*verts)[k] * mt)[1] << " " << ((*verts)[k] * mt)[2] << std::endl;


			        }

					//std::cout <<  (double)m/x.size()*100<<std::endl;
					w1->emitprogress((double)m / x.size() * 100);
				//	verts->insert(verts->end(), osg::Vec3f(0., 0., 0.));

			}

		
		}
		w1->emitprogressOff();
}
