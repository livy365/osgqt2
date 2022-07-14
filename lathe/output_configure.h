#pragma once

#include <QWidget>
#include "ui_output_configure.h"

class output_configure : public QWidget
{
	Q_OBJECT

public:
	output_configure(QWidget *parent = Q_NULLPTR);
	~output_configure();
protected slots :
	void outputfile();
	void yes();

private:
	Ui::output_configure ui;
};
