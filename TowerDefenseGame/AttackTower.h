#pragma once
#include "Tower.h"
#include "Constants.h"
#include "Projectile.h"
class AttackTower : public Tower
{
public:
	AttackTower(int health, const TowerType towerType);
	virtual void setTarget(Damageable* target) = 0;
	virtual void update() = 0;
};

