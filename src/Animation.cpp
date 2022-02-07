#include "Include.h"
#include "Animation.h"
#include "Game.h"

Animation::Animation(AnimationData* data)
{
	mAnimData = data;
	mCurState = NULL;
	mCurFrame = NULL;
}

Animation::~Animation()
{
}

bool Animation::setState(const char* newStateName)
{
	AnimationState* st = mAnimData->getState(newStateName);
	if(!st) {
		log_warning(STR("Unable to get state: ") + newStateName);
		return false;
	}

	AnimationFrame* fr = st->getFrame(0);
	if(!fr) {
		log_warning(STR("Unable to get frame 0 of state: ") + newStateName);
		return false;
	}

	mCurState = st;
	mCurFrame = fr;
	return true;
}

void Animation::incFrame()
{
	if(mCurFrame) {
		mCurFrame = mCurFrame->getNext();
	}
}
void Animation::decFrame()
{
	if(mCurFrame) {
		mCurFrame = mCurFrame->getPrev();
	}
}

Model* Animation::getModel()
{
	if(mCurFrame) {
		return mCurFrame->getModel();
	} else {
		return NULL;
	}
}

Texture* Animation::getTexture()
{
	if(mCurFrame) {
		return mCurFrame->getTexture();
	} else {
		return NULL;
	}
}