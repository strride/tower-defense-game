#pragma once
#include "AttackTower.h"
#include "Constants.h"
#include "Blast.h"
#include "Spell.h"
class MageTower : public AttackTower
{
public:
	MageTower();
	~MageTower();
	void init();
	void shoot();
	void setTarget(Damageable* target) override;
	void runAnimation();
	void update() override;
	void spawn(const Vector2f& position) override;
	void notify(Subject* subject) override;
	static std::vector<Blast*> blasts;
private:
	static const int HEALTH = 250;
	static const float ATTACK_SPEED; // = 1.5f;
	static const ProjectileType PROJECTILE_TYPE = ProjectileType::blast;
	static const TowerType TOWER_TYPE = TowerType::mage;
	static const int IMAGES_IDLE_COUNT = 1;
	static const int IMAGES_SHOOT_COUNT = 3;
	static const int MAGE_WIDTH = 150;
	static const int MAGE_HEIGHT = 150;
	static const float SECONDS_PER_FRAME; // = 0.15f;

	IntRect imageIdle;
	IntRect* imagesFire;

	float animTime;
	int currentAnim;

	enum Animation { FIRE, IDLE };
	Animation currentAnimation = Animation::IDLE;

	bool isShooting;
	Damageable* target;
	float blastShot;

	Sound blastSound;

	Spell* sacredLightSpell;
};

