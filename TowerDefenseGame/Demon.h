#pragma once
#include "Damageable.h"
#include "Waypoint.h"
#include "Fireball.h"
#include "IObserver.h"
#include "LifeBar.h"
#include "Spell.h"

class Demon : public Damageable, public IObserver, public Subject
{
public:
	Demon();
	~Demon();
	void update();
	void init();
	void spawn(const Vector2f position, Waypoint* firstWaypoint);
	void draw(RenderWindow& renderWindow) const override;
	void takeDamage(int damage) override;
	void setTarget(Damageable* target);
	static std::vector<Fireball*> fireballs;
	void notify(Subject* subject) override;
	bool isAlive() const override;
	int getHealth() const override;

private:
	static const int MOVE_SPEED = 54;
	static const int MOVE_SPEED_WAVE_MODIFIER = 6;
	static const int HEALTH = 60;
	static const int ANIM_COUNT = 5;
	static const int DEMON_WIDTH = 100;
	static const int DEMON_HEIGHT = 50;
	static const float SECONDS_PER_FRAME; // = 0.1f;
	static const int MIN_LIGHT_PENALTY = 1;
	static const int MAX_LIGHT_PENALTY = 5;
	static const int MIN_PLAGUE_PENALTY = 1;
	static const int MAX_PLAGUE_PENALTY = 10;

	IntRect* imagesMove;
	IntRect* imagesDeath;

	float animTime;
	int currentAnim;
	int health;

	enum Animation { MOVE, DEATH };
	Animation currentAnimation = Animation::MOVE;

	float fireballShot;

	Waypoint* currentWaypoint;
	void move();
	float calculateSpeed() const;
	void runAnimation();
	void shoot();
	Damageable* target;
	LifeBar lifeBar;
	Sound demonAttackSound;
	Spell* plagueSpell;
	Spell* sacredLightSpell;
	bool alive;
};

