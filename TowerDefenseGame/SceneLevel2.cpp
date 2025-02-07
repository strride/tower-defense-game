#include "SceneLevel2.h"
#include <iostream>

SceneLevel2::SceneLevel2(RenderWindow& renderWindow, Event& event, int highscore, bool reset) : SceneGame(renderWindow, event, highscore, reset)
{
}

bool SceneLevel2::init()
{
	SceneGame::setMap(Maps::map2);
	SceneGame::setKingTowerPos(Vector2f(KING_POS_X, KING_POS_Y));
	SceneGame::setTowersPos(TOWERS_POS, NB_TOWERS);
	setUpWaypoints();
	SceneGame::setDemonStartPos(Vector2f(DEMON_START_POS_X, DEMON_START_POS_Y));
	SceneGame::init();

	return true;
}

void SceneLevel2::setUpWaypoints()
{
	Waypoint* waypoints = new Waypoint[NB_WAYPOINTS];
	for (int i = 0; i < NB_WAYPOINTS; i++)
	{
		if (i != PATH_TWO_END && i != PATH_ONE_END) 
		{
			if (i == DOUBLE_WAYPOINT)
				waypoints[i].setNextWaypoint(&waypoints[PATH_ONE_START], &waypoints[PATH_TWO_START]);
			else
				waypoints[i].setNextWaypoint(&waypoints[i + 1]);
		}
		waypoints[i].setPosition(WAYPOINTS_POS[i][0], WAYPOINTS_POS[i][1]);
	}
	SceneGame::setWaypoints(waypoints, NB_WAYPOINTS);
}


