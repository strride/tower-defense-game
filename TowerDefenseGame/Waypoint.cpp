#include "Waypoint.h"
#include "ContentPipeline.h"

Waypoint::Waypoint()
{
	nextWaypoint = nullptr;
	nextWaypoint2 = nullptr;
}

void Waypoint::init()
{
	Sprite::setTexture(ContentPipeline::getInstance().getWaypointTexture());
}

void Waypoint::setNextWaypoint(Waypoint* next) 
{
	nextWaypoint = next;
}

void Waypoint::setNextWaypoint(Waypoint* next, Waypoint* next2)
{
	nextWaypoint = next;
	nextWaypoint2 = next2;
}

void Waypoint::draw(RenderWindow& renderWindow) const
{
	renderWindow.draw(*this);
}

Waypoint* Waypoint::getNextWaypoint() const 
{
	if (nextWaypoint2 == nullptr)
	{
		return nextWaypoint;
	}
	else
	{
		if (rand() % 2 == 1) 
		{
			return nextWaypoint;
		}
		else 
		{
			return nextWaypoint2;
		}
	}
}