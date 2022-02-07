#include "Include.h"
#include "Mouse.h"
#include "Game.h"

Mouse::Mouse(World* world, AnimationData* animData, Math::Vector3& pos)
	: Animable(animData), Object(world, pos)
{

}

Mouse::~Mouse()
{
}

bool Mouse::initialize()
{
	mAnimation->setState("idle");

	return true;
}

void Mouse::update(GameTime& gameTime)
{
	Kitty* cat = mWorld->getKitty();
	Math::Vector3 catPos = cat->getPosition();
	Math::Vector3 diffPos = mPosition - catPos;
	float dist = diffPos.getLength();
	if(dist < 10.0f) {

		mPosition += diffPos * ((10-dist)/10.0f) *(MAX_RUN_SPEED*0.3f) * gameTime.deltaTime;

	}

	updateAnimation(gameTime);
}



void Mouse::draw()
{
	Model* model = mAnimation->getModel();
	Texture* texture = mAnimation->getTexture();
	if(model && texture) {
		
		glPushMatrix();
			glTranslatef(mPosition.x, mPosition.y, mPosition.z);
			glScalef(0.9f, 0.9f, 0.9f);
			glBindTexture(GL_TEXTURE_2D, texture->getId());
			glCallList(model->getId());
			glBindTexture(GL_TEXTURE_2D, 0);
		glPopMatrix();

	}
}