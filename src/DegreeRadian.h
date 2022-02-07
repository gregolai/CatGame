#ifndef MATH_DEGREE_RADIAN_H
#define MATH_DEGREE_RADIAN_H

#include "Math.h"

namespace Math
{
	class Degree;

	class Radian
	{
	public:
		//ctor
		inline Radian();
		inline Radian(float val);
		inline Radian(Radian& r);
		inline Radian(Degree& d);

		//= operator
		inline Radian& operator=(float f);
		inline Radian& operator=(Radian& r);
		inline Radian& operator=(Degree& d);

		//+ operator
		inline Radian operator+(float f);
		inline Radian operator+(Radian& r);
		inline Radian operator+(Degree& d);

		//+= operator
		inline Radian& operator+=(float f);
		inline Radian& operator+=(Radian& r);
		inline Radian& operator+=(Degree& d);

		//negate
		inline Radian operator-();

		//- operator
		inline Radian operator-(float f);
		inline Radian operator-(Radian& r);
		inline Radian operator-(Degree& d);

		//-= operator
		inline Radian& operator-=(float f);
		inline Radian& operator-=(Radian& r);
		inline Radian& operator-=(Degree& d);

		//* operator
		inline Radian operator*(float f);
        inline Radian operator*(Radian& r);
		inline Radian operator*(Degree& d);

		//*= operator
		inline Radian& operator*=(float f);
		inline Radian& operator*=(Radian& r);
		inline Radian& operator*=(Degree& d);

		// / operator
		inline Radian operator/(float f);
		inline Radian operator/(Radian& r);
		inline Radian operator/(Degree& d);

		// /= operator
		inline Radian& operator/=(float f);
		inline Radian& operator/=(Radian& r);
		inline Radian& operator/=(Degree& d);

		// < operator
		inline bool operator<(float f);
		inline bool operator<(Radian& r);
		inline bool operator<(Degree& d);

		// <= operator
		inline bool operator<=(float f);
		inline bool operator<=(Radian& r);
		inline bool operator<=(Degree& d);

		// == operator
		inline bool operator==(float f);
		inline bool operator==(Radian& r);
		inline bool operator==(Degree& d);

		// != operator
		inline bool operator!=(float f);
		inline bool operator!=(Radian& r);
		inline bool operator!=(Degree& d);

		// >= operator
		inline bool operator>=(float f);
		inline bool operator>=(Radian& r);
		inline bool operator>=(Degree& d);

		// > operator
		inline bool operator>(float f);
		inline bool operator>(Radian& r);
		inline bool operator>(Degree& d);

		inline float getDegrees();
		inline float getValue();
	private:
		inline void valueClamp();

		float mValue;
	};

	class Degree
	{
	public:
		//ctor
		inline Degree();
		inline Degree(float val);	
		inline Degree(Degree& d);
		inline Degree(Radian& r);

		//= operator
		inline Degree& operator=(float f);
		inline Degree& operator=(Degree& d);
		inline Degree& operator=(Radian& r);

		//+ operator
		inline Degree operator+(float f);
		inline Degree operator+(Degree& d);
		inline Degree operator+(Radian& r);

		//+= operator
		inline Degree& operator+=(float f);
		inline Degree& operator+=(Degree& d);
		inline Degree& operator+=(Radian& r);

		//negate
		inline Degree operator-();

		//- operator
		inline Degree operator-(float f);
		inline Degree operator-(Degree& d);
		inline Degree operator-(Radian& r);

		//-= operator
		inline Degree& operator-=(float f);
		inline Degree& operator-=(Degree& d);
		inline Degree& operator-=(Radian& r);

		//* operator
		inline Degree operator*(float f);
        inline Degree operator*(Degree& d);
		inline Degree operator*(Radian& r);

		//*= operator
		inline Degree& operator*=(float f);
		inline Degree& operator*=(Degree& d);
		inline Degree& operator*=(Radian& r);

		// / operator
		inline Degree operator/(float f);
		inline Degree operator/(Degree& d);
		inline Degree operator/(Radian& r);

		// /= operator
		inline Degree& operator/=(float f);
		inline Degree& operator/=(Degree& d);
		inline Degree& operator/=(Radian& r);

		// < operator
		inline bool operator<(float f);
		inline bool operator<(Degree& d);
		inline bool operator<(Radian& r);

		// <= operator
		inline bool operator<=(float f);
		inline bool operator<=(Degree& d);
		inline bool operator<=(Radian& r);

		// == operator
		inline bool operator==(float f);
		inline bool operator==(Degree& d);
		inline bool operator==(Radian& r);

		// != operator
		inline bool operator!=(float f);
		inline bool operator!=(Degree& d);
		inline bool operator!=(Radian& r);

		// >= operator
		inline bool operator>=(float f);
		inline bool operator>=(Degree& d);
		inline bool operator>=(Radian& r);

		// > operator
		inline bool operator>(float f);
		inline bool operator>(Degree& d);
		inline bool operator>(Radian& r);

		inline float getRadians();
		inline float getValue();
	private:
		inline void valueClamp();

		float mValue;
	};

	//ctor
	inline Radian::Radian()
		: mValue(0)
	{
		mValue = 0;
	}
	inline Radian::Radian(float val)
	{
		mValue = val;
		valueClamp();
	}		
	inline Radian::Radian(Radian& r)
	{
		mValue = r.mValue;
		valueClamp();
	}
	inline Radian::Radian(Degree& d)
	{	
		mValue = d.getRadians();
		valueClamp();
	}

	//= operator
	inline Radian& Radian::operator=(float f)
	{ 
		mValue = f;
		valueClamp();
		return *this;
	}
	inline Radian& Radian::operator=(Radian& r)
	{
		mValue = r.mValue;
		valueClamp();
		return *this;
	}
	inline Radian& Radian::operator=(Degree& d)
	{
		mValue = d.getRadians();
		valueClamp();
		return *this;
	}

	//+ operator
	inline Radian Radian::operator+(float f)
	{
		return Radian(mValue + f);
	}
	inline Radian Radian::operator+(Radian& r)
	{
		return Radian(mValue + r.mValue);
	}
	inline Radian Radian::operator+(Degree& d)
	{
		return Radian(mValue + d.getRadians());
	}

	//+= operator
	inline Radian& Radian::operator+=(float f)
	{
		mValue += f;
		valueClamp();
		return *this;
	}
	inline Radian& Radian::operator+=(Radian& r)
	{
		mValue += r.mValue;
		valueClamp();
		return *this;
	}
	inline Radian& Radian::operator+=(Degree& d)
	{
		mValue += d.getRadians();
		valueClamp();
		return *this;
	}

	//negate
	inline Radian Radian::operator-()
	{
		return Radian(mValue - C_PI);
	}

	//- operator
	inline Radian Radian::operator-(float f)
	{
		return Radian(mValue - f);
	}
	inline Radian Radian::operator-(Radian& r)
	{
		return Radian(mValue - r.mValue);
	}
	inline Radian Radian::operator-(Degree& d)
	{
		return Radian(mValue - d.getRadians());
	}

	//-= operator
	inline Radian& Radian::operator-=(float f)
	{
		mValue -= f;
		valueClamp();
		return *this;
	}
	inline Radian& Radian::operator-=(Radian& r)
	{
		mValue -= r.mValue;
		valueClamp();
		return *this;
	}
	inline Radian& Radian::operator-=(Degree& d)
	{
		mValue -= d.getRadians();
		valueClamp();
		return *this;
	}

	//* operator
	inline Radian Radian::operator*(float f)
	{
		return Radian(mValue * f);
	}
	inline Radian Radian::operator*(Radian& r)
	{
		return Radian(mValue * r.mValue);
	}
	inline Radian Radian::operator*(Degree& d)
	{
		return Radian(mValue * d.getRadians());
	}

	//*= operator
	inline Radian& Radian::operator*=(float f)
	{
		mValue *= f;
		valueClamp();
		return *this;
	}
	inline Radian& Radian::operator*=(Radian& r)
	{
		mValue *= r.mValue;
		valueClamp();
		return *this;
	}
	inline Radian& Radian::operator*=(Degree& d)
	{
		mValue *= d.getRadians();
		valueClamp();
		return *this;
	}

	// / operator
	inline Radian Radian::operator/(float f)
	{
		if(f == 0)
			return Radian(C_POS_INFINITY);
		return Radian(mValue / f);
	}
	inline Radian Radian::operator/(Radian& r)
	{
		if(r.mValue == 0)
			return Radian(C_POS_INFINITY);
		return Radian(mValue / r.mValue);
	}
	inline Radian Radian::operator/(Degree& d)
	{
		float deg = d.getRadians();
		if(deg == 0)
			return Radian(C_POS_INFINITY);
		return Radian(mValue / deg);
	}

	// /= operator
	inline Radian& Radian::operator/=(float f)
	{
		if(f == 0)
			mValue = C_POS_INFINITY;
		else
			mValue /= f;
		valueClamp();
		return *this;
	}
	inline Radian& Radian::operator/=(Radian& r)
	{
		if(r.mValue == 0)
			mValue = C_POS_INFINITY;
		else
			mValue /= r.mValue;
		valueClamp();
		return *this;
	}
	inline Radian& Radian::operator/=(Degree& d)
	{
		float deg = d.getRadians();
		if(deg == 0)
			mValue = C_POS_INFINITY;
		else
			mValue /= deg;
		valueClamp();
		return *this;
	}
	
	// < operator
	inline bool Radian::operator<(float f)					{ return mValue < f; }
	inline bool Radian::operator<(Radian& r)				{ return mValue < r.mValue; }
	inline bool Radian::operator<(Degree& d)				{ return mValue < d.getRadians(); }

	// <= operator
	inline bool Radian::operator<=(float f)					{ return mValue <= f; }
	inline bool Radian::operator<=(Radian& r)				{ return mValue <= r.mValue; }
	inline bool Radian::operator<=(Degree& d)				{ return mValue <= d.getRadians(); }

	// == operator
	inline bool Radian::operator==(float f)					{ return mValue == f; }
	inline bool Radian::operator==(Radian& r)				{ return mValue == r.mValue; }
	inline bool Radian::operator==(Degree& d)				{ return mValue == d.getRadians(); }

	// != operator
	inline bool Radian::operator!=(float f)					{ return mValue != f; }
	inline bool Radian::operator!=(Radian& r)				{ return mValue != r.mValue; }
	inline bool Radian::operator!=(Degree& d)				{ return mValue != d.getRadians(); }

	// >= operator
	inline bool Radian::operator>=(float f)					{ return mValue >= f; }
	inline bool Radian::operator>=(Radian& r)				{ return mValue >= r.mValue; }
	inline bool Radian::operator>=(Degree& d)				{ return mValue >= d.getRadians(); }

	// > operator
	inline bool Radian::operator>(float f)					{ return mValue > f; }
	inline bool Radian::operator>(Radian& r)				{ return mValue > r.mValue; }
	inline bool Radian::operator>(Degree& d)				{ return mValue > d.getRadians(); }

	inline float Radian::getDegrees()						{ return radiansToDegrees(mValue); }
	inline float Radian::getValue()							{ return mValue; }

	inline void Radian::valueClamp()
	{
		while(mValue >= C_FOUR_PI) {
			mValue -= C_TWO_PI;
		}
		while(mValue < -C_FOUR_PI) {
			mValue += C_TWO_PI;
		}	
	}

	//ctor
	inline Degree::Degree()
	{
		mValue = 0;
	}
	inline Degree::Degree(float val)
	{
		mValue = val;
		valueClamp();
	}		
	inline Degree::Degree(Degree& d)
	{
		mValue = d.mValue;
		valueClamp();
	}
	inline Degree::Degree(Radian& r)
	{
		mValue = r.getDegrees();
		valueClamp();
	}

	//= operator
	inline Degree& Degree::operator=(float f)
	{ 
		mValue = f;
		valueClamp();
		return *this;
	}
	inline Degree& Degree::operator=(Degree& d)
	{
		mValue = d.mValue;
		valueClamp();
		return *this;
	}
	inline Degree& Degree::operator=(Radian& r)
	{
		mValue = r.getDegrees();
		valueClamp();
		return *this;
	}

	//+ operator
	inline Degree Degree::operator+(float f)
	{
		return Degree(mValue + f);
	}
	inline Degree Degree::operator+(Degree& d)
	{
		return Degree(mValue + d.mValue);
	}
	inline Degree Degree::operator+(Radian& r)
	{
		return Degree(mValue + r.getDegrees());
	}

	//+= operator
	inline Degree& Degree::operator+=(float f)
	{
		mValue += f;
		valueClamp();
		return *this;
	}
	inline Degree& Degree::operator+=(Degree& d)
	{
		mValue += d.mValue;
		valueClamp();
		return *this;
	}
	inline Degree& Degree::operator+=(Radian& r)
	{
		mValue += r.getDegrees();
		valueClamp();
		return *this;
	}

	//negate
	inline Degree Degree::operator-()
	{
		return Degree(mValue - 180.0f);
	}

	//- operator
	inline Degree Degree::operator-(float f)
	{
		return Degree(mValue - f);
	}
	inline Degree Degree::operator-(Degree& d)
	{
		return Degree(mValue - d.mValue);
	}
	inline Degree Degree::operator-(Radian& r)
	{
		return Degree(mValue - r.getDegrees());
	}

	//-= operator
	inline Degree& Degree::operator-=(float f)
	{
		mValue -= f;
		valueClamp();
		return *this;
	}
	inline Degree& Degree::operator-=(Degree& d)
	{
		mValue -= d.mValue;
		valueClamp();
		return *this;
	}
	inline Degree& Degree::operator-=(Radian& r)
	{
		mValue -= r.getDegrees();
		valueClamp();
		return *this;
	}

	//* operator
	inline Degree Degree::operator*(float f)
	{
		return Degree(mValue * f);
	}
	inline Degree Degree::operator*(Degree& d)
	{
		return Degree(mValue * d.mValue);
	}
	inline Degree Degree::operator*(Radian& r)
	{
		return Degree(mValue * r.getDegrees());
	}

	//*= operator
	inline Degree& Degree::operator*=(float f)
	{
		mValue *= f;
		valueClamp();
		return *this;
	}
	inline Degree& Degree::operator*=(Degree& d)
	{
		mValue *= d.mValue;
		valueClamp();
		return *this;
	}
	inline Degree& Degree::operator*=(Radian& r)
	{
		mValue *= r.getDegrees();
		valueClamp();
		return *this;
	}

	// / operator
	inline Degree Degree::operator/(float f)
	{
		if(f == 0)
			return Degree(C_POS_INFINITY);
		return Degree(mValue / f);
	}
	inline Degree Degree::operator/(Degree& d)
	{
		if(d.mValue == 0)
			return Degree(C_POS_INFINITY);
		return Degree(mValue / d.mValue);
	}
	inline Degree Degree::operator/(Radian& r)
	{
		float deg = r.getDegrees();
		if(deg == 0)
			return Degree(C_POS_INFINITY);
		return Degree(mValue / deg);
	}

	// /= operator
	inline Degree& Degree::operator/=(float f)
	{
		if(f == 0)
			mValue = C_POS_INFINITY;
		else
			mValue /= f;
		valueClamp();
		return *this;
	}
	inline Degree& Degree::operator/=(Degree& d)
	{
		if(d.mValue == 0)
			mValue = C_POS_INFINITY;
		else
			mValue /= d.mValue;
		valueClamp();
		return *this;
	}
	inline Degree& Degree::operator/=(Radian& r)
	{
		float deg = r.getDegrees();
		if(deg == 0)
			mValue = C_POS_INFINITY;
		else
			mValue /= deg;
		valueClamp();
		return *this;
	}

	// < operator
	inline bool Degree::operator<(float f)					{ return mValue < f; }
	inline bool Degree::operator<(Degree& d)				{ return mValue < d.mValue; }
	inline bool Degree::operator<(Radian& r)				{ return mValue < r.getDegrees(); }

	// <= operator
	inline bool Degree::operator<=(float f)					{ return mValue <= f; }
	inline bool Degree::operator<=(Degree& d)				{ return mValue <= d.mValue; }
	inline bool Degree::operator<=(Radian& r)				{ return mValue <= r.getDegrees(); }

	// == operator
	inline bool Degree::operator==(float f)					{ return mValue == f; }
	inline bool Degree::operator==(Degree& d)				{ return mValue == d.mValue; }
	inline bool Degree::operator==(Radian& r)				{ return mValue == r.getDegrees(); }

	// != operator
	inline bool Degree::operator!=(float f)					{ return mValue != f; }
	inline bool Degree::operator!=(Degree& d)				{ return mValue != d.mValue; }
	inline bool Degree::operator!=(Radian& r)				{ return mValue != r.getDegrees(); }

	// >= operator
	inline bool Degree::operator>=(float f)					{ return mValue >= f; }
	inline bool Degree::operator>=(Degree& d)				{ return mValue >= d.mValue; }
	inline bool Degree::operator>=(Radian& r)				{ return mValue >= r.getDegrees(); }

	// > operator
	inline bool Degree::operator>(float f)					{ return mValue > f; }
	inline bool Degree::operator>(Degree& d)				{ return mValue > d.mValue; }
	inline bool Degree::operator>(Radian& r)				{ return mValue > r.getDegrees(); }

	inline float Degree::getRadians()						{ return degreesToRadians(mValue); }
	inline float Degree::getValue()							{ return mValue; }

	inline void Degree::valueClamp()
	{
		while(mValue >= 720.0f) {
			mValue -= 360.0f;
		}
		while(mValue < -720.0f) {
			mValue += 360.0f;
		}	
	}

} //namespace Math

#endif