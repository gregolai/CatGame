#ifndef MATH_TWEEN2_H
#define MATH_TWEEN2_H

#include "Math.h"
#include "Vector2.h"

namespace Math
{

	class Tween2
	{
	public:
		Tween2(Math::Vector2& start, Math::Vector2& end, float endTime)
		{
			mCurrentTime		= 0;
			mEndTime			= endTime;
			mStart				= start;
			mEnd				= end;
		}

		inline void addTime(float amount) { mCurrentTime += amount; }
		
		inline bool timeExpired() { return mCurrentTime >= mEndTime; }
		inline Math::Vector2 getPosition() { return Math::lerp<Math::Vector2>(mStart, mEnd, mCurrentTime/mEndTime); }
		inline Math::Vector2& getEnd() { return mEnd; }
	private:
		float				mCurrentTime;
		float				mEndTime;
		Math::Vector2		mStart;
		Math::Vector2		mEnd;
	};

}

#endif