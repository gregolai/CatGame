#ifndef BOX_3_H
#define BOX_3_H

#include "Math.h"
#include "Vector3.h"

namespace Math
{
	class Box3
	{
	public:
		float left;
		float top;
		float right;
		float bottom;
		float front;
		float back;

		inline Box3(float _left = 0, float _bottom = 0, float _front = 0, float _right = 0, float _top = 0, float _back = 0)
			: left(_left), bottom(_bottom), front(_front), right(_right), top(_top), back(_back)
		{
		}
	
		inline Math::Vector3 getCenter()
		{
			return Math::Vector3(left + (right-left)*0.5f, bottom + (top-bottom)*0.5f, front + (back-front)*0.5f);
		}

		inline float getWidth()
		{
			return (right-left);
		}

		inline float getHeight()
		{
			return (top-bottom);
		}

		inline float getLength()
		{
			return (back-front);
		}

		void draw(float r = 1.0f, float g = 1.0f, float b = 1.0f)
		{
			glDisable(GL_DEPTH_TEST);
			glDisable(GL_LIGHTING);

			glColor3f(r, g, b);
			glLineWidth(2.0f);
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			glBegin(GL_QUADS);
				//LEFT FACE
				glVertex3f(left, bottom, front);
				glVertex3f(left, top, front);
				glVertex3f(left, top, back);
				glVertex3f(left, bottom, back);

				//RIGHT FACE
				glVertex3f(right, bottom, front);
				glVertex3f(right, top, front);
				glVertex3f(right, top, back);
				glVertex3f(right, bottom, back);

				//FRONT FACE
				glVertex3f(left, bottom, front);
				glVertex3f(left, top, front);
				glVertex3f(right, top, front);
				glVertex3f(right, bottom, front);

				//BACK FACE
				glVertex3f(left, bottom, back);
				glVertex3f(left, top, back);
				glVertex3f(right, top, back);
				glVertex3f(right, bottom, back);

			glEnd();

			glEnable(GL_DEPTH_TEST);
			glEnable(GL_LIGHTING);
		}
	};
}

#endif