#pragma once
#include "Projectile.h"
class Fireball : public Projectile
{
public:
	Fireball();
	void init() override;
	static const float FIRING_RATE;
	static const float FIRING_RATE_WAVE_MODIFIER;
private:
	static const int SPEED = 10;
	static const int MIN_DAMAGE = 1;
	static const int MAX_DAMAGE = 10;
	static const ProjectileType TYPE = ProjectileType::fireball;

};

