#include "Projectile.h"
#include "ContentPipeline.h"
#include "Scene.h"
Projectile::Projectile(const int speed, const int minDamage, const int maxDamage, const ProjectileType type)
{
	this->speed = speed;
	this->minDamage = minDamage;
	this->maxDamage = maxDamage;
	this->target = nullptr;
	this->type = type;
}

void Projectile::init()
{
	hitSound.setBuffer(ContentPipeline::getInstance().getHitSoundBuffer());
	hitSound.setVolume(20);
}

void Projectile::spawn(const Vector2f& position, Damageable* target)
{
	setPosition(position);
	this->target = target;
	activate();
}


void Projectile::update()
{
	if (!GameObject::isActive()) return;
	if (target == nullptr || !target->isActive())
	{
		deactivate();
		return;
	}
	if (this->isCircleColliding(*target)) 
	{
		target->takeDamage(calculateDamage());
		hitSound.play();
		deactivate();
		return;
	}

	float angle = atan2f(target->getPosition().y - getPosition().y, target->getPosition().x - getPosition().x);
	float xMod = cos(angle) * this->speed;
	float yMod = sin(angle) * this->speed;
	GameObject::move(Scene::applyDeltaTime(xMod), Scene::applyDeltaTime(yMod));
	GameObject::setRotationRadians(angle);
}

ProjectileType Projectile::getType() const
{
	return type;
}

int Projectile::calculateDamage() const
{
	return rand() % (maxDamage - minDamage + 1) + minDamage;
}
