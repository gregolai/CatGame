#include "Include.h"
#include "WorldTime.h"
#include "Game.h"

WorldTime::WorldTime(World* world)
{
	mSeconds = 0;
	mMinutes = 0;
	mHours = 0;
}

void WorldTime::update(GameTime& gameTime)
{
	mSeconds += ( gameTime.deltaTime * SEC_PER_DAY / SEC_PER_WORLDDAY );
	if(mSeconds >= SEC_PER_DAY) {
		mSeconds -= SEC_PER_DAY;
	}
	mMinutes = (int)(mSeconds / 60);
	mHours = (int)(mMinutes / 60);
}

void WorldTime::setTime(int hours, int minutes)
{	
	hours = Math::clamp<int>(hours, 0, 23);
	minutes = Math::clamp<int>(minutes, 0, 59);

	mSeconds = (float)(hours * 3600 + minutes * 60);
	mMinutes = minutes;
	mHours = hours;
}

int WorldTime::getTotalSeconds()
{
	return (int)mSeconds;
}

int WorldTime::getTotalMinutes()
{
	return mMinutes;
}

int WorldTime::getTotalHours()
{
	return mHours;
}


int WorldTime::getMinutes()
{
	return mMinutes % 60;
}

int WorldTime::getHours()
{
	return mHours;
}

float WorldTime::getPercentOfDay()
{
	return mSeconds / SEC_PER_DAY;
}