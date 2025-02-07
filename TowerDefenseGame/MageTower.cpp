#include "MageTower.h"
#include "ContentPipeline.h"
#include "Scene.h"
#include <iostream>
#include "SceneGame.h"

std::vector<Blast*> MageTower::blasts;
const float MageTower::ATTACK_SPEED = 1.5f;
const float MageTower::SECONDS_PER_FRAME = 0.15f;

MageTower::MageTower() : AttackTower(HEALTH, TOWER_TYPE)
{
	Subject::addObserver(this);
	this->sacredLightSpell = nullptr;
}

MageTower::~MageTower()
{
	delete[] imagesFire;
}


void MageTower::setTarget(Damageable* target)
{
	if (this->target != nullptr) return;
	this->target = target;
}

void MageTower::init()
{
	target = nullptr;
	setTexture(ContentPipeline::getInstance().getTowerTexture(TOWER_TYPE));
	blastSound.setBuffer(ContentPipeline::getInstance().getMageAttackSoundBuffer());
	blastSound.setVolume(20);
	GameObject::setCollisionCircleRadius(MAGE_WIDTH / 4);

	imagesFire = new IntRect[IMAGES_SHOOT_COUNT];

	imageIdle.left = 0;
	imageIdle.top = 0;
	imageIdle.height = MAGE_HEIGHT;
	imageIdle.width = MAGE_WIDTH;

	for (int i = 0; i < IMAGES_SHOOT_COUNT; i++)
	{
		imagesFire[i].top = 0;
		imagesFire[i].left = i * MAGE_WIDTH;
		imagesFire[i].height = MAGE_HEIGHT;
		imagesFire[i].width = MAGE_WIDTH;
	}

	setTextureRect(imageIdle);
	setOrigin(MAGE_WIDTH / 2, MAGE_HEIGHT / 2);
	Tower::init();
}


void MageTower::update()
{
	if(!GameObject::isActive()) return;

	blastShot += Scene::getDeltaTime();

	if (sacredLightSpell != nullptr) 
	{
		blastShot += Scene::getDeltaTime();
	}
	if (blastShot >= ATTACK_SPEED && target != nullptr && !isShooting) 
	{
		if (target->isAlive() && this->getDistanceFrom(*target) <= SceneGame::MAX_ATTACK_DISTANCE) 
		{
			isShooting = true;
		}
		else 
		{
			target = nullptr;
		}
	}
	runAnimation();
}

void MageTower::spawn(const Vector2f& position)
{
	blastShot = 0;
	animTime = 0;
	currentAnim = 0;
	isShooting = false;
	target = nullptr;
	sacredLightSpell = nullptr;
	Tower::spawn(position);
}

void MageTower::notify(Subject* subject)
{
	if (!isActive()) return;
	if (typeid(*subject) == typeid(Spell))
	{
		Spell* spell = dynamic_cast<Spell*>(subject);
		if (getDistanceFrom(*spell) > Spell::RANGE) return;
		else if (spell->getSpellType() == sacredLight)
		{
			if (sacredLightSpell == spell) sacredLightSpell = nullptr;
			else if (spell->isActive()) sacredLightSpell = spell;
		}
	}
	Tower::notify(subject);
}

void MageTower::runAnimation()
{
	animTime += Scene::getDeltaTime();

	if (animTime >= SECONDS_PER_FRAME && isShooting)
	{
		animTime = 0;

		if (++currentAnim == IMAGES_SHOOT_COUNT) 
		{
			shoot();
			isShooting = false;
			currentAnim = 0;
			setTextureRect(imageIdle);
		}
		else 
		{
			setTextureRect(imagesFire[currentAnim]);
		}
	}
}

void MageTower::shoot()
{
	Blast* blast = nullptr;
	for (int i = 0; i < blasts.size(); i++)
	{
		if (!blasts[i]->isActive()) 
		{
			blast = blasts[i];
			break;
		}
	}
	if (blast == nullptr) 
	{
		blast = new Blast();
		blast->init();
		blasts.push_back(blast);
	}
	isShooting = true;
	blast->spawn(getPosition(), target);
	blastSound.play();
	blastShot = 0;
}
