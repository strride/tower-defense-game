#include "Arrow.h"
#include "ContentPipeline.h"

Arrow::Arrow() : Projectile(SPEED, MIN_DAMAGE, MAX_DAMAGE, TYPE)
{
}

void Arrow::init()
{
	setTexture(ContentPipeline::getInstance().getArrowTexture());
	Projectile::init();
}
