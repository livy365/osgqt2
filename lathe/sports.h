#pragma once
#include <osg/ref_ptr>
#include <osg/Geode> 
#include <osg/Geometry>
#include <osg/Group>
#include <osg/MatrixTransform> 
class zshift : public osg::NodeCallback
{
public:

	zshift();
	virtual void operator()(osg::Node* node, osg::NodeVisitor* nv);
	void setlength(double a);
	void setposition();
	void start();
	void pause();
protected:
	int vec = 10;
	std::vector<double> strVec;
	bool moving = false;
	double shiftlength, plus, originallength;
	double length;
	osg::Vec3 osglength;
};

class xshift : public osg::NodeCallback
{
public:

	xshift();
	virtual void operator()(osg::Node* node, osg::NodeVisitor* nv);
	void setlength(double a);
	void setposition();
	void start();
	void pause();
protected:
	int vec = 10;
	std::vector<double> strVec;
	bool moving = false;
	double shiftlength, plus, originallength;
	double length;
	osg::Vec3 osglength;
};

class yshift : public osg::NodeCallback
{
public:

	yshift();
	virtual void operator()(osg::Node* node, osg::NodeVisitor* nv);
	void setlength(double a);
	void setposition();
	void start();
	void pause();
	void plus();
	void minus();

protected:
	int vec = 10;
	std::vector<double> strVec;
	bool moving = false;
	double shiftlength, originallength;
	double length;
	osg::Vec3 osglength;
};


class ashift : public osg::NodeCallback
{
public:
	ashift();

	virtual void operator()(osg::Node* node, osg::NodeVisitor* nv);
	void setlength(double a);
	void setposition();
	void start();
	void pause();
	void plus();
	void minus();
protected:
	int vec = 10;
	bool moving = false;
	double rotate = 0, currentrotate = 0; int c = 0;
	std::vector<double> strVec;
};

class cshift : public osg::NodeCallback
{
public:
	cshift();

	virtual void operator()(osg::Node* node, osg::NodeVisitor* nv);
	void setlength(double a);
	void setposition();
	void start();
	void pause();
	void plus();
	void minus();
protected:
	int vec = 10;
	bool moving = false;
	double rotate = 0,  currentrotate = 0; int c = 0;
	std::vector<double> strVec;
};