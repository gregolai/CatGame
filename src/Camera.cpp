#include "Include.h"
#include "Camera.h"
#include "Game.h"

Camera::Camera(Math::Degree& rotElev, Math::Degree& rotX, Math::Degree& rotY, float zoom)
{
	mRotElev	= rotElev;
	mRotX		= rotX;
	mRotY		= rotY;
	mZoom		= zoom;
}

Camera::~Camera()
{
}

void Camera::apply()
{
	glRotatef(mRotElev.getValue(), 1, 0, 0);

	glTranslatef(0, 0, mZoom);								//translate camera away from world
	glRotatef(mRotX.getValue(), 1.0f, 0, 0);							//rotate world to an angle

	//minor adjustment to displace cat from center of camera
	glTranslatef(0, 0, 2 + 3 * (mZoom - MIN_ZOOM)/(MAX_ZOOM - MIN_ZOOM));	//translate camera to show cat at bottom on screen
	
	glRotatef(mRotY.getValue(), 0, 1, 0);								//rotation around the cat
}

Math::Vector3 Camera::getPosition()
{
	float q;
	float x, y, z;

	Kitty* cat = theGame->getWorld()->getKitty();
	Math::Vector3 catPos = cat->getPosition();
	float headingRad = (-cat->getHeading()).getRadians();

	q = cos(mRotX.getRadians()) * mZoom;
	y = -sin(mRotX.getRadians()) * mZoom;

	x = -sin(headingRad+mRotY.getRadians()) * q;
	z = cos(headingRad+mRotY.getRadians()) * q;


	return Math::Vector3(catPos.x, catPos.y, catPos.z) + Math::Vector3(x, y, z);
}

void Camera::setRotElev(Math::Degree& newRotElev)
{
	mRotElev = newRotElev;
	mRotElev = Math::clamp<float>(mRotElev.getValue(), MIN_ROT_ELEV, MAX_ROT_ELEV);
}

void Camera::setRotX(Math::Degree& newRotX)
{
	mRotX = newRotX;
	mRotX = Math::clamp<float>(mRotX.getValue(), MIN_ROT_X, MAX_ROT_X);
}
void Camera::setRotY(Math::Degree& newRotY)
{
	mRotY = newRotY;		
}
void Camera::setZoom(float newZoom)
{
	mZoom = newZoom;
}

Math::Degree Camera::getRotElev()
{
	return mRotElev;
}

Math::Degree Camera::getRotX()
{
	return mRotX;
}
Math::Degree Camera::getRotY()
{
	return mRotY;
}
float Camera::getZoom()
{
	return mZoom;
}