#include "Include.h"
#include "Object.h"
#include "Game.h"

Object::Object(World* world, Math::Vector3& pos, std::string& name)
{
	mWorld				= world;
	mPosition			= pos;
	mName				= std::string(name);
}

Object::~Object()
{
}

bool Object::initialize()
{
	return true;
}

void Object::update(GameTime& gameTime)
{
}

void Object::draw()
{

}

Math::Vector3& Object::getPosition()
{
	return mPosition;
}

std::string Object::getName()
{
	return mName;
}