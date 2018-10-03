#include "RVOTest.h"

#include <QVBoxLayout>
#include <QGraphicsItem>

RVOTest::RVOTest(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	//this->setWindowFlag(Qt::FramelessWindowHint);
	m_QScene = std::make_unique<QGraphicsScene>();

	m_QScene->setSceneRect(-500, -500, 1000, 1000);
	this->setFixedSize(QSize(800, 800));

	QWidget* mainWidget = new QWidget(this);
	setCentralWidget(mainWidget);

	m_QView = new QGraphicsView(this);
	m_QView->setDragMode(QGraphicsView::ScrollHandDrag);
	m_QView->resize(800, 800);
	m_QView->setScene(m_QScene.get());

	QPen pen(Qt::red);
	QBrush brush(Qt::red, Qt::SolidPattern);
	QRectF rect(0, -200, 5, 5);
	m_QScene->addEllipse(rect, pen, brush);
	setNumericalGrid();
	setGrid();
}

void RVOTest::AddAgent(QPointF pos)
{
	QPen pen(Qt::black);
	QBrush brush(Qt::black, Qt::SolidPattern);
	QRectF rect(pos.x(), pos.y(), 5, 5);
	m_agents.push_back(m_QScene->addEllipse(rect, pen, brush));
}

void RVOTest::UpdateAgentPosition(int index, QPointF pos)
{
	QGraphicsEllipseItem* test = m_agents[index];
	test->setPos(pos);
}

void RVOTest::AddPolygon(QVector<QPointF> poly)
{
	m_QScene->addPolygon(poly);
}

void RVOTest::setNumericalGrid()
{
	int multiplier = 100;
	for (int y = -10; y < 10; ++y)
	{
		for (int x = -10; x < 10; ++x)
		{
			QPoint pos(x * multiplier, y * multiplier);
			QString output = "";
			if (x != 0)
				output += QString::number(x * multiplier);
			if (y != 0)
			{
				if (x != 0)
					output += ", ";
				output += QString::number(y * multiplier);
			}
			if (x == 0 && y == 0)
				output = "0";
			auto item = m_QScene->addSimpleText(output);
			item->setPos(pos);
		}
	}
}

void RVOTest::setGrid()
{
	const QRectF GRID_RECT(m_QScene->sceneRect());
	const int DENSITY = 25;
	const int SEPARATOR = 8;
	const QPen PEN(QColor(40, 40, 40, 50), 1, Qt::SolidLine);
	const QPen BOLD_PEN(QColor(50, 50, 50, 50), 2, Qt::SolidLine);

	for (qreal i = GRID_RECT.x(); i < GRID_RECT.width(); i += DENSITY)
	{
		QPointF a(i, GRID_RECT.y());
		QPointF b(i, GRID_RECT.width());
		int currPosX = static_cast<int>(i);
		QGraphicsLineItem* newLine = nullptr;
		if (currPosX % SEPARATOR != 0)
			newLine = m_QScene->addLine(QLineF(a, b), PEN);
		else
			newLine = m_QScene->addLine(QLineF(a, b), BOLD_PEN);
		newLine->setZValue(-3);
		newLine->setFlag(QGraphicsItem::ItemIsSelectable, false);
		newLine->setFlag(QGraphicsItem::ItemIsMovable, false);
	}

	for (qreal i = GRID_RECT.y(); i < GRID_RECT.height(); i += DENSITY)
	{
		QPointF a(GRID_RECT.x(), i);
		QPointF b(GRID_RECT.height(), i);
		int currPosX = static_cast<int>(i);
		QGraphicsLineItem* newLine = nullptr;
		if (currPosX % SEPARATOR != 0)
			newLine = m_QScene->addLine(QLineF(a, b), PEN);
		else
			newLine = m_QScene->addLine(QLineF(a, b), BOLD_PEN);
		newLine->setZValue(-3);
		newLine->setFlag(QGraphicsItem::ItemIsSelectable, false);
		newLine->setFlag(QGraphicsItem::ItemIsMovable, false);
	}
}