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

	
	void applyKKK(osg::Geode& geode) //����apply�����������ó�������ͼ���е�ÿ���ڵ㣬����������Ƿ���������Ҫ��������ϵĻ���������ڵ�ĵ�ַ��

	{
		for (int i = 0; i < geode.getNumDrawables(); ++i)//��ȡ������Return the number of Drawables currently attached to the Geode��
		{												 //�ڱ��˲��Ե������У������а�����Drawables��������1 
			osg::Geometry* geom = dynamic_cast<osg::Geometry*>(geode.getDrawable(i));

			if (!geom)
				continue;

			osg::Vec3Array* verts = dynamic_cast<osg::Vec3Array*>(geom->getVertexArray());//����ǰgeom�Ķ������鱣�浽verts�У���ʱvertsΪָ�롣
			/*ȡverts��һ�е�ֵ  verts->begin(),verts->at(0)��ȡverts�ڶ��е�ֵ,verts->at(1),ȡverts�����е�һ�е�ֵ,(*verts)[2][0]*/


			int size_v = verts->end() - verts->begin();//ͼ���������Ķ������
			for (int k = 0; k < size_v; ++k)//�����ж�����������޸�,���޸Ŀ�ʡ�Դ�ѭ��
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
		for (int i = 0; i < geode.getNumDrawables(); ++i)//��ȡ������Return the number of Drawables currently attached to the Geode��
		{												 //�ڱ��˲��Ե������У������а�����Drawables��������1 
			osg::Geometry* geom = dynamic_cast<osg::Geometry*>(geode.getDrawable(i));

			if (!geom)
				continue;

			osg::Vec3Array* verts = dynamic_cast<osg::Vec3Array*>(geom->getVertexArray());//����ǰgeom�Ķ������鱣�浽verts�У���ʱvertsΪָ�롣
			/*ȡverts��һ�е�ֵ  verts->begin(),verts->at(0)��ȡverts�ڶ��е�ֵ,verts->at(1),ȡverts�����е�һ�е�ֵ,(*verts)[2][0]*/

			osg::Vec3Array* normalverts = dynamic_cast<osg::Vec3Array*>(geom->getNormalArray());

			int size_v = verts->end() - verts->begin();//ͼ���������Ķ������
			//defultcolor(size_v);
			osg::Vec4Array* c = new osg::Vec4Array;
			for (int k = 0; k < size_v; ++k)//�����ж�����������޸�,���޸Ŀ�ʡ�Դ�ѭ��
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