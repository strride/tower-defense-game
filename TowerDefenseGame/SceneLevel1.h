#pragma once
#include "SceneGame.h"

class SceneLevel1: public SceneGame 
{
public:
	SceneLevel1(RenderWindow& renderWindow, Event& event, int highscore, bool reset);
	bool init() override;

private:
	const float KING_POS_X = 1138;
	const float KING_POS_Y = 600;
	static const int TOWERS_COUNT = 8;
	static const int WAYPOINTS_COUNT = 11;
	const float TOWERS_POS[TOWERS_COUNT][2] = {
		{470, 170},
		{770, 250},
		{440, 370},
		{650, 520},
		{120, 650},
		{470, 700},
		{850, 710},
		{660, 950}
	};
	const float WAYPOINTS_POS[WAYPOINTS_COUNT][2] = {
		{610, 8},
		{630, 222},
		{595, 444},
		{478, 514},
		{320, 558},
		{260, 620},
		{280, 720},
		{348, 812},
		{720, 830},
		{968, 850},
		{1110, 682}
	};
	const float DEMON_START_POS_X = 610;
	const float DEMON_START_POS_Y = -100;
	void setUpWaypoints();
};

