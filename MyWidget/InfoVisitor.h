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
	osg::ref_ptr<osg::Vec3Array> extracted_verts;//osg�������άArray  �������涥������
	osg::ref_ptr<osg::Vec3Array> normal_verts;
	VertexExtractor() : osg::NodeVisitor(osg::NodeVisitor::TRAVERSE_ALL_CHILDREN)//���캯����ѡ��TRAVERSE_ALL_CHILDRENΪ�������н��.
	{
		extracted_verts = new osg::Vec3Array;
	}

	void apply(osg::Geode& geode) //����apply�����������ó�������ͼ���е�ÿ���ڵ㣬����������Ƿ���������Ҫ��������ϵĻ���������ڵ�ĵ�ַ��

	{
		for (int i = 0; i < geode.getNumDrawables(); ++i)//��ȡ������Return the number of Drawables currently attached to the Geode��
		{												 //�ڱ��˲��Ե������У������а�����Drawables��������1 
			osg::Geometry* geom = dynamic_cast<osg::Geometry*>(geode.getDrawable(i));

			if (!geom)
				continue;

			osg::Vec3Array* verts = dynamic_cast<osg::Vec3Array*>(geom->getVertexArray());//����ǰgeom�Ķ������鱣�浽verts�У���ʱvertsΪָ�롣
			/*ȡverts��һ�е�ֵ  verts->begin(),verts->at(0)��ȡverts�ڶ��е�ֵ,verts->at(1),ȡverts�����е�һ�е�ֵ,(*verts)[2][0]*/

			osg::Vec3Array* normalverts = dynamic_cast<osg::Vec3Array*>(geom->getNormalArray());
			osg::ref_ptr<osg::Vec4Array> c = new osg::Vec4Array;
			int size_v = verts->end() - verts->begin();//ͼ���������Ķ������
			for (int k = 0; k < size_v; ++k)//�����ж�����������޸�,���޸Ŀ�ʡ�Դ�ѭ��
			{
				
			}
			//normalverts->push_back(osg::Vec3(1, 0, 0));
		
			
			//-0.0228271484, 384.411621, -834.500061
			
			extracted_verts = verts;
			normal_verts = normalverts;


		}

	}
};