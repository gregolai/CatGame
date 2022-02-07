#ifndef NPC_H
#define NPC_H

#include "Include.h"
#include "Object.h"

class Npc : public Object
{
private:
	Npc(World* world);
public:
	void update(GameTime& gameTime);
	void draw();
	void setAction(Action* action);
protected:
	Action*		mAction;
};

#endif