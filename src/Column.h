#ifndef COLUMN_H
#define COLUMN_H

#include "Include.h"

class Column
{
	friend class World;
private:
	Column(World* world, int x, int z);
	~Column();
	bool initialize();
	void update(GameTime& gameTime);
	void draw();
	void insertObject(StaticObject* obj);	
public:
	StaticObject* checkCollisions(Math::Vector3& v);

	int getTileX();
	int getTileZ();
	float getUnitLeft();
	float getUnitRight();
	float getUnitFront();
	float getUnitBack();
	Math::Vector3& getCenter();
private:
	World*							mWorld;
	int								mX;
	int								mZ;
	Math::Box2						mBox;
	Math::Vector3					mCenter;
	std::vector<StaticObject*>		mObjects;
};

#endif