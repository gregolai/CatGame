#ifndef KITTY_H
#define KITTY_H

#include "Include.h"
#include "Animable.h"
#include "Object.h"

class Kitty : public Animable, public Object
{
	friend class MemoryManager;
private:
	Kitty(World* world, AnimationData* animData);
	~Kitty();
	bool initialize();
public:
	void update(GameTime& gameTime);
	void draw();

	void setHeading(Math::Degree& heading);

	Math::Vector3& getPosition();
	Math::Degree& getHeading();
	Math::Vector3& getVelocity();
	float getStamina();
private:
	void updateAnimation(GameTime& gameTime);
	void updateStamina(GameTime& gameTime);
	void updateCollisions(GameTime& gameTime);

	void updatePointCollision(Math::Vector3& PT, Math::Vector3& prevPT);

	KittyState				mKittyState;

	Math::Degree			mHeading;
	Math::Vector3			mScale;

	Math::Vector3			mPrevPosition;
	Math::Degree			mPrevHeading;
	Math::Box3				mBoundingBox;
	Math::Vector3			mVelocity;
	bool					mGrounded;
	float					mAnimSwapTime;
	float					mLastAnimTime;
	float					mStamina;
};

#endif