#include "Spell.h"
#include "ContentPipeline.h"
#include "Scene.h"

const float Spell::DURATION = 5.0f;
const float Spell::ROTATION_TIME_MODIFIER = 15.0f;
const float Spell::ROTATION_SPEED_INCREASE_PER_SECOND = 5.0f;
const Color Spell::PLAGUE_COLOR = Color(96, 241, 76, 255);
const Color Spell::SACRED_LIGHT_COLOR = Color(214, 172, 2, 255);

Spell::Spell(const SpellType spelltype)
{
	this->spellType = spelltype;
	this->activeTime = 0;
	this->rotationSpeed = 0;
}

void Spell::init()
{
	setTexture(ContentPipeline::getInstance().getSpellTexture(spellType));
	rune.setTexture(ContentPipeline::getInstance().getRunesTexture());
	rune.setOrigin(rune.getLocalBounds().width / 2, rune.getLocalBounds().height / 2);
}

SpellType Spell::getSpellType() const
{
	return this->spellType;
}

void Spell::update()
{
	if (!isActive()) return;
	activeTime += Scene::getDeltaTime();
	if (activeTime >= DURATION)
	{
		deactivate();
		notifyAllObservers();
	}

	rotationSpeed += Scene::getDeltaTime() * ROTATION_SPEED_INCREASE_PER_SECOND;

	rune.rotate(Scene::applyDeltaTime((Scene::getDeltaTime() / ROTATION_TIME_MODIFIER) + rotationSpeed));
}

void Spell::draw(RenderWindow& renderWindow) const
{
	if (!isActive()) return;
	renderWindow.draw(rune);
	GameObject::draw(renderWindow);
}

void Spell::spawn(const Vector2f& position)
{
	setPosition(position);
	rune.setPosition(position);
	rotationSpeed = 0;
	activeTime = 0;
	activate();
	notifyAllObservers();
}

const Color Spell::getColor() const
{
	switch (spellType)
	{
		case sacredLight:
			return SACRED_LIGHT_COLOR;
			break;
		case plague:
			return PLAGUE_COLOR;
			break;
		default:
			Color::White;
			break;
	}
}
