#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_RVOTest.h"

class RVOTest : public QMainWindow
{
	Q_OBJECT

public:
	RVOTest(QWidget *parent = Q_NULLPTR);

private:
	Ui::RVOTestClass ui;
};
