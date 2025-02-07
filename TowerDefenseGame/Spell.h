#pragma once
#include "GameObject.h"
#include "Subject.h"
#include "Constants.h"

class Spell : public GameObject, public Subject
{
public:
	Spell(const SpellType spelltype);
	void init();
	SpellType getSpellType() const;
	void update();
	void draw(RenderWindow& renderWindow) const override;
	void spawn(const Vector2f& position);
	const Color getColor() const;
	static const int RANGE = 400;
private:
	static const float DURATION; // = 5.0f;
	static const float ROTATION_TIME_MODIFIER; // = 15.0f;
	static const float ROTATION_SPEED_INCREASE_PER_SECOND; // = 5.0f;
	static const Color PLAGUE_COLOR; // = Color(96, 241, 76, 255);
	static const Color SACRED_LIGHT_COLOR; // = Color(214, 172, 2, 255);

	SpellType spellType;
	Sprite rune;
	float activeTime;
	float rotationSpeed;
};

