#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_RVOTest.h"
#include <qgraphicsscene.h>
#include <qgraphicsview.h>

#include <memory>

class RVOTest : public QMainWindow
{
	Q_OBJECT

public:
	RVOTest(QWidget* parent = Q_NULLPTR);

private:
	Ui::RVOTestClass ui;
	std::unique_ptr<QGraphicsScene> m_QScene;
	QGraphicsView* m_QView;
};
