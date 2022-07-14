#pragma once

#include <QWidget>
#include "ui_knife_configure.h"

class knife_configure : public QWidget
{
	Q_OBJECT

public:
	knife_configure(QWidget *parent = Q_NULLPTR);
	~knife_configure();

private:
	Ui::knife_configure ui;
};
