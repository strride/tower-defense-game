#pragma once
#include "Projectile.h"
class Arrow : public Projectile
{
public:
	Arrow();
	void init() override;
private:
	static const int SPEED = 15;
	static const int MIN_DAMAGE = 1;
	static const int MAX_DAMAGE = 4;
	static const ProjectileType TYPE = ProjectileType::arrow;
};

