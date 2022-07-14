#include <iostream>
#include <osg/Geometry>
#include <osg/Geode> 
#include <osg/Drawable>
#include <osg/Node>
#include <osg/NodeVisitor>
#include <vector>
#include <string>

class color : public osg::NodeVisitor
{
public:
	color() : osg::NodeVisitor(osg::NodeVisitor::TRAVERSE_ALL_CHILDREN) {

	}

	
	void applyKKK(osg::Geode& geode) //重载apply方法，将调用场景功能图形中的每个节点，检查其名称是否符合输入的要求。如果符合的话，将保存节点的地址。

	{
		for (int i = 0; i < geode.getNumDrawables(); ++i)//获取数量，Return the number of Drawables currently attached to the Geode，
		{												 //在本人测试的数据中，数据中包含的Drawables数量都是1 
			osg::Geometry* geom = dynamic_cast<osg::Geometry*>(geode.getDrawable(i));

			if (!geom)
				continue;

			osg::Vec3Array* verts = dynamic_cast<osg::Vec3Array*>(geom->getVertexArray());//将当前geom的顶点数组保存到verts中，此时verts为指针。
			/*取verts第一行的值  verts->begin(),verts->at(0)，取verts第二行的值,verts->at(1),取verts第三行第一列的值,(*verts)[2][0]*/


			int size_v = verts->end() - verts->begin();//图像所包含的顶点个数
			for (int k = 0; k < size_v; ++k)//对所有顶点坐标进行修改,不修改可省略此循环
			{
				osg::Vec3 new_v((*verts)[k][0] +1000, (*verts)[k][1] +1000, (*verts)[k][2] + 1000);//osg::Vec3 v (x, y, z);
				verts->at(k) = new_v;
			}

			if (!verts)
				continue;
			
		}

	}



	 void apply(osg::Geode& geode)
	{

		//osg::ref_ptr<osg::Geode>geode = node.asGroup()->getChild(0)->asGeode();
		for (int i = 0; i < geode.getNumDrawables(); ++i)//获取数量，Return the number of Drawables currently attached to the Geode，
		{												 //在本人测试的数据中，数据中包含的Drawables数量都是1 
			osg::Geometry* geom = dynamic_cast<osg::Geometry*>(geode.getDrawable(i));

			if (!geom)
				continue;

			osg::Vec3Array* verts = dynamic_cast<osg::Vec3Array*>(geom->getVertexArray());//将当前geom的顶点数组保存到verts中，此时verts为指针。
			/*取verts第一行的值  verts->begin(),verts->at(0)，取verts第二行的值,verts->at(1),取verts第三行第一列的值,(*verts)[2][0]*/

			osg::Vec3Array* normalverts = dynamic_cast<osg::Vec3Array*>(geom->getNormalArray());

			int size_v = verts->end() - verts->begin();//图像所包含的顶点个数
			//defultcolor(size_v);
			osg::Vec4Array* c = new osg::Vec4Array;
			for (int k = 0; k < size_v; ++k)//对所有顶点坐标进行修改,不修改可省略此循环
			{

				osg::Vec3 new_v((*verts)[k][0] + 1000, (*verts)[k][1] + 1000, (*verts)[k][2] + 1000);//osg::Vec3 v (x, y, z);
				verts->at(k) = new_v;
				//std::cout << cc<<std::endl;
				c->push_back(osg::Vec4(1,1,0,1));
				
				//c->push_back(osg::Vec4((double)((int)(*verts)[k][0] % 10) / 10, (double)((int)(*verts)[k][1] % 10) / 10, (double)((int)(*verts)[k][2] % 10) / 10, 1.f));
				// std::cout << ((*verts)[k] * mt)[0]<<" " << ((*verts)[k] * mt)[1] << " " << ((*verts)[k] * mt)[2] << std::endl;
				normalverts->at(k) = new_v;

			}
			//std::cout << ((*verts)[1] * mt)[0] << " " << ((*verts)[1] * mt)[1] << " " << ((*verts)[1] * mt)[2] << std::endl;
			//normalverts->push_back(osg::Vec3(1, 0, 0));
			geom->setNormalArray(normalverts);

			geom->setNormalBinding(osg::Geometry::BIND_PER_VERTEX);


			geom->setColorArray(c);
			geom->setColorBinding(osg::Geometry::BIND_PER_VERTEX);

		}
		std::cout << "2";
		//traverse(*geode);

	}





};