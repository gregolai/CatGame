#ifndef WORLD_TIME_H
#define WORLD_TIME_H

#include "Include.h"

class WorldTime
{
public:
	WorldTime(World* world);
	void update(GameTime& gameTime);

	void setTime(int hours, int minutes);

	int getTotalSeconds();
	int getTotalMinutes();
	int getTotalHours();

	int getMinutes();
	int getHours();

	float getPercentOfDay();
private:
	float mSeconds;
	int mMinutes;
	int mHours;
};

#endif