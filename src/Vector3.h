#ifndef MATH_VECTOR3_H
#define MATH_VECTOR3_H

#include "Math.h"

namespace Math
{

	struct Vector3
	{
	public:
		// special points
		static const Vector3 ZERO;
		static const Vector3 UNIT_X;
		static const Vector3 UNIT_Y;
		static const Vector3 UNIT_Z;
		static const Vector3 NEGATIVE_UNIT_X;
		static const Vector3 NEGATIVE_UNIT_Y;
		static const Vector3 NEGATIVE_UNIT_Z;
		static const Vector3 UNIT_SCALE;

		float x;
		float y;
		float z;

		inline Vector3()
			: x(0), y(0), z(0)
		{
		}

		inline Vector3(float _x, float _y, float _z)
			: x(_x), y(_y), z(_z)
		{
		}

		inline Vector3(Vector3& rhs)
			: x(rhs.x), y(rhs.y), z(rhs.z)
		{
		}

		inline Vector3& operator=(Vector3& rhs)
		{
			x = rhs.x;
			y = rhs.y;
			z = rhs.z;
			return *this;
		}

		inline bool operator==(Vector3& rhs)
		{
			return (x == rhs.x && y == rhs.y && z == rhs.z);
		}

		inline bool operator!=(Vector3& rhs)
		{
			return (x != rhs.x || y != rhs.y || z != rhs.z);
		}

		inline Vector3 operator+(Vector3& rhs)
		{
			return Vector3(x + rhs.x, y + rhs.y, z + rhs.z);
		}

		inline Vector3 operator-(Vector3& rhs)
		{
			return Vector3(x - rhs.x, y - rhs.y, z - rhs.z);
		}

		inline Vector3 operator*(float scalar)
		{
			return Vector3(x * scalar, y * scalar, z * scalar);
		}

		inline Vector3 operator*(Vector3& rhs)
		{
			return Vector3(x * rhs.x, y * rhs.y, z * rhs.z);
		}

        inline friend Vector3 operator*(float scalar, Vector3& rhs)
        {
            return Vector3(scalar * rhs.x, scalar * rhs.y, scalar * rhs.z);
        }

		inline Vector3 operator/(float scalar)
		{
			if(scalar == 0) {
				return Vector3(C_POS_INFINITY, C_POS_INFINITY, C_POS_INFINITY);
			} else {
				float inv = 1.0f / scalar;
				return Vector3(x * inv, y * inv, z * inv);
			}
		}

		inline Vector3 operator/(Vector3& rhs)
		{
			float newX, newY, newZ;

			if(rhs.x == 0)
				newX = C_POS_INFINITY;
			else
				newX = x * (1.0f / rhs.x);

			if(rhs.y == 0)
				newY = C_POS_INFINITY;
			else
				newY = y * (1.0f / rhs.y);

			if(rhs.z == 0)
				newZ = C_POS_INFINITY;
			else
				newZ = z * (1.0f / rhs.z);
			
			return Vector3(newX, newY, newZ);
		}

        inline friend Vector3 operator/(float scalar, Vector3& rhs)
        {
			float newX, newY, newZ;

			if(rhs.x == 0)
				newX = C_POS_INFINITY;
			else
				newX = scalar * (1.0f / rhs.x);

			if(rhs.y == 0)
				newY = C_POS_INFINITY;
			else
				newY = scalar * (1.0f / rhs.y);

			if(rhs.z == 0)
				newZ = C_POS_INFINITY;
			else
				newZ = scalar * (1.0f / rhs.z);

            return Vector3(newX, newY, newZ);
        }

		inline Vector3 operator-()		//negate
		{
			return Vector3(-x, -y, -z);
		}

		inline Vector3& operator+=(float scalar)
		{
			x += scalar;
			y += scalar;
			z += scalar;
			return *this;
		}

		inline Vector3& operator+=(Vector3& rhs)
		{
			x += rhs.x;
			y += rhs.y;
			z += rhs.z;
			return *this;
		}

		inline Vector3& operator-=(float scalar)
		{
			x -= scalar;
			y -= scalar;
			z -= scalar;
			return *this;
		}

		inline Vector3& operator-=(Vector3& rhs)
		{
			x -= rhs.x;
			y -= rhs.y;
			z -= rhs.z;
			return *this;
		}

		inline Vector3& operator*=(float scalar)
		{
			x *= scalar;
			y *= scalar;
			z *= scalar;
			return *this;
		}

		inline Vector3& operator*=(Vector3& rhs)
		{
			x *= rhs.x;
			y *= rhs.y;
			z *= rhs.z;
			return *this;
		}

		inline Vector3& operator/=(float scalar)
		{
			if(scalar == 0) {
				x = C_POS_INFINITY;
				y = C_POS_INFINITY;
				z = C_POS_INFINITY;
			} else {
				float inv = 1.0f / scalar;
				x *= inv;
				y *= inv;
				z *= inv;
			}
			return *this;
		}

		inline Vector3& operator /= (Vector3& rhs)
		{
			if(rhs.x == 0)
				x = C_POS_INFINITY;
			else
				x *= 1.0f / rhs.x;

			if(rhs.y == 0)
				y = C_POS_INFINITY;
			else
				y *= 1.0f / rhs.y;

			if(rhs.z == 0)
				z = C_POS_INFINITY;
			else
				z *= 1.0f / rhs.z;

			return *this;
		}

		inline float getLength()
		{
			return sqrt(x * x + y * y + z * z);
		}

		inline void setLength(float newLength)
		{
			normalise();
			x *= newLength;
			y *= newLength;
			z *= newLength;
		}

		inline float getSquaredLength()
		{
			return x * x + y * y + z * z;
		}

		inline float distance(Vector3& rhs)
		{
			float diffX = rhs.x - x;
			float diffY = rhs.y - y;
			float diffZ = rhs.z - z;
			return sqrt(diffX * diffX + diffY * diffY + diffZ * diffZ);
		}

		inline float squaredDistance(Vector3& rhs)
		{
			float diffX = rhs.x - x;
			float diffY = rhs.y - y;
			float diffZ = rhs.z - z;
			return diffX * diffX + diffY * diffY + diffZ * diffZ;
		}

		inline float dotProduct(Vector3& rhs)
		{
			return x * rhs.x + y * rhs.y + z * rhs.z;
		}


		inline float normalise()
		{
			float len = sqrt(x * x + y * y + z * z);

			if (len != 0)
			{
				float inv = 1.0f / len;
				x *= inv;
				y *= inv;
				z *= inv;
			}
			return len;
		}

		inline Vector3 midPoint(Vector3& rhs)
		{
			return Vector3( (x+rhs.x)*0.5f, (y+rhs.y)*0.5f, (z+rhs.z)*0.5f );
		}

		inline bool operator<(Vector3& rhs)
		{
			if(x < rhs.x && y < rhs.y && z < rhs.z)
				return true;
			return false;
		}		

		inline bool operator>(Vector3& rhs)
		{
			if( x > rhs.x && y > rhs.y && z > rhs.z)
				return true;
			return false;
		}

		inline void makeFloor(Vector3& rhs)
		{
			if( rhs.x < x ) x = rhs.x;
			if( rhs.y < y ) y = rhs.y;
			if( rhs.z < z ) z = rhs.z;
		}

		inline void makeCeil(Vector3& rhs)
		{
			if( rhs.x > x ) x = rhs.x;
			if( rhs.y > y ) y = rhs.y;
			if( rhs.z > z ) z = rhs.z;
		}

		inline Vector3 perpendicular()
		{
			return Vector3(-y, x, z);
		}

		inline Vector3 crossProduct(Vector3& rhs)
		{
            return Vector3(y * rhs.z - z * rhs.y, z * rhs.x - x * rhs.z, x * rhs.y - y * rhs.x);
		}

		inline bool isNaN() const
		{
			return Math::isNaN(x) || Math::isNaN(y) || Math::isNaN(z);
		}
	};



} //namespace Math

#endif

