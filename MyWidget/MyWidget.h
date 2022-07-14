#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MyWidget.h"


#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <osgQOpenGL/osgQOpenGLWidget>
#include <string>

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MyWidget; }
QT_END_NAMESPACE

class MyWidget : public QMainWindow
{
    Q_OBJECT

public:
    MyWidget(QWidget* parent = nullptr);
    ~MyWidget();

    void resizeEvent(QResizeEvent* ev);

protected slots:
    void initWindow();

protected:
    osgQOpenGLWidget* _pOsgQOpenGLWidget;
    string _sFilename;

private:
    Ui::MyWidget* ui;
};
#endif // MYWIDGET_H

