#include "RVOWorld.h"

#include <QTimer>
#include <QDebug>

#include "RVOTest.h"

#ifndef M_PI
const float M_PI = 3.14159265358979323846f;
#endif

RVOWorld::RVOWorld(RVOTest* view)
{
	m_view = view;
	m_sim = new RVO::RVOSimulator();
	setupScenario(m_sim);
	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(SLUpdate()));
	timer->start(5);
}

void RVOWorld::setupScenario(RVO::RVOSimulator *sim)
{
	sim->setTimeStep(0.51f);
	sim->setAgentDefaults(15.0f, 10, 10.0f, 10.0f, 1.5f, 2.0f);

	for (int i = -7; i < 7; ++i)
	{
		for (int j = -7; j < 7; ++j)
		{
			sim->addAgent(RVO::Vector2(-250.0f + i * 5, -150.0f + j * 5));
			m_view->AddAgent(QPointF(0, 0));
			goals.push_back(RVO::Vector2(0 + i * 5, -10 + j * 5));
		}
	}

	/*
 * Add (polygonal) obstacles, specifying their vertices in counterclockwise
 * order.
 */
	std::vector<RVO::Vector2> obstacle1, obstacle2, obstacle3, obstacle4;

	obstacle1.push_back(RVO::Vector2(10.0f, 0.0f));
	obstacle1.push_back(RVO::Vector2(-20.0f, 0.0f));
	obstacle1.push_back(RVO::Vector2(-20.0f, -30.0f));
	obstacle1.push_back(RVO::Vector2(10.0f, -30.0f));
	QVector<QPointF> v1;
	v1.push_back(QPointF(10.0f, 0.0f));
	v1.push_back(QPointF(-20.0f, 0.0f));
	v1.push_back(QPointF(-20.0f, -30.0f));
	v1.push_back(QPointF(10.0f, -30.0f));
	m_view->AddPolygon(v1);

	sim->addObstacle(obstacle1);

	/* Process the obstacles so that they are accounted for in the simulation. */
	sim->processObstacles();
}

void RVOWorld::updateVisualization(RVO::RVOSimulator* sim)
{
	for (size_t i = 0; i < sim->getNumAgents(); ++i)
	{
		RVO::Vector2 rPos = sim->getAgentPosition(i);
		QPointF qPos = QPointF(rPos.x(), rPos.y());
		m_view->UpdateAgentPosition(i, qPos);
	}
}

void RVOWorld::setPreferredVelocities(RVO::RVOSimulator *sim)
{
#ifdef _OPENMP
#pragma omp parallel for
#endif
	for (int i = 0; i < static_cast<int>(sim->getNumAgents()); ++i) {
		RVO::Vector2 goalVector = goals[i] - sim->getAgentPosition(i);

		if (RVO::absSq(goalVector) > 1.0f) {
			goalVector = RVO::normalize(goalVector);
		}

		sim->setAgentPrefVelocity(i, goalVector);
	}
}

bool RVOWorld::reachedGoal(RVO::RVOSimulator *sim)
{
	for (size_t i = 0; i < sim->getNumAgents(); ++i) {
		if (RVO::absSq(sim->getAgentPosition(i) - goals[i]) > sim->getAgentRadius(i) * sim->getAgentRadius(i)) {
			return false;
		}
	}

	return true;
}

void RVOWorld::SLUpdate()
{
	if (!reachedGoal(m_sim))
	{
		updateVisualization(m_sim);
		setPreferredVelocities(m_sim);
		m_sim->doStep();
	}
	else
	{
		//delete m_sim;
	}
}