#include "Include.h"
#include "AnimationFrame.h"
#include "Game.h"

AnimationFrame::AnimationFrame(Model* model, Texture* texture)
{
	mModel			= model;
	mTexture		= texture;
	mNext			= NULL;
	mPrev			= NULL;
}

void AnimationFrame::setNext(AnimationFrame* frame)
{
	mNext = frame;
}

void AnimationFrame::setPrev(AnimationFrame* frame)
{
	mPrev = frame;
}

Model* AnimationFrame::getModel()
{
	return mModel;
}

Texture* AnimationFrame::getTexture()
{
	return mTexture;
}

AnimationFrame* AnimationFrame::getNext()
{
	return mNext;
}

AnimationFrame* AnimationFrame::getPrev()
{
	return mPrev;
}