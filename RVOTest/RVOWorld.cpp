#include "RVOWorld.h"

#include <QTimer>
#include <QDebug>

#include "RVOTest.h""

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
	sim->setTimeStep(1.25f);
	sim->setAgentDefaults(15.0f, 10, 10.0f, 10.0f, 1.5f, 2.0f);

	for (size_t i = 0; i < 250; ++i)
	{
		float x = std::cos(i * 2.0f * M_PI / 250.0f);
		float y = std::sin(i * 2.0f * M_PI / 250.0f);
		sim->addAgent(200.0f * RVO::Vector2(x, y));
		m_view->AddAgent(QPointF(x*200 + 500, y*200 + 500));
		goals.push_back(-sim->getAgentPosition(i) * 2);
		qDebug() << -sim->getAgentPosition(i).x() << -sim->getAgentPosition(i).y();
	}
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