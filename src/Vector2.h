#ifndef MATH_VECTOR2_H
#define MATH_VECTOR2_H

#include "Math.h"

namespace Math
{

	class Vector2
	{
	public:
		// special points
		static const Vector2 ZERO;
		static const Vector2 UNIT_X;
		static const Vector2 UNIT_Y;
		static const Vector2 NEGATIVE_UNIT_X;
		static const Vector2 NEGATIVE_UNIT_Y;
		static const Vector2 UNIT_SCALE;

		float x;
		float y;

		inline Vector2()
			: x(0), y(0)
		{
		}

		inline Vector2(float _x, float _y)
			: x(_x), y(_y)
		{
		}

		inline Vector2(Vector2& rhs)
			: x(rhs.x), y(rhs.y)
		{
		}

		inline Vector2& operator=(Vector2& rhs)
		{
			x = rhs.x;
			y = rhs.y;
			return *this;
		}

		inline bool operator==(Vector2& rhs)
		{
			return (x == rhs.x && y == rhs.y);
		}

		inline bool operator!=(Vector2& rhs)
		{
			return (x != rhs.x || y != rhs.y);
		}

		inline Vector2 operator+(Vector2& rhs)
		{
			return Vector2(x + rhs.x, y + rhs.y);
		}

		inline Vector2 operator-(Vector2& rhs)
		{
			return Vector2(x - rhs.x, y - rhs.y);
		}

		inline Vector2 operator*(float scalar)
		{
			return Vector2(x * scalar, y * scalar);
		}

		inline Vector2 operator*(Vector2& rhs)
		{
			return Vector2(x * rhs.x, y * rhs.y);
		}

        inline friend Vector2 operator*(float scalar, Vector2& rhs)
        {
            return Vector2(scalar * rhs.x, scalar * rhs.y);
        }

		inline Vector2 operator/(float scalar)
		{
			if(scalar == 0) {
				return Vector2(C_POS_INFINITY, C_POS_INFINITY);
			} else {
				float inv = 1.0f / scalar;
				return Vector2(x * inv, y * inv);
			}
		}

		inline Vector2 operator/(Vector2& rhs)
		{
			float newX, newY;

			if(rhs.x == 0)
				newX = C_POS_INFINITY;
			else
				newX = x * (1.0f / rhs.x);

			if(rhs.y == 0)
				newY = C_POS_INFINITY;
			else
				newY = y * (1.0f / rhs.y);
			
			return Vector2(newX, newY);
		}

        inline friend Vector2 operator/(float scalar, Vector2& rhs)
        {
			float newX, newY;

			if(rhs.x == 0)
				newX = C_POS_INFINITY;
			else
				newX = scalar * (1.0f / rhs.x);

			if(rhs.y == 0)
				newY = C_POS_INFINITY;
			else
				newY = scalar * (1.0f / rhs.y);

            return Vector2(newX, newY);
        }

		inline Vector2 operator-()		//negate
		{
			return Vector2(-x, -y);
		}

		inline Vector2& operator+=(float scalar)
		{
			x += scalar;
			y += scalar;
			return *this;
		}

		inline Vector2& operator+=(Vector2& rhs)
		{
			x += rhs.x;
			y += rhs.y;
			return *this;
		}

		inline Vector2& operator-=(float scalar)
		{
			x -= scalar;
			y -= scalar;
			return *this;
		}

		inline Vector2& operator-=(Vector2& rhs)
		{
			x -= rhs.x;
			y -= rhs.y;
			return *this;
		}

		inline Vector2& operator*=(float scalar)
		{
			x *= scalar;
			y *= scalar;
			return *this;
		}

		inline Vector2& operator*=(Vector2& rhs)
		{
			x *= rhs.x;
			y *= rhs.y;
			return *this;
		}

		inline Vector2& operator/=(float scalar)
		{
			if(scalar == 0) {
				x = C_POS_INFINITY;
				y = C_POS_INFINITY;
			} else {
				float inv = 1.0f / scalar;
				x *= inv;
				y *= inv;
			}
			return *this;
		}

		inline Vector2& operator /= (Vector2& rhs)
		{
			if(rhs.x == 0)
				x = C_POS_INFINITY;
			else
				x *= 1.0f / rhs.x;

			if(rhs.y == 0)
				y = C_POS_INFINITY;
			else
				y *= 1.0f / rhs.y;

			return *this;
		}

		inline float getLength()
		{
			return sqrt(x * x + y * y);
		}

		inline void setLength(float newLength)
		{
			normalise();
			x *= newLength;
			y *= newLength;
		}

		inline float getSquaredLength()
		{
			return x * x + y * y;
		}

		inline float distance(Vector2& rhs)
		{
			float diffX = rhs.x - x;
			float diffY = rhs.y - y;
			return sqrt(diffX * diffX + diffY * diffY);
		}

		inline float squaredDistance(Vector2& rhs)
		{
			float diffX = rhs.x - x;
			float diffY = rhs.y - y;
			return diffX * diffX + diffY * diffY;
		}

		inline float dotProduct(Vector2& rhs)
		{
			return x * rhs.x + y * rhs.y;
		}


		inline float normalise()
		{
			float len = sqrt(x * x + y * y);

			if (len != 0)
			{
				float inv = 1.0f / len;
				x *= inv;
				y *= inv;
			}
			return len;
		}

		inline Vector2 midPoint(Vector2& rhs)
		{
			return Vector2( (x+rhs.x)*0.5f,(y+rhs.y)*0.5f );
		}

		inline bool operator<(Vector2& rhs)
		{
			if(x < rhs.x && y < rhs.y)
				return true;
			return false;
		}		

		inline bool operator>(Vector2& rhs)
		{
			if( x > rhs.x && y > rhs.y )
				return true;
			return false;
		}

		inline void makeFloor(Vector2& rhs)
		{
			if( rhs.x < x ) x = rhs.x;
			if( rhs.y < y ) y = rhs.y;
		}

		inline void makeCeil(Vector2& rhs)
		{
			if( rhs.x > x ) x = rhs.x;
			if( rhs.y > y ) y = rhs.y;
		}

		inline Vector2 perpendicular()
		{
			return Vector2(-y, x);
		}

		inline float crossProduct(Vector2& rhs)
		{
			return x * rhs.y - y * rhs.x;
		}

		inline bool isNaN() const
		{
			return Math::isNaN(x) || Math::isNaN(y);
		}
	};



} //namespace Math

#endif

