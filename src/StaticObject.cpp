#include "Include.h"
#include "StaticObject.h"
#include "Game.h"

StaticObject::StaticObject(World* world, Model* model, Texture* texture, Column* col, float elev, Math::Degree& rot,
	Math::Vector3& scale, float collideHeight)
	: Object(world, Math::Vector3(col->getCenter().x, elev, col->getCenter().z))
{
	mRotation			= rot;
	mScale				= scale;
	mColumn				= col;
	mCollides			= (collideHeight <= 0 ? false : true);
	mCollisionHeight	= collideHeight;
	
	mModel				= model;
	mTexture			= texture;
}

StaticObject::~StaticObject()
{
}

bool StaticObject::initialize()
{
	bool ret = Object::initialize();
	return ret;
}

void StaticObject::draw()
{
	if(mModel && mTexture) {
		glPushMatrix();
			glTranslatef(mPosition.x, mPosition.y, mPosition.z);
			glRotatef(mRotation.getValue(), 0, 1, 0);
			glScalef(mScale.x, mScale.y, mScale.z);
			glBindTexture(GL_TEXTURE_2D, mTexture->getId());
			glCallList(mModel->getId());
			glBindTexture(GL_TEXTURE_2D, 0);
		glPopMatrix();
	}
}

bool StaticObject::collides()
{
	return mCollides;
}

float StaticObject::getCollisionHeight()
{
	return mCollisionHeight;
}

Model* StaticObject::getModel()
{
	return mModel;
}

