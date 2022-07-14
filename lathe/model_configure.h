#pragma once
#include <string>
#include <QWidget>
#include "ui_model_configure.h"

class model_configure : public QWidget
{
	Q_OBJECT

public:
	model_configure(QWidget *parent = Q_NULLPTR);
	~model_configure();

	void change_model(std::string file);
	void emitfinished();
signals:
	void finish_signal();
protected slots:
	void chose();
	void ok();;
	void del();
	void finished();
private:

	Ui::model_configure ui;
};
