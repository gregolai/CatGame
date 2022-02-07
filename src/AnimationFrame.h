#ifndef ANIMATION_FRAME_H
#define ANIMATION_FRAME_H

#include "Include.h"

class AnimationFrame
{
	friend class AnimationState;
private:
	AnimationFrame(Model* model, Texture* texture);

	void setNext(AnimationFrame* frame);
	void setPrev(AnimationFrame* frame);
public:
	Model* getModel();
	Texture* getTexture();
	AnimationFrame* getNext();
	AnimationFrame* getPrev();
private:
	Model*				mModel;
	Texture*			mTexture;
	AnimationFrame*		mNext;
	AnimationFrame*		mPrev;
};

#endif