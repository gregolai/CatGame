#ifndef ACTION_H
#define ACTION_H

#include "Include.h"

class Action
{
public:
	Action(ActionType type, Object* target);
	
	void setNext(Action* next);

	ActionType getType();
	Object* getTarget();
private:
	Action*			mNext;
	ActionType		mType;
	Object*			mTarget;
};

class ActionANI : public Action
{
public:
	ActionANI(Object* target, AnimationState* state, bool loop);
private:
	AnimationState*		mAnimState;
	bool				mLoop;
};

class ActionCOLLIDE : public Action
{
public:
	ActionCOLLIDE(Object* target, bool on);
private:
	bool mOn;
};

class ActionCONTINUE : public Action
{
public:
	ActionCONTINUE(Object* target, Object* other);
private:
	Object* mOther;
};

class ActionGO : public Action
{
public:
	ActionGO(Object* target, Waypoint* waypoint);
private:
	Waypoint* mWaypoint;
};

class ActionROT : public Action
{
public:
	ActionROT(Object* target, Math::Degree& angle);
private:
	Math::Degree mAngle;
};

class ActionSPEED : public Action
{
public:
	ActionSPEED(Object* target, float multiplier);
private:
	float mMultiplier;
};

class ActionSTART : public Action
{
public:
	ActionSTART(Object* target, Object* other, ActionList* actList);
private:
	Object* mOther;
	ActionList* mActionList;
};

class ActionTO : public Action
{
public:
	ActionTO(Object* target, Waypoint* waypoint);
private:
	Waypoint* mWaypoint;
};

class ActionWAIT : public Action
{
public:
	ActionWAIT(Object* target, float timeUnits);
private:
	float mTimeUnits;
};

#endif