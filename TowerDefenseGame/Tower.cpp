#include "Tower.h"
#include "ContentPipeline.h"
#include <iostream>

Tower::Tower(const int health, TowerType towerType) : lifeBar(health, ACTOR_HEIGHT)
{
	this->health = health;
	this->startingHealth = health;
	this->towerType = towerType;
	this->plagueSpell = nullptr;
	this->sacredLightSpell = nullptr;
}

void Tower::init()
{
	lifeBar.init();
	this->alive = false;
}

void Tower::draw(RenderWindow& renderWindow) const
{
	lifeBar.draw(renderWindow);
	GameObject::draw(renderWindow);
}

TowerType Tower::getType() const
{
	return towerType;
}

void Tower::spawn(const Vector2f& position)
{
	lifeBar.setPosition(position);
	lifeBar.show();
	health = startingHealth;
	setPosition(position);
	this->alive = true;
	setColor(Color::White);
	plagueSpell = nullptr;
	sacredLightSpell = nullptr;
	activate();
}

void Tower::takeDamage(int damage)
{
	if (plagueSpell != nullptr) 
	{
		damage *= 2;
	}
	health -= damage;
	lifeBar.removeHealth(damage);
	if (health <= 0)
	{
		this->alive = false;
		notifyAllObservers();
		lifeBar.hide();
		deactivate();
	}
}

void Tower::notify(Subject* subject)
{
	if (!isActive()) return;
	if (typeid(*subject) == typeid(Spell))
	{
		Spell* spell = dynamic_cast<Spell*>(subject);
		if (getDistanceFrom(*spell) > Spell::RANGE) return;
		if (spell->getSpellType() == plague)
		{
			if (plagueSpell == spell) 
			{
				plagueSpell = nullptr;
				setColor(Color::White);
			}
			else if(spell->isActive())
			{
				takeDamage(rand() % (MAX_HEALTH_PENALTY - MIN_HEALTH_PENALTY + 1) + MIN_HEALTH_PENALTY);
				setColor(spell->getColor());
				plagueSpell = spell;
			}
		}
		else if (spell->getSpellType() == sacredLight)
		{
			if (sacredLightSpell == spell) 
			{
				sacredLightSpell = nullptr;
				setColor(Color::White);
			}
			else if(spell->isActive())
			{
				takeDamage(-(rand() % (MAX_HEALTH_BONUS - MIN_HEALTH_BONUS + 1) + MIN_HEALTH_BONUS));
				setColor(spell->getColor());
				sacredLightSpell = spell;
			}
		}
	}
}

bool Tower::isAlive() const
{
	return this->alive;
}

int Tower::getHealth() const
{
	return health;
}
