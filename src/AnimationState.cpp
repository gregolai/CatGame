#include "Include.h"
#include "AnimationState.h"
#include "Game.h"

AnimationState::AnimationState(const char* stateName)
{
	mName			= stateName;
	mFrames			= std::vector<AnimationFrame*>();
	mFirstFrame		= NULL;
	mPrevFrame		= NULL;
}

AnimationState::~AnimationState()
{
	size_t sz = mFrames.size();
	for(size_t i=0; i<sz; ++i) {
		delete mFrames[i];
	}
}

void AnimationState::addFrame(Model* model, Texture* texture)
{
	AnimationFrame* frame = new AnimationFrame(model, texture);

	if(!mFirstFrame) {
		mFirstFrame = frame;
		mPrevFrame = frame;
	}

	frame->setNext(mFirstFrame);
	frame->setPrev(mPrevFrame);
	mPrevFrame->setNext(frame);
	mFirstFrame->setPrev(frame);

	mFrames.push_back(frame);

	mPrevFrame = frame;
}

AnimationFrame* AnimationState::getFrame(unsigned int index)
{
	size_t sz = mFrames.size();
	if(sz == 0) {
		log_error(STR("No frames found in state: ") + mName);
		return NULL;
	}
	if(index >= sz) {
		log_info(STR("Frame out of bound. Setting to last frame in state: ") + mName);
		index = sz - 1;
	}
	return mFrames[index];
}