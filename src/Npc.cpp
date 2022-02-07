#include "Include.h"
#include "Npc.h"
#include "Game.h"

Npc::Npc(World* world)
	: Object( world, Math::Vector3(0, 0, 0) )
{
	
}

void Npc::update(GameTime& gameTime)
{

}

void Npc::draw()
{
	/*
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
	*/
}