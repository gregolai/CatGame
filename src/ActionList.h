#ifndef ACTION_LIST_H
#define ACTION_LIST_H

#include "Include.h"

class ActionList
{
public:
	ActionList(Object* obj, Sequence* seq);
	~ActionList();
	void insertAction(Action* act);
private:
	Object*					mObject;
	Sequence*				mSequence;
	std::vector<Action*>	mActions;
};

#endif