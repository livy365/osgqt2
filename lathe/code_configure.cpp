#include "code_configure.h"
#include <QFileDialog>
#include <QDir>
#include<string>
#include<iostream>
#include <QMessageBox>
#include <thread>
#include"sports.h"
extern zshift* zs;
extern xshift* xs;
extern yshift* ys;
extern ashift* as;
extern cshift* cs;
int readtext(std::string file, bool first, bool last);
code_configure::code_configure(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
    ui.label->hide();
	connect(ui.choseButton, SIGNAL(clicked()), this, SLOT(chose()));
    connect(ui.OK, SIGNAL(clicked()), this, SLOT(ok()));
    connect(ui.delButton, SIGNAL(clicked()), this, SLOT(del()));
    connect(this, SIGNAL(finish_signal()), this, SLOT(finished()));
}

code_configure::~code_configure()
{
}
void code_configure::chose()
{
    QStringList _lFileNames;
    _lFileNames.append(QFileDialog::getOpenFileNames(this, "Select  files", "C:/Users/Administrator/Deskop", "TXT(*.txt)"));

    for (auto file : _lFileNames)
    {
        ui.list->addItem(file);;
       
    }

}

void code_configure::OK_thread() {

    int row = 0;
    QString line;

    while (row < (ui.list->count()))
    {
        bool first, last;
        line = ui.list->item(row)->text();
        if (row == 0)first = true; else first = false;
        if (row == ui.list->count() - 1)last = true; else last = false;
        readtext(line.toStdString(), first, last);
        row++;
    }

    ys->setposition();
    xs->setposition();
    zs->setposition();
    as->setposition();
    cs->setposition();
    emitfinished();
}


void code_configure::ok()
{
    ui.label->show();
    std::thread yy(std::bind(&code_configure::OK_thread, this));
    yy.detach();

}
void code_configure::del()
{
    std::cout << "dsd";
    ui.list->takeItem(ui.list->currentRow());
 //   QListWidgetItem* item = ui.list->currentItem();//被选中或背点击的item删除
//   
  // ui.list->removeItemWidget(item);
  //  delete item;

}

void code_configure::emitfinished()
{
    emit  finish_signal();
}

void code_configure::finished() {

    ui.label->hide();
    QMessageBox::information(this, "success", "success", QMessageBox::Ok);

}