#include "Include.h"
#include "ActionList.h"
#include "Game.h"

ActionList::ActionList(Object* obj, Sequence* seq)
{
	mObject		= obj;
	mSequence	= seq;
}

ActionList::~ActionList()
{
	size_t sz = mActions.size();
	for(size_t i=0; i<sz; ++i) {
		delete mActions[i];
	}
}

void ActionList::insertAction(Action* act)
{
	mActions.push_back(act);
}