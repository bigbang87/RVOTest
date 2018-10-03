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
	void AddAgent(QPointF pos);
	void UpdateAgentPosition(int index, QPointF pos);
	void AddPolygon(QVector<QPointF> pointArray);

private:
	void setNumericalGrid();
	void setGrid();

private:
	Ui::RVOTestClass ui;
	std::unique_ptr<QGraphicsScene> m_QScene; 
	QGraphicsView* m_QView;
	QVector<QGraphicsEllipseItem*> m_agents;
};
