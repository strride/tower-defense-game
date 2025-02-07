#pragma once
#include "SceneGame.h"
class SceneLevel2 : public SceneGame
{
public:
	SceneLevel2(RenderWindow& renderWindow, Event& event, int highscore, bool reset);
	bool init() override;
private:
	const float KING_POS_X = 1138;
	const float KING_POS_Y = 564;
	static const int NB_TOWERS = 9;
	static const int NB_WAYPOINTS = 14;
	static const int DOUBLE_WAYPOINT = 5;
	static const int PATH_ONE_START = 6;
	static const int PATH_ONE_END = 10;
	static const int PATH_TWO_START = 11;
	static const int PATH_TWO_END = NB_WAYPOINTS - 1;
	const float TOWERS_POS[NB_TOWERS][2] = {
		{110, 620},
		{228, 320},
		{444, 780},
		{362, 530},
		{610, 222},
		{998, 270},
		{630, 460},
		{935, 520},
		{798, 760}
	};
	const float WAYPOINTS_POS[NB_WAYPOINTS][2] = {
		{88, 412},
		{168, 465},
		{222, 588},
		{308, 670},
		{424, 668},
		{510, 590},
		{478, 468},
		{516, 380},
		{594, 360},
		{806, 368},
		{1140, 450},
		{660, 598},
		{804, 650},
		{1140, 680}
	};
	const float DEMON_START_POS_X = -100;
	const float DEMON_START_POS_Y = 410;

	void setUpWaypoints();
};

