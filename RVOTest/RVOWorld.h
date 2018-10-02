#pragma once

#ifndef RVO_OUTPUT_TIME_AND_POSITIONS
#define RVO_OUTPUT_TIME_AND_POSITIONS 1
#endif

#include <QObject>
#include <cmath>
#include <cstddef>
#include <vector>

#if RVO_OUTPUT_TIME_AND_POSITIONS
#include <iostream>
#endif

#include <RVO.h>

class RVOTest;
class RVOWorld : public QObject
{
	Q_OBJECT

public:
	RVOWorld(RVOTest* view);
	void setupScenario(RVO::RVOSimulator *sim);
	void updateVisualization(RVO::RVOSimulator *sim);
	void setPreferredVelocities(RVO::RVOSimulator *sim);
	bool reachedGoal(RVO::RVOSimulator *sim);

public slots:
	void SLUpdate();

private:
	std::vector<RVO::Vector2> goals;
	RVOTest* m_view;
	RVO::RVOSimulator* m_sim;
};