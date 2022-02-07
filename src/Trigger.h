#ifndef TRIGGER_H
#define TRIGGER_H

#include "Include.h"

class Trigger
{
	friend class MemoryManager;
protected:
	Trigger(Sequence* seq);
	void execute();
private:
	Sequence* mSequence;
};

#endif