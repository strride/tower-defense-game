#include "LifeBar.h"
#include "ContentPipeline.h"

LifeBar::LifeBar(int health, const int actorHeight)
{
	this->totalHealth = health;
	this->offset = actorHeight / 2 + HEIGHT_OFFSET;
	this->isActive = false;
}

void LifeBar::init()
{
	redBar.setTexture(ContentPipeline::getInstance().getRedBarTexture());
	greenBar.setTexture(ContentPipeline::getInstance().getGreenBarTexture());
}

void LifeBar::removeHealth(const int amount)
{
	this->currentHealth -= amount;
	update();
}

void LifeBar::draw(RenderWindow& renderWindow) const
{
	if (!isActive) return;
	renderWindow.draw(redBar);
	renderWindow.draw(greenBar);
}

void LifeBar::setPosition(const Vector2f& position)
{
	redBar.setPosition(position.x - 25, position.y - offset);
	greenBar.setPosition(position.x - 25, position.y - offset);
}

void LifeBar::show()
{
	this->currentHealth = totalHealth;
	update();
	isActive = true;
}

void LifeBar::hide()
{
	isActive = false;
}

void LifeBar::update()
{
	float percentage = (float)currentHealth / totalHealth;
	greenBar.setScale(percentage, 1);
}
