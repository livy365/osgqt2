#include "output_configure.h"
#include <QMessageBox>
#include <QDebug>
#include <QFileDialog>
#include <QDir>
std::string outfile="out.stl";
output_configure::output_configure(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
    ui.lineEdit->setText(QString::fromStdString(outfile));
	connect(ui.changeButton, SIGNAL(clicked()), this, SLOT(outputfile()));
    connect(ui.yesButton, SIGNAL(clicked()), this, SLOT(yes()));
}

output_configure::~output_configure()
{
}
void output_configure::outputfile()
{

    QString srcDirPath = QFileDialog::getExistingDirectory(
        this, "choose src Directory",
        "/");

    if (srcDirPath.isEmpty())
    {
        return;
    }
    else
    {
        qDebug() << "srcDirPath=" << srcDirPath;
        srcDirPath += "/";
    }
    ui.lineEdit->setText(srcDirPath + "out.stl");
	outfile= ui.lineEdit->text().toStdString();
}

void output_configure::yes()
{

    outfile = ui.lineEdit->text().toStdString();
}