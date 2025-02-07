#include "TowerEmplacement.h"
#include "ContentPipeline.h"

TowerEmplacement::TowerEmplacement()
{
	Subject::addObserver(this);
}

void TowerEmplacement::setTower(AttackTower* tower)
{
	this->tower = tower;
	deactivate();
}

void TowerEmplacement::init()
{
	GameObject::setTexture(ContentPipeline::getInstance().getTowerEmplacementTexture());
	GameObject::activate();
}

void TowerEmplacement::notify(Subject* subject) 
{
	if (subject == tower) activate();
}
