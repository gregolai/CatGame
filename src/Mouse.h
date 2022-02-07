#ifndef MOUSE_H
#define MOUSE_H

#include "Include.h"
#include "Animable.h"
#include "Object.h"

class Mouse : public Animable, public Object
{
	friend class MemoryManager;
private:
	Mouse(World* world, AnimationData* animData, Math::Vector3& pos);
	~Mouse();
	bool initialize();
public:
	void update(GameTime& gameTime);
	void draw();
private:
	
};

#endif