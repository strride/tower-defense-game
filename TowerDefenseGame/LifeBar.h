#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class LifeBar
{
public:
	LifeBar(int health, const int actorHeight);
	void init();
	void removeHealth(const int amount);
	void draw(RenderWindow& renderWindow) const;
	void setPosition(const Vector2f& position);
	void show();
	void hide();
private:
	void update();
	int totalHealth;
	int currentHealth;
	int offset;
	Sprite redBar;
	Sprite greenBar;
	Vector2f position;

	bool isActive;

	static const int HEIGHT_OFFSET = 10;
};

