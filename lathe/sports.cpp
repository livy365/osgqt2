#include "sports.h"
#include "lathe.h"
#include<stdlib.h>
#include<iostream>
#include<string>
#include<fstream>

int i1=0, i2 = 0,i3=0,i4=0,i5=0;

osg::Matrix mx,my,mz,ma,mc;
osg::Matrix mx1, my1, mz1, ma1, mc1;
extern lathe *w1;

zshift::zshift() {
	
	
	length =250;
	setposition();
}
void zshift::operator()(osg::Node* node, osg::NodeVisitor* nv)
{


	osg::MatrixTransform* mtshift =
		dynamic_cast<osg::MatrixTransform*>(node);
	osg::Matrix mT;
	osglength = osg::Vec3(0, 0, length+75 );
	mT.makeTranslate(osglength);
	mtshift->setMatrix(mT);
	//std::cout << shiftlength / vec << std::endl;
	mz .makeTranslate(osg::Vec3(0, 0, -length));
	mz1.makeTranslate(osg::Vec3(0, 0, length));
// cy.stockgeode((shiftlength / vec) - 800);
	
	if (moving)
	{

		
		if (i2 == strVec.size())
		{
			w1->emitprogressOff();
			moving = false;
			std::cout << "zend";
		}
		
		else  
		{
			
			setlength(strVec[i2]);
            i2++;
		}
		w1->emitprogressOn();
		w1->emitprogress((double)i2 / strVec.size() * 100);
    // w1->setprogress((double)i2 /strVec.size() * 100);
	}

	traverse(node, nv);

}

void zshift::setlength(double a)
{





	length = a;
	moving = true;
}
void zshift::pause()
{
	moving = false;
}

void zshift::setposition()
{
	using namespace std;
	ifstream text;
	text.open("readz.txt", ios::in);
	strVec.clear();

	while (!text.eof())
	{
		string inbuf;
		//getline(text, inbuf, 'E');
		getline(text, inbuf, '\n');
		double num = std::stod(inbuf);

		strVec.push_back(num);
	}



}

void zshift::start() 
{
	moving = true;
}

xshift::xshift() {

	
	length = 0;
	setposition();
}
void xshift::operator()(osg::Node* node, osg::NodeVisitor* nv)
{


	osg::MatrixTransform* mtshift =
		dynamic_cast<osg::MatrixTransform*>(node);
	osg::Matrix mT;
	osglength = osg::Vec3(length-200,0,0);
	mT.makeTranslate(osglength);
	mtshift->setMatrix(mT);
	//std::cout << shiftlength / vec << std::endl;
	mx.makeTranslate(-osg::Vec3(length, 0, 0));
	mx1.makeTranslate(osg::Vec3(length, 0, 0));
// cy.stockgeode((shiftlength / vec) - 800);

	if (moving)
	{


		if (i1 == strVec.size())
		{
			moving = false;
			
		}

		else
		{

			setlength(strVec[i1]);
			i1++;
		}


	}

	traverse(node, nv);

}
void xshift::start()
{
	moving = true;
}
void xshift::setlength(double a)
{





	length = a;
	moving = true;
}
void xshift::pause()
{
	moving = false;
}
void xshift::setposition()
{
	using namespace std;
	ifstream text;
	text.open("readx.txt", ios::in);
	strVec.clear();

	while (!text.eof())
	{
		string inbuf;
		//getline(text, inbuf, 'E');
		getline(text, inbuf, '\n');
		double num = std::stod(inbuf);

		strVec.push_back(num);
	}



}




yshift::yshift() {

	
	length = 0;
	setposition();
}
void yshift::operator()(osg::Node* node, osg::NodeVisitor* nv)
{


	osg::MatrixTransform* mtshift =
		dynamic_cast<osg::MatrixTransform*>(node);
	osg::Matrix mT;
	osglength = osg::Vec3(0, -length+ 143.9116,0);
	mT.makeTranslate(osglength);
	mtshift->setMatrix(mT);
	//std::cout << shiftlength / vec << std::endl;
	my.makeTranslate(osg::Vec3(0, -length , 0));
	my1.makeTranslate(osg::Vec3(0, length , 0));
// cy.stockgeode((shiftlength / vec) - 800);

	if (moving)
	{


		if (i3 == strVec.size())
		{
			moving = false;
			std::cout << "zend";
		}

		else
		{

			setlength(strVec[i3]);
			i3++;
		}


	}

	traverse(node, nv);

}
void yshift::start()
{
	moving = true;
}
void yshift::pause()
{
	moving = false;
}
void yshift::plus()
{
	length=length+10;
}
void yshift::minus()
{
	length = length -10;
}
void yshift::setlength(double a)
{





	length = a;
	moving = true;
}
void yshift::setposition()
{
	using namespace std;
	ifstream text;
	text.open("ready.txt", ios::in);
	strVec.clear();

	while (!text.eof())
	{
		string inbuf;
		//getline(text, inbuf, 'E');
		getline(text, inbuf, '\n');
		double num = std::stod(inbuf);

		strVec.push_back(num);
	}



}



ashift::ashift() {


	rotate = 0;
	setposition();
}

void ashift::operator()(osg::Node* node, osg::NodeVisitor* nv)
{


	osg::MatrixTransform* mtshift =
		dynamic_cast<osg::MatrixTransform*>(node);
	osg::Matrix mR;
	//mT.makeTranslate(osg::Vec3(75, -410, 693.3259));
	mR.makeRotate(osg::DegreesToRadians(-rotate), osg::Vec3(1, 0, 0));
	//mt.makeTranslate(osg::Vec3(-75, 410, -693.3259));
	//mtshift->setMatrix(mT * mR * mt);
	mtshift->setMatrix( mR );
	ma = mR;
	ma1.makeRotate(osg::DegreesToRadians(rotate), osg::Vec3(1, 0, 0));
	if (moving)
	{


		if (i4 == strVec.size())
		{
			moving = false;
			
		}

		else
		{

			setlength(strVec[i4]);
			i4++;
		}


	}

	traverse(node, nv);

}
void ashift::start()
{
	moving = true;
}
void ashift::plus()
{
	rotate++;
}
void ashift:: minus()
{
	rotate--;
}


void ashift::pause()
{
	moving = false;
}
void ashift::setlength(double a)
{

	rotate = a;
	moving = true;

}
void ashift::setposition()
{
	using namespace std;
	ifstream text;
	text.open("reada.txt", ios::in);
	strVec.clear();

	while (!text.eof())
	{
		string inbuf;
		//getline(text, inbuf, 'E');
		getline(text, inbuf, '\n');
		double num = std::stod(inbuf);

		strVec.push_back(num);
	}



}

cshift::cshift() {


	rotate = 0;

	setposition();
}

void cshift::operator()(osg::Node* node, osg::NodeVisitor* nv)
{


	osg::MatrixTransform* mtshift =
		dynamic_cast<osg::MatrixTransform*>(node);
	osg::Matrix mR;
	//mT.makeTranslate(osg::Vec3(75, -410, 693.3259));
	mR.makeRotate(osg::DegreesToRadians(-rotate), osg::Vec3(0, 0, 1));
	//mt.makeTranslate(osg::Vec3(-75, 410, -693.3259));
	//mtshift->setMatrix(mT * mR * mt);
	mtshift->setMatrix(mR);
	mc = mR;
	mc1.makeRotate(osg::DegreesToRadians(rotate), osg::Vec3(0, 0, 1));
	if (moving)
	{


		if (i5 == strVec.size())
		{
			moving = false;

		}

		else
		{

			setlength(strVec[i5]);
			i5++;
		}


	}

	traverse(node, nv);

}
void cshift::start()
{
	moving = true;
}

void cshift::plus()
{
	rotate++;
}
void cshift::minus()
{
	rotate--;
}

void cshift::pause()
{
	moving =false;
}
void cshift::setlength(double a)
{

	rotate = a;
	moving = true;
}
void cshift::setposition()
{
	using namespace std;
	ifstream text;
	text.open("readc.txt", ios::in);
	strVec.clear();

	while (!text.eof())
	{
		string inbuf;
		//getline(text, inbuf, 'E');
		getline(text, inbuf, '\n');
		double num = std::stod(inbuf);

		strVec.push_back(num);
	}



}