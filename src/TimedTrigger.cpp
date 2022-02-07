#include "Include.h"
#include "TimedTrigger.h"
#include "Game.h"

TimedTrigger::TimedTrigger(float timeOfDay, Sequence* seq)
	: Trigger(seq)
{
	mSequence = seq;
}