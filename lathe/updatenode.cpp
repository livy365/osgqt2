#include "updatenode.h"
/*bool isitequal6666(osg::Vec3 a, osg::Vec3 b)
{
	if ((a.x() - b.x()) * (a.x() - b.x()) + (a.y() - b.y()) * (a.y() - b.y()) + (a.z() - b.z()) * (a.z() - b.z()) <= 4)
	{
		return true;
	}
	else
	{
		return false;
	}
}*/
bool isitequal(osg::Vec3 a, osg::Vec3 b)
{
	if ((a.x() - b.x()) * (a.x() - b.x()) + (a.y() - b.y()) * (a.y() - b.y()) <= 2 && (a.z() > b.z()+2))
	{
		return true;
	}
	else
	{
		return false;
	}
}
/*bool isitupequal(osg::Vec3 a, osg::Vec3 b)
{
	if ((a.x() == b.x()) &&(a.y() == b.y())&&(a.z()>=b.z()) )
	{
		return true;
	}
	else
	{
		return false;
	}
}*/
/*int dis(osg::Vec3 a, osg::Vec3 b)
{

	return (a.x() - b.x()) * (a.x() - b.x()) + (a.y() - b.y()) * (a.y() - b.y()) + (a.z() - b.z()) * (a.z() - b.z());	

}*/