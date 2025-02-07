#include "Fireball.h"
#include "ContentPipeline.h"

const float Fireball::FIRING_RATE = 1.05f;
const float Fireball::FIRING_RATE_WAVE_MODIFIER = 0.05f;

Fireball::Fireball() : Projectile(SPEED, MIN_DAMAGE, MAX_DAMAGE, TYPE)
{
}

void Fireball::init()
{
	setTexture(ContentPipeline::getInstance().getFireballTexture());
	Projectile::init();
}
