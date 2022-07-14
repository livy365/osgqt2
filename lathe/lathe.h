#ifndef lathe_H
#define lathe_H
#include "knife_configure.h"
#include "output_configure.h"
#include "code_configure.h"
#include "model_configure.h"
#include "ClassfollowNode.h"
//#include"updatenode.h"
#include <QtWidgets/QMainWindow>
#include<QCoreApplication>
#include <QWidget>
#include <osgQOpenGL/osgQOpenGLWidget>
#include <string>
#include <osg/Node>
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class lathe; }
QT_END_NAMESPACE

class lathe : public QMainWindow
{
    Q_OBJECT

public:
    lathe(QWidget* parent = nullptr);
    ~lathe();
   
    
    void emitprogress(double va);
    void emitprogressOn();
    void emitprogressOff();
    //void change_model(string file);
    signals:
    void open();
    void set(double value);
    void closeit();
 public slots:
    void initWindow();
    void start();
    void pause();
    void out();
    void finalm();
    void knife_action();
    void output_action();
    void code_action();
    void model_action();
    void setprogress(double va);
    void setprogressOn();
    void setprogressOff();
    void follow();
    void model();
    void yplus();
    void yminus();
    void aplus();
    void aminus();
    void cplus();
    void cminus();

protected:
    osgQOpenGLWidget* _pOsgQOpenGLWidget;
    string _sFilename;
    void resizeEvent(QResizeEvent* ev);

private:
    Ui::lathe* ui;
    code_configure* code;
    knife_configure* knife_1;
    output_configure* output_1;
    model_configure* model_1;
    osgViewer::Viewer* pViewer;
    transformAccumulator* tankWorldCoords;
    followNodeMatrixManipulator* followTank;

};

#endif // lathe_H

