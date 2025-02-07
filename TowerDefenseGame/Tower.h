#pragma once
#include "Damageable.h"
#include "Constants.h"
#include "Subject.h"
#include "IObserver.h"
#include "LifeBar.h"
#include "Spell.h"

class Tower : public Damageable, public Subject, public IObserver
{
public:
	Tower(const int health, const TowerType towerType);
	virtual void init();
	void draw(RenderWindow& renderWindow) const override;
	TowerType getType() const;
	virtual void spawn(const Vector2f& position);
	void takeDamage(int damage) override;
	virtual void notify(Subject* subject);
	bool isAlive() const override;
	int getHealth() const override;
private:
	static const int ACTOR_HEIGHT = 150;
	static const int MIN_HEALTH_BONUS = 6;
	static const int MAX_HEALTH_BONUS = 15;
	static const int MIN_HEALTH_PENALTY = 1;
	static const int MAX_HEALTH_PENALTY = 10;
	
	int startingHealth;
	int health;
	TowerType towerType;
	LifeBar lifeBar;
	Spell* plagueSpell;
	Spell* sacredLightSpell;
	bool alive;
};