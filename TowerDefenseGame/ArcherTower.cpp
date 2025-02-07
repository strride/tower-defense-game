#include "ArcherTower.h"
#include "ContentPipeline.h"
#include "Scene.h"
#include "SceneGame.h"
#include "Arrow.h"
#include <iostream>

std::vector<Arrow*> ArcherTower::arrows;

const float ArcherTower::ATTACK_SPEED = 0.8f;

ArcherTower::ArcherTower() : AttackTower(HEALTH, TOWER_TYPE)
{
	Subject::addObserver(this);
	this->sacredLightSpell = nullptr;
}

void ArcherTower::setTarget(Damageable* target)
{
	if (this->target != nullptr) return;
	this->target = target;
}

void ArcherTower::init()
{
	target = nullptr;
	setTexture(ContentPipeline::getInstance().getTowerTexture(TOWER_TYPE));
	arrowSound.setBuffer(ContentPipeline::getInstance().getArcherAttackSoundBuffer());
	arrowSound.setVolume(20);
	GameObject::setCollisionCircleRadius(GameObject::getTexture()->getSize().x / 4);

	setOrigin(GameObject::getTexture()->getSize().x / 2, GameObject::getTexture()->getSize().y / 2);
	Tower::init();
}

void ArcherTower::update()
{
	if (!GameObject::isActive()) return;
	shoot();
}

void ArcherTower::spawn(const Vector2f& position)
{
	arrowShot = 0;
	isShooting = false;
	target = nullptr;
	sacredLightSpell = nullptr;
	Tower::spawn(position);
}

void ArcherTower::notify(Subject* subject)
{
	if (!isActive()) return;
	if (typeid(*subject) == typeid(Spell))
	{
		Spell* spell = dynamic_cast<Spell*>(subject);
		if (getDistanceFrom(*spell) > Spell::RANGE) return;
		else if (spell->getSpellType() == sacredLight)
		{
			if (sacredLightSpell == spell) 
			{
				sacredLightSpell = nullptr;
			}
			else if (spell->isActive()) 
			{
				sacredLightSpell = spell;
			}
		}
	}
	Tower::notify(subject);
}

void ArcherTower::shoot()
{
	if (target == nullptr || !target->isAlive() || this->getDistanceFrom(*target) > SceneGame::MAX_ATTACK_DISTANCE) 
	{
		target = nullptr;
		return;
	}

	arrowShot += Scene::getDeltaTime();

	if (sacredLightSpell != nullptr) 
	{
		arrowShot += Scene::getDeltaTime();
	}

	if (arrowShot >= ATTACK_SPEED) 
	{
		Arrow* arrow = nullptr;
		for (int i = 0; i < arrows.size(); i++)
		{
			if (!arrows[i]->isActive()) 
			{
				arrow = arrows[i];
				break;
			}
		}
		if (arrow == nullptr) 
		{
			arrow = new Arrow();
			arrow->init();
			arrows.push_back(arrow);
		}
		isShooting = true;
		arrow->spawn(getPosition(), target);
		arrowSound.play();
		arrowShot = 0;
	}
}