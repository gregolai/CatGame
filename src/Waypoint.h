#ifndef WAYPOINT_H
#define WAYPOINT_H

#include "Include.h"
#include "Object.h"

class Waypoint : public Object
{
	friend class MemoryManager;
private:
	Waypoint(World* world, int id, Column* col, float elev);
	~Waypoint();
private:
	int mId;
};

#endif