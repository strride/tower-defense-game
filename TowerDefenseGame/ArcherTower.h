#pragma once
#include "AttackTower.h"
#include "Arrow.h"
#include "Spell.h"

class ArcherTower : public AttackTower
{
public:
	ArcherTower();
	void setTarget(Damageable* target) override;
	void shoot();
	void init();
	void update() override;
	void spawn(const Vector2f& position) override;
	void notify(Subject* subject) override;
	static std::vector<Arrow*> arrows;
private:
	static const int HEALTH = 250;
	static const float ATTACK_SPEED; // = 0.8f;
	static const ProjectileType PROJECTILE_TYPE = ProjectileType::arrow;
	static const TowerType TOWER_TYPE = TowerType::archer;

	Damageable* target;
	float arrowShot;
	bool isShooting;
	Sound arrowSound;
	Spell* sacredLightSpell;
};