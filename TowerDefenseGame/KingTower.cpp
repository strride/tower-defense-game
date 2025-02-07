#include "KingTower.h"
#include "ContentPipeline.h"

KingTower::KingTower() : Tower(HEALTH, TOWER_TYPE)
{
	Subject::addObserver(this);
}

void KingTower::init()
{
	setTexture(ContentPipeline::getInstance().getTowerTexture(TOWER_TYPE));
	Tower::init();
}

void KingTower::notify(Subject* subject)
{
	Tower::notify(subject);
}
