#pragma once

#include <QWidget>
#include "ui_code_configure.h"

class code_configure : public QWidget
{
	Q_OBJECT

public:
	code_configure(QWidget *parent = Q_NULLPTR);
	~code_configure();
	void OK_thread();
	void emitfinished();
signals:
	void finish_signal();
protected slots:
	void finished();
	void chose();
	void ok();
	void del();
private:
	Ui::code_configure ui;
};
