#pragma once
#include "GameObject.h"
#include "AttackTower.h"
#include "IObserver.h"

class TowerEmplacement: public GameObject, public IObserver
{
public:
	TowerEmplacement();
	void setTower(AttackTower* tower);
	void init();
	void notify(Subject* subject) override;
private:
	AttackTower* tower;
};

