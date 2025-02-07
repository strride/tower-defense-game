#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Waypoint : public Sprite
{
public:
	Waypoint();
	void init();
	Waypoint* getNextWaypoint() const;
	void setNextWaypoint(Waypoint* next);
	void setNextWaypoint(Waypoint* next, Waypoint* next2);
	void draw(RenderWindow& renderWindow) const;

private:
	Waypoint* nextWaypoint;
	Waypoint* nextWaypoint2;
};

