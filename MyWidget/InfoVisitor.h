#include <iostream>
#include <osg/Geometry>
#include <osg/Geode> 
#include <osg/Drawable>
#include <osg/Node>
#include <osg/NodeVisitor>
#include<osgDB/OutputStream>
#include <vector>
#include <string>

using namespace std;

class VertexExtractor : public osg::NodeVisitor
{
public:
	osg::ref_ptr<osg::Vec3Array> extracted_verts;//osg定义的三维Array  用来保存顶点数据
	osg::ref_ptr<osg::Vec3Array> normal_verts;
	VertexExtractor() : osg::NodeVisitor(osg::NodeVisitor::TRAVERSE_ALL_CHILDREN)//构造函数，选项TRAVERSE_ALL_CHILDREN为遍历所有结点.
	{
		extracted_verts = new osg::Vec3Array;
	}

	void apply(osg::Geode& geode) //重载apply方法，将调用场景功能图形中的每个节点，检查其名称是否符合输入的要求。如果符合的话，将保存节点的地址。

	{
		for (int i = 0; i < geode.getNumDrawables(); ++i)//获取数量，Return the number of Drawables currently attached to the Geode，
		{												 //在本人测试的数据中，数据中包含的Drawables数量都是1 
			osg::Geometry* geom = dynamic_cast<osg::Geometry*>(geode.getDrawable(i));

			if (!geom)
				continue;

			osg::Vec3Array* verts = dynamic_cast<osg::Vec3Array*>(geom->getVertexArray());//将当前geom的顶点数组保存到verts中，此时verts为指针。
			/*取verts第一行的值  verts->begin(),verts->at(0)，取verts第二行的值,verts->at(1),取verts第三行第一列的值,(*verts)[2][0]*/

			osg::Vec3Array* normalverts = dynamic_cast<osg::Vec3Array*>(geom->getNormalArray());
			osg::ref_ptr<osg::Vec4Array> c = new osg::Vec4Array;
			int size_v = verts->end() - verts->begin();//图像所包含的顶点个数
			for (int k = 0; k < size_v; ++k)//对所有顶点坐标进行修改,不修改可省略此循环
			{
				
			}
			//normalverts->push_back(osg::Vec3(1, 0, 0));
		
			
			//-0.0228271484, 384.411621, -834.500061
			
			extracted_verts = verts;
			normal_verts = normalverts;


		}

	}
};