#include "Include.h"
#include "Animable.h"
#include "Game.h"

Animable::Animable(AnimationData* animData)
{
	mAnimation = new Animation(animData);
}
Animable::~Animable()
{
	delete mAnimation;
}

void Animable::updateAnimation(GameTime& gameTime)
{
}

Animation* Animable::getAnimation()
{
	return mAnimation;
}