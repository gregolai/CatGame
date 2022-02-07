#include "Include.h"
#include "Action.h"
#include "Game.h"

Action::Action(ActionType type, Object* target)
{
	mType			= type;
	mTarget			= target;
	mNext			= NULL;
}

void Action::setNext(Action* next)
{
	mNext = next;
}

ActionType Action::getType()
{
	return mType;
}

Object* Action::getTarget()
{
	return mTarget;
}

//ctor
ActionANI::ActionANI(Object* target, AnimationState* state, bool loop)
	: Action(ACTION_ANI, target)
{
	mAnimState	= state;
	mLoop		= loop;
}

//ctor
ActionCOLLIDE::ActionCOLLIDE(Object* target, bool on)
	: Action(ACTION_COLLIDE, target)
{
	mOn = on;
}

//ctor
ActionCONTINUE::ActionCONTINUE(Object* target, Object* other)
	: Action(ACTION_COLLIDE, target)
{
	mOther = other;
}

//ctor
ActionGO::ActionGO(Object* target, Waypoint* waypoint)
	: Action(ACTION_GO, target)
{
	mWaypoint = waypoint;
}

//ctor
ActionROT::ActionROT(Object* target, Math::Degree& angle)
	: Action(ACTION_ROT, target)
{
	mAngle = angle;
}

//ctor
ActionSPEED::ActionSPEED(Object* target, float multiplier)
	: Action(ACTION_SPEED, target)
{
	mMultiplier = multiplier;
}

//ctor
ActionSTART::ActionSTART(Object* target, Object* other, ActionList* actList)
	: Action(ACTION_START, target)
{
	mOther = other;
	mActionList = actList;
}

//ctor
ActionTO::ActionTO(Object* target, Waypoint* waypoint)
	: Action(ACTION_TO, target)
{
	mWaypoint = waypoint;
}

//ctor
ActionWAIT::ActionWAIT(Object* target, float timeUnits)
	: Action(ACTION_WAIT, target)
{
	mTimeUnits = timeUnits;
}