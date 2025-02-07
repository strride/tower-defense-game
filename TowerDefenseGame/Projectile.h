#pragma once
#include "GameObject.h"
#include "Damageable.h"
#include "Constants.h"
#include "Subject.h"

class Projectile : public GameObject
{
public:
	Projectile(const int speed, const int minDamage, const int maxDamage, const ProjectileType type);
	virtual void init();
	void spawn(const Vector2f& position, Damageable* target);
	void update();
	ProjectileType getType() const;
private:
	int speed;
	int minDamage;
	int maxDamage;
	int calculateDamage() const;

	Damageable* target;
	Sound hitSound;
	ProjectileType type;
};

