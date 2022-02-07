#ifndef ANIMATION_DATA_H
#define ANIMATION_DATA_H

#include "Include.h"

class AnimationData
{
	friend class MemoryManager;
private:
	AnimationData();
	~AnimationData();
	AnimationData* loadFromFile(const char* filename);
public:
	AnimationState* getState(const char* stateName);
private:
	std::string								mName;
	std::map<std::string, AnimationState*>	mStates;
};

#endif