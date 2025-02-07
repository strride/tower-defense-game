#include "Demon.h"
#include "Scene.h"
#include "SceneGame.h"
#include "ContentPipeline.h"
#include <iostream>
std::vector<Fireball*> Demon::fireballs;
const float Demon::SECONDS_PER_FRAME = 0.1f;

Demon::Demon() : lifeBar(HEALTH, DEMON_HEIGHT)
{
	Subject::addObserver(this);
	this->plagueSpell = nullptr;
	this->sacredLightSpell = nullptr;
}

Demon::~Demon()
{
	delete[] imagesDeath;
	delete[] imagesMove;
}

void Demon::init()
{
	lifeBar.init();

	setTexture(ContentPipeline::getInstance().getDemonTexture());

	demonAttackSound.setBuffer(ContentPipeline::getInstance().getDemonAttackSoundBuffer());
	demonAttackSound.setVolume(20);

	GameObject::setCollisionCircleRadius(DEMON_WIDTH / 4);

	imagesDeath = new IntRect[ANIM_COUNT];
	imagesMove = new IntRect[ANIM_COUNT];

	for (int i = 0; i < ANIM_COUNT; i++)
	{
		imagesMove[i].width = DEMON_WIDTH;
		imagesMove[i].height = DEMON_HEIGHT;
		imagesMove[i].left = i * DEMON_WIDTH;
		imagesMove[i].top = 0;

		imagesDeath[i].width = DEMON_WIDTH;
		imagesDeath[i].height = DEMON_HEIGHT;
		imagesDeath[i].left = i * DEMON_WIDTH;
		imagesDeath[i].top = DEMON_HEIGHT;
	}

	setTextureRect(imagesMove[0]);

	setOrigin(DEMON_WIDTH / 2, DEMON_HEIGHT / 2);

	this->alive = false;
}

void Demon::spawn(const Vector2f position, Waypoint* firstWaypoint)
{
	lifeBar.setPosition(position);
	lifeBar.show();
	animTime = 0;
	currentAnim = 0;
	health = HEALTH;
	fireballShot = 0;
	target = nullptr;
	setPosition(position);
	currentWaypoint = firstWaypoint;
	this->alive = true;
	setColor(Color::White);
	plagueSpell = nullptr;
	sacredLightSpell = nullptr;
	activate();
}

void Demon::draw(RenderWindow& renderWindow) const
{
	lifeBar.draw(renderWindow);
	GameObject::draw(renderWindow);
}

void Demon::takeDamage(int damage)
{
	if (plagueSpell != nullptr) 
	{
		damage *= 2;
	}
	health -= damage;
	lifeBar.removeHealth(damage);
	if (health <= 0 && alive)
	{
		lifeBar.hide();
		currentAnim = 0;
		this->alive = false;
		notifyAllObservers();
		currentAnimation = Animation::DEATH;
	}
}

void Demon::setTarget(Damageable* target)
{
	this->target = target;
}

void Demon::notify(Subject* subject)
{
	if (!isActive()) return;
	if (typeid(*subject) == typeid(Spell))
	{
		Spell* spell = dynamic_cast<Spell*>(subject);
		if (spell->getSpellType() == plague)
		{
			if (plagueSpell == spell) 
			{
				plagueSpell = nullptr;
				setColor(Color::White);
			}
			else if (spell->isActive() && getDistanceFrom(*spell) <= Spell::RANGE) 
			{
				takeDamage(rand() % (MAX_PLAGUE_PENALTY - MIN_PLAGUE_PENALTY + 1) + MIN_PLAGUE_PENALTY);
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
			else if (spell->isActive() && getDistanceFrom(*spell) <= Spell::RANGE) 
			{
				takeDamage((rand() % (MAX_LIGHT_PENALTY - MIN_LIGHT_PENALTY + 1) + MIN_LIGHT_PENALTY));
				setColor(spell->getColor());
				sacredLightSpell = spell;
			}
		}
	}
}

bool Demon::isAlive() const
{
	return this->alive;
}

int Demon::getHealth() const
{
	return health;
}

void Demon::update()
{
	if (!GameObject::isActive()) return;
	if (currentAnimation == Animation::MOVE) 
	{
		move();
		shoot();
	}
	runAnimation();
}

void Demon::move()
{
	if (currentWaypoint != nullptr && GameObject::getDistanceFrom(*currentWaypoint) < 1)
	{
		currentWaypoint = currentWaypoint->getNextWaypoint();
	}

	if (currentWaypoint == nullptr) return;

	float angle = atan2f(currentWaypoint->getPosition().y - getPosition().y, currentWaypoint->getPosition().x - getPosition().x);
	float xMod = cos(angle) * calculateSpeed();
	float yMod = sin(angle) * calculateSpeed();
	GameObject::move(xMod, yMod);
	lifeBar.setPosition(getPosition());
	GameObject::setScale(xMod > 0 ? 1 : -1, 1);
}

float Demon::calculateSpeed() const
{
	float moveSpeed = MOVE_SPEED + MOVE_SPEED_WAVE_MODIFIER * SceneGame::getWave();
	if (sacredLightSpell != nullptr) 
	{
		moveSpeed /= 2;
	}
	return moveSpeed * Scene::getDeltaTime();
}

void Demon::runAnimation()
{
	animTime += Scene::getDeltaTime();

	if (animTime >= SECONDS_PER_FRAME)
	{
		animTime = 0;

		if (++currentAnim == ANIM_COUNT) 
		{
			if (currentAnimation == Animation::MOVE) currentAnim = 0;
			else 
			{
				currentAnimation = Animation::MOVE;
				currentAnim = 0;
				deactivate();
			}
		}

		if (currentAnimation == Animation::MOVE) 
		{
			setTextureRect(imagesMove[currentAnim]);
		}
		else 
		{
			setTextureRect(imagesDeath[currentAnim]);
		}
	}
}

void Demon::shoot()
{
	if (target == nullptr || !target->isActive() || this->getDistanceFrom(*target) > SceneGame::MAX_ATTACK_DISTANCE) 
	{
		target = nullptr;
		return;
	}

	fireballShot += Scene::getDeltaTime();

	if (fireballShot >= Fireball::FIRING_RATE - Fireball::FIRING_RATE_WAVE_MODIFIER * SceneGame::getWave()) 
	{
		Fireball* fireball = nullptr;
		for (int i = 0; i < fireballs.size(); i++)
		{
			if (!fireballs[i]->isActive()) 
			{
				fireball = fireballs[i];
				break;
			}
		}
		if (fireball == nullptr) 
		{
			fireball = new Fireball();
			fireball->init();
			fireballs.push_back(fireball);
		}
		fireball->spawn(getPosition(), target);
		demonAttackSound.play();
		fireballShot = 0;
	}
}
