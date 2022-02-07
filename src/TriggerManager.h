#ifndef TRIGGER_MANAGER_H
#define TRIGGER_MANAGER_H

#include "Include.h"

class TriggerManager
{
public:
	TriggerManager();
	~TriggerManager();
private:
	std::set<Trigger*> mTriggers;
};

#endif