#include "RVOTest.h"

#include <QVBoxLayout>
#include <QGraphicsItem>

RVOTest::RVOTest(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	//this->setWindowFlag(Qt::FramelessWindowHint);
	m_QScene = std::make_unique<QGraphicsScene>();

	m_QScene->setSceneRect(0, 0, 1000, 1000);
	this->setFixedSize(QSize(800, 800));

	QWidget* mainWidget = new QWidget(this);
	setCentralWidget(mainWidget);

	m_QView = new QGraphicsView(this);
	m_QView->setBackgroundBrush(QBrush(QColor(30, 30, 30, 255), Qt::SolidPattern));
	m_QView->setDragMode(QGraphicsView::ScrollHandDrag);
	m_QView->resize(800, 800);
	m_QView->setScene(m_QScene.get());
}

void RVOTest::AddAgent(QPointF pos)
{
	QPen pen(Qt::green, 3, Qt::SolidLine);
	QBrush brush(Qt::red, Qt::SolidPattern);
	QRectF rect(pos.x(), pos.y(), 5, 5);
	m_agents.push_back(m_QScene->addEllipse(rect, pen, brush));
}

void RVOTest::UpdateAgentPosition(int index, QPointF pos)
{
	QGraphicsEllipseItem* test = m_agents[index];
	test->setPos(pos);
}
