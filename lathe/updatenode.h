#include<iostream>
#include <osg/ref_ptr>
#include <osg/Geode> 
#include <osg/Geometry>
#include <osg/Group>
#include <osg/MatrixTransform> 
extern osg::Matrix mx, my, mz, ma, mc;
extern osg::Matrix mx1, my1, mz1, ma1, mc1;
bool isitequal(osg::Vec3 a, osg::Vec3 b);
//int dis(osg::Vec3 a, osg::Vec3 b);
//bool isitupequal(osg::Vec3 a, osg::Vec3 b);
extern osg::ref_ptr<osg::Switch> stockswitch;


class updatenode : public osg::NodeCallback
{
protected:
osg::ref_ptr<osg::Vec4Array> c= new osg::Vec4Array;
public:

	
	void defultcolor(int size)
	{
	
		if(c->end() - c->begin()<size)
	    {	
		   for (int k = 0; k < size; ++k)//对所有顶点坐标进行修改,不修改可省略此循环
		   {
			 c->push_back(osg::Vec4(1, 1, 0, 0));
		   }
	    }
	}
	virtual void operator()(osg::Node* node, osg::NodeVisitor* nv)
	{
		osg::Matrix mt = mc * ma * my *mx * mz;
		osg::Matrix mt1 = mz1*mx1*my1*ma1*mc1;
		osg::ref_ptr<osg::Geode>geode = node->asGroup()->getChild(0)->asGeode();
		//for (int i = 0; i < geode->getNumDrawables(); ++i)//获取数量，Return the number of Drawables currently attached to the Geode，
		//{												 //在本人测试的数据中，数据中包含的Drawables数量都是1 
			osg::Geometry* geom = dynamic_cast<osg::Geometry*>(geode->getDrawable(0));

		

			osg::Vec3Array* verts = dynamic_cast<osg::Vec3Array*>(geom->getVertexArray());//将当前geom的顶点数组保存到verts中，此时verts为指针。
			//取verts第一行的值  verts->begin(),verts->at(0)，取verts第二行的值,verts->at(1),取verts第三行第一列的值,(*verts)[2][0]

			osg::Vec3Array* normalverts = dynamic_cast<osg::Vec3Array*>(geom->getNormalArray());
			
			int size_v = verts->end() - verts->begin();//图像所包含的顶点个数
			defultcolor(size_v);
			
			for (int k = 0; k < size_v; ++k)//对所有顶点坐标进行修改,不修改可省略此循环
			{

				
				//std::cout << cc<<std::endl;
				//c->push_back(osg::Vec4(1,1,0,1));
				if (isitequal((*verts)[k] * mt, osg::Vec3f(0., 0., 0.)))
				{
                

				  
				 // c->at(k) = osg::Vec4(0, 1, 1, 1);
				  std::cout << "yes"<<std::endl;
				  
						  //osg::Vec3 v (x, y, z);
						//  std::cout << "(*verts)"<<i<<":" << (*verts)[i][0] << "  " << (*verts)[i][1] << "  " << (*verts)[i][2] << "          " << "(*verts)" << k<<":" << (*verts)[k][0] << "  " << (*verts)[k][1] << "  " << (*verts)[k][2] << std::endl;
						 
					  
				  
                  (*verts)[k] = osg::Vec3f(0., 0., 0.) *mt1;
				  c->at(k) = osg::Vec4(0, 1, 0, 0);

				}
				
				// std::cout << ((*verts)[k] * mt)[0]<<" " << ((*verts)[k] * mt)[1] << " " << ((*verts)[k] * mt)[2] << std::endl;
				

			}
			//std::cout << ((*verts)[1] * mt)[0] << " " << ((*verts)[1] * mt)[1] << " " << ((*verts)[1] * mt)[2] << std::endl;
			//normalverts->push_back(osg::Vec3(1, 0, 0));
			//geom->setNormalArray(normalverts);

			//geom->setNormalBinding(osg::Geometry::BIND_PER_VERTEX);

			osg::StateSet* stateset = geode->getOrCreateStateSet();
			
			
		
			geom->setColorArray(c.get());
			geom->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
		// 
		//}
	}
	
};

