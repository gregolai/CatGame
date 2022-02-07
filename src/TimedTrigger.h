#ifndef TIMED_TRIGGER_H
#define TIMED_TRIGGER_H

#include "Include.h"
#include "Trigger.h"

class TimedTrigger : public Trigger
{
public:
	TimedTrigger(float worldSeconds, Sequence* seq);
private:
	float		mWorldSeconds;
	Sequence*	mSequence;
};

#endif