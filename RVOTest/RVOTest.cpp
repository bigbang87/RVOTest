#include "RVOTest.h"
#include <QVBoxLayout>

RVOTest::RVOTest(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	this->setWindowFlag(Qt::FramelessWindowHint);
	m_QScene = std::make_unique<QGraphicsScene>();

	m_QScene->setSceneRect(0, 0, 600, 600);
	this->setFixedSize(QSize(800, 800));


	QWidget* mainWidget = new QWidget(this);
	setCentralWidget(mainWidget);

	m_QView = new QGraphicsView(this);
	m_QView->setBackgroundBrush(QBrush(QColor(30, 30, 30, 255), Qt::SolidPattern));
	m_QView->setDragMode(QGraphicsView::ScrollHandDrag);
	m_QView->resize(800, 800);
	m_QView->setScene(m_QScene.get());
	
	QPen pen(Qt::green, 3, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin);
	QBrush brush(Qt::red, Qt::SolidPattern);
	QRectF rect(100.0, 200.1, 11.2, 16.3);
	m_QScene->addEllipse(rect, pen, brush);
}
