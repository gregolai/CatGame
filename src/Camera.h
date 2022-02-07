#ifndef CAMERA_H
#define CAMERA_H

#include "Include.h"

class Camera
{
public:
	Camera(Math::Degree& rotElev, Math::Degree& rotX, Math::Degree& rotY, float zoom);
	~Camera();

	void apply();
	Math::Vector3 getPosition();

	void setRotElev(Math::Degree& newRotElev);
	void setRotX(Math::Degree& newRotX);
	void setRotY(Math::Degree& newRotY);
	void setZoom(float newZoom);

	Math::Degree getRotElev();
	Math::Degree getRotX();
	Math::Degree getRotY();
	float getZoom();
private:
	Math::Degree		mRotElev;
	Math::Degree		mRotX;
	Math::Degree		mRotY;
	float				mZoom;
};

#endif