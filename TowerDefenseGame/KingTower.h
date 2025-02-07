#pragma once
#include "Tower.h"
#include "Constants.h"

class KingTower : public Tower
{
public:
	KingTower();
	void init();
	void notify(Subject* subject) override;
private:
	static const int HEALTH = 500;
	static const TowerType TOWER_TYPE = TowerType::king;
};

