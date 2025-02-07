#pragma once
#include "Projectile.h"
class Blast : public Projectile
{
public:
	Blast();
	void init() override;
private:
	static const int SPEED = 8;
	static const int MIN_DAMAGE = 1;
	static const int MAX_DAMAGE = 12;
	static const ProjectileType TYPE = ProjectileType::blast;
};

