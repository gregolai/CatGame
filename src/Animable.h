#ifndef ANIMABLE_H
#define ANIMABLE_H

#include "Include.h"

class Animable
{
public:
	Animable(AnimationData* animData);
	~Animable();

	void updateAnimation(GameTime& gameTime);

	Animation* getAnimation();
protected:
	Animation* mAnimation;
};

#endif