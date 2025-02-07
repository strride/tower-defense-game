#pragma once
#include "GameObject.h"
class Damageable : public GameObject
{
public:
	virtual void takeDamage(int damage) = 0;
	virtual bool isAlive() const = 0;
	virtual int getHealth() const = 0;
};

