#ifndef BOX_2_H
#define ROX_2_H

#include "Math.h"
#include "Vector2.h"

namespace Math
{
	class Box2
	{
	public:
		float left;
		float top;
		float right;
		float bottom;

		inline Box2(float _left = 0, float _bottom = 0, float _right = 0, float _top = 0)
			: left(_left), bottom(_bottom), right(_right), top(_top)
		{
		}
	
		inline Math::Vector2 getCenter()
		{
			return Math::Vector2(left + (right-left)*0.5f, bottom + (top-bottom)*0.5f);
		}

		inline Math::Vector2 getTopLeft()
		{
			return Math::Vector2(left, top);
		}

		inline Math::Vector2 getBottomLeft()
		{
			return Math::Vector2(left, bottom);
		}

		inline Math::Vector2 getTopRight()
		{
			return Math::Vector2(right, top);
		}

		inline Math::Vector2 getBottomRight()
		{
			return Math::Vector2(right, bottom);
		}
	};
}

#endif