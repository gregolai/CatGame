#include "Include.h"
#include "Waypoint.h"
#include "Game.h"

Waypoint::Waypoint(World* world, int id, Column* col, float elev)
	: Object( world, Math::Vector3(col->getCenter().x, elev, col->getCenter().z) )
{
	mId = id;	
}

Waypoint::~Waypoint()
{
}

/*
void Waypoint::setNext(Waypoint* wp)
{
	mNext = wp;
}

bool Waypoint::isDone()
{
	return (mTween.timeExpired() && mDelay <= mDelayElapsed);
}

void Waypoint::addTime(float amount)
{
	if(mTween.timeExpired()) {
		mDelayElapsed += amount;
	} else {
		mTween.addTime(amount);
	}
}

Waypoint* Waypoint::getNext()
{
	return mNext;
}

Animation* Waypoint::getAnimation()
{
	return mWaypointData->getAnimation();
}

Column* Waypoint::getColumn()
{
	return mWaypointData->getColumn();
}
*/