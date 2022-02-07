#ifndef STATIC_OBJECT_H
#define STATIC_OBJECT_H

#include "Include.h"
#include "Object.h"

class StaticObject : public Object
{
	friend class MemoryManager;
protected:
	StaticObject(World* world, Model* model, Texture* texture, Column* col, float elev, Math::Degree& rot,
		Math::Vector3& scale, float collideHeight);
	~StaticObject();
	virtual bool initialize();
public:
	virtual void draw();

	bool collides();
	float getCollisionHeight();
	Model* getModel();
private:
	Math::Degree			mRotation;
	Math::Vector3			mScale;
	Column*					mColumn;
	bool					mCollides;
	float					mCollisionHeight;
	Model*					mModel;
	Texture*				mTexture;
};

#endif