#include "updatenode.h"
osg::ref_ptr<osg::Node> stock(osg::ref_ptr<osg::Vec3Array> ver, osg::ref_ptr<osg::Vec3Array> nor)
{
	// 创建一个用于保存几何信息的对象
	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;

	// 创建顶点的数组
	osg::ref_ptr<osg::Vec3Array> v = ver;
	geom->setVertexArray(v.get());

	osg::ref_ptr<osg::Vec2Array> tc2 = new osg::Vec2Array;
	//geom->setTexCoordArray(0, tc2.get());
	osg::ref_ptr<osg::Vec3Array> rpNormal = nor;
	geom->setNormalArray(rpNormal.get());
	osg::ref_ptr<osg::Vec4Array> c = new osg::Vec4Array;






	// 为法线创建一个数组
	//geom->setNormalArray(rpNormal);
	//geom->setNormalBinding(osg::Geometry::BIND_PER_VERTEX);



	// 由保存的数据绘制四个顶点的多边形

	osg::ref_ptr<osg::DrawElementsUInt> rpFace = new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLE_STRIP);
	for (int i = 0; i < v->size()-1; i++) {
		
			rpFace->push_back(i);
			
			}

	

	geom->addPrimitiveSet(rpFace);



	// 向 Geode 类添加几何体（Drawable）并返回 Geode 
	osg::ref_ptr<osg::Geode> geode = new osg::Geode;
	geode->addDrawable(geom.get());
	return geode.get();
}