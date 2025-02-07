#include "Blast.h"
#include "ContentPipeline.h"
Blast::Blast() : Projectile(SPEED, MIN_DAMAGE, MAX_DAMAGE, TYPE)
{
}

void Blast::init()
{
	setTexture(ContentPipeline::getInstance().getBlastTexture());
	Projectile::init();
}
