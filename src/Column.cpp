#include "Include.h"
#include "Column.h"
#include "Game.h"

Column::Column(World* world, int x, int z)
{
	mWorld		= world;
	mX			= x;
	mZ			= z;
	
	float xw	= x * COLUMN_WIDTH;
	float zw	= z * COLUMN_WIDTH;
	mBox		= Math::Box2(xw, zw, xw + COLUMN_WIDTH, zw + COLUMN_WIDTH);
	
	Math::Vector2 cbox = mBox.getCenter();
	mCenter		= Math::Vector3(cbox.x, 0, cbox.y);
}

Column::~Column()
{
}

bool Column::initialize()
{
	return true;
}

void Column::update(GameTime& gameTime)
{
	size_t sz = mObjects.size();
	for(size_t i=0; i<sz; ++i) {
		mObjects[i]->update(gameTime);
	}
}

void Column::draw()
{
	size_t sz = mObjects.size();
	for(size_t i=0; i<sz; ++i) {
		mObjects[i]->draw();
	}
}

void Column::insertObject(StaticObject* obj)
{
	mObjects.push_back(obj);
}

StaticObject* Column::checkCollisions(Math::Vector3& v)
{
	size_t sz = mObjects.size();
	StaticObject* obj;
	float h;
	float y;
	for(size_t i=0; i<sz; ++i) {
		obj = mObjects[i];
		if(obj->collides()) {
			y = obj->getPosition().y;
			h = obj->getCollisionHeight();			
			if(Math::between<float>(v.y, y, y+h)) {
				return obj;
			}
		}
	}
	return NULL;
}

int Column::getTileX()
{
	return mX;
}

int Column::getTileZ()
{
	return mZ;
}

float Column::getUnitLeft()
{
	return mBox.left;
}

float Column::getUnitRight()
{
	return mBox.right;
}

float Column::getUnitFront()
{
	return mBox.bottom;
}

float Column::getUnitBack()
{
	return mBox.top;
}

Math::Vector3& Column::getCenter()
{
	return mCenter;
}