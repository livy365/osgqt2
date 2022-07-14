#include "updatenode.h"
osg::ref_ptr<osg::Node> stock(osg::ref_ptr<osg::Vec3Array> ver, osg::ref_ptr<osg::Vec3Array> nor)
{
	// ����һ�����ڱ��漸����Ϣ�Ķ���
	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;

	// �������������
	osg::ref_ptr<osg::Vec3Array> v = ver;
	geom->setVertexArray(v.get());

	osg::ref_ptr<osg::Vec2Array> tc2 = new osg::Vec2Array;
	//geom->setTexCoordArray(0, tc2.get());
	osg::ref_ptr<osg::Vec3Array> rpNormal = nor;
	geom->setNormalArray(rpNormal.get());
	osg::ref_ptr<osg::Vec4Array> c = new osg::Vec4Array;






	// Ϊ���ߴ���һ������
	//geom->setNormalArray(rpNormal);
	//geom->setNormalBinding(osg::Geometry::BIND_PER_VERTEX);



	// �ɱ�������ݻ����ĸ�����Ķ����

	osg::ref_ptr<osg::DrawElementsUInt> rpFace = new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLE_STRIP);
	for (int i = 0; i < v->size()-1; i++) {
		
			rpFace->push_back(i);
			
			}

	

	geom->addPrimitiveSet(rpFace);



	// �� Geode ����Ӽ����壨Drawable�������� Geode 
	osg::ref_ptr<osg::Geode> geode = new osg::Geode;
	geode->addDrawable(geom.get());
	return geode.get();
}