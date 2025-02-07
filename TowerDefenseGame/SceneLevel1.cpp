#include "SceneLevel1.h"

SceneLevel1::SceneLevel1(RenderWindow& renderWindow, Event& event, int highscore, bool reset): SceneGame(renderWindow, event, highscore, reset)
{
	
}

bool SceneLevel1::init()
{
	SceneGame::setMap(Maps::map1);
	SceneGame::setKingTowerPos(Vector2f(KING_POS_X, KING_POS_Y));
	SceneGame::setTowersPos(TOWERS_POS, TOWERS_COUNT);
	setUpWaypoints();
	SceneGame::setDemonStartPos(Vector2f(DEMON_START_POS_X, DEMON_START_POS_Y));
	SceneGame::init();

	return true;
}

void SceneLevel1::setUpWaypoints()
{
	Waypoint* waypoints = new Waypoint[WAYPOINTS_COUNT];
	for (int i = 0; i < WAYPOINTS_COUNT; i++)
	{
		if (i < WAYPOINTS_COUNT - 1)
			waypoints[i].setNextWaypoint(&waypoints[i + 1]);
		waypoints[i].setPosition(WAYPOINTS_POS[i][0], WAYPOINTS_POS[i][1]);
	}
	SceneGame::setWaypoints(waypoints, WAYPOINTS_COUNT);
}
