#include<iostream>
#include <osg/ref_ptr>
#include <osg/Geode> 
#include <osg/Geometry>
#include <osg/Group>
#include <osg/MatrixTransform> 
class updatenode : public osg::NodeCallback
{
public:


	virtual void operator()(osg::Node* node, osg::NodeVisitor* nv)
	{
		
		osg::ref_ptr<osg::Geode>geode = node->asGroup()->getChild(0)->asGeode();
		for (int i = 0; i < geode->getNumDrawables(); ++i)//��ȡ������Return the number of Drawables currently attached to the Geode��
		{												 //�ڱ��˲��Ե������У������а�����Drawables��������1 
			osg::Geometry* geom = dynamic_cast<osg::Geometry*>(geode->getDrawable(i));

			if (!geom)
				continue;

			osg::Vec3Array* verts = dynamic_cast<osg::Vec3Array*>(geom->getVertexArray());//����ǰgeom�Ķ������鱣�浽verts�У���ʱvertsΪָ�롣
			/*ȡverts��һ�е�ֵ  verts->begin(),verts->at(0)��ȡverts�ڶ��е�ֵ,verts->at(1),ȡverts�����е�һ�е�ֵ,(*verts)[2][0]*/

			osg::Vec3Array* normalverts = dynamic_cast<osg::Vec3Array*>(geom->getNormalArray());
			osg::ref_ptr<osg::Vec4Array> c = new osg::Vec4Array;
			int size_v = verts->end() - verts->begin();//ͼ���������Ķ������
			for (int k = 0; k < size_v; ++k)//�����ж�����������޸�,���޸Ŀ�ʡ�Դ�ѭ��
			{
				osg::Vec3 new_v((*verts)[k][0] + 0.0228271484, (*verts)[k][1] - 384.411621, (*verts)[k][2] + 834.500061);//osg::Vec3 v (x, y, z);

				normalverts->at(k) = new_v;
				// std::cout << (*normalverts)[k][0]<<" " << (*normalverts)[k][1] << " " << (*normalverts)[k][2] << std::endl;
				c->push_back(osg::Vec4((double)((int)(*verts)[k][0] % 10) / 10, (double)((int)(*verts)[k][1] % 10) / 10, (double)((int)(*verts)[k][2] % 10) / 10,1.f));

			}
			//normalverts->push_back(osg::Vec3(1, 0, 0));
			geom->setNormalArray(normalverts);

			geom->setNormalBinding(osg::Geometry::BIND_PER_VERTEX);
			

			geom->setColorArray(c.get());
			geom->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
		}
	}
};
