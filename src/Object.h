#ifndef OBJECT_H
#define OBJECT_H

#include "Include.h"

class Object
{
	friend class MemoryManager;
protected:
	Object(World* world, Math::Vector3& pos, std::string& name = std::string(""));
	~Object();
	virtual bool initialize();
public:
	virtual void update(GameTime& gameTime);
	virtual void draw();

	Math::Vector3& getPosition();
	std::string getName();
protected:
	World*								mWorld;
	std::string							mName;
	Math::Vector3						mPosition;
};

#endif