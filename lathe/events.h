#pragma once
#include <osgDB/WriteFile>
#include<osgDB/ReaderWriter>

#include<osgDB/OutputStream>


#include<osgViewer/ViewerEventHandlers>
#include"sports.h"
extern zshift* zs ;
extern xshift* xs ;
extern yshift* ys;
extern ashift* as ;
extern cshift* cs ;
extern osg::ref_ptr<osg::Node> stock ;
//void finalmodel(osg::Node* geode);

class events :public osgGA::GUIEventHandler
{
public:
	virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
	{
	
		switch (ea.getEventType())
		{
		case (osgGA::GUIEventAdapter::KEYDOWN):
		{
			if (ea.getKey() == 'o' || ea.getKey() == 'O')
			{

				ys->start();
				xs->start();
				zs->start();
				as->start();
				cs->start();


			}
			if (ea.getKey() == 'p' || ea.getKey() == 'P')
			{

			osgDB::writeNodeFile(*stock,"out.stl");

			}
			if (ea.getKey() == 'k' || ea.getKey() == 'K')
			{

                //  finalmodel(stock);
			}

			

			
		}

		}
	return 0;
	}
	
};
