#ifndef ANIMATION_STATE_H
#define ANIMATION_STATE_H

#include "Include.h"

class AnimationState
{
public:	
	AnimationState(const char* stateName);
	~AnimationState();

	void addFrame(Model* model, Texture* texture);

	AnimationFrame* getFrame(unsigned int index);
private:
	std::string						mName;
	std::vector<AnimationFrame*>	mFrames;
	AnimationFrame*					mFirstFrame;
	AnimationFrame*					mPrevFrame;
};

#endif