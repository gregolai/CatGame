#ifndef ANIMATION_H
#define ANIMATION_H

#include "Include.h"

class Animation
{
public:
	Animation(AnimationData* data);
	~Animation();

	bool setState(const char* newStateName);

	void incFrame();
	void decFrame();

	Model* getModel();
	Texture* getTexture();
private:
	AnimationData*								mAnimData;
	AnimationState*								mCurState;
	AnimationFrame*								mCurFrame;
};

#endif