/*#include <iostream>
#include <osg/Geometry>
#include <osg/Geode> 
#include <osg/Drawable>
#include <vector>
#include <string>
#include <osg/Node>
#include <osg/ShapeDrawable>
#include <osg/Switch>
extern osg::ref_ptr<osg::Switch> stockswitch;

void stockmake(osg::ref_ptr<osg::Vec3Array> extracted_verts, int size)
{
	for (int k = 0; k < size; ++k)
	{
		osg::Vec3 new_v((*extracted_verts)[k][0] , (*extracted_verts)[k][1], (*extracted_verts)[k][2]);

        osg::ref_ptr<osg::Sphere> cy1=new osg::Sphere;
        cy1->setCenter(new_v);
        cy1->setRadius(1);
        osg::ref_ptr<osg::ShapeDrawable> sd6 = new osg::ShapeDrawable(cy1);
        sd6->setColor(osg::Vec4(1, 1, 0, 0.5));
        osg::ref_ptr<osg::Geode> partical = new osg::Geode;
        osg::ref_ptr<osg::StateSet>particalstate = partical->getOrCreateStateSet();
        particalstate->setMode(GL_BLEND, osg::StateAttribute::ON |
            osg::StateAttribute::PROTECTED);
        particalstate->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
        partical->addDrawable(sd6.get());
        stockswitch->addChild(partical, true);
	}


}*/