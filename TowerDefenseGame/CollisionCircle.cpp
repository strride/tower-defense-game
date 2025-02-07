#include "CollisionCircle.h"
//#include <cmath>

CollisionCircle::CollisionCircle() : radius(0.0f), x(0.0f), y(0.0f)
{
}

CollisionCircle::CollisionCircle(const float radius, const float x, const float y) : radius(radius), x(x), y(y)
{
}

bool CollisionCircle::checkCollision(const CollisionCircle& otherCircle) const
{
	float lineX = this->x - otherCircle.x;
	float lineY = this->y - otherCircle.y;

	//Solution classique
	//float distance = sqrt(lineX * lineX + lineY * lineY);
	//float totalRadius = this->radius + otherCircle.radius;

	//� la place de faire la racine carr� de la distance, on met la somme des rayons des cercles au carr�; 
	//C'est �quivalent, c'est plus �conome en calcul (sqrt est exigeant) et ne de demande m�me pas l'inclusion de cmath.
	float distance = lineX * lineX + lineY * lineY;
	float totalRadius = this->radius + otherCircle.radius;
	totalRadius *= totalRadius;

	//Deux cercles qui se touchent ne sont pas consid�r�es en collision
	if (distance < totalRadius) return true;

	return false;
}

float CollisionCircle::getRadius() const
{
	return radius;
}

float CollisionCircle::getX() const
{
	return x;
}

float CollisionCircle::getY() const
{
	return y;
}

void CollisionCircle::setPosition(const float x, const float y)
{
	this->x = x;
	this->y = y;
}

void CollisionCircle::setRadius(const float radius)
{
	this->radius = radius;
}