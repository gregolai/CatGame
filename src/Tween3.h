#ifndef TWEEN_3_H
#define TWEEN_3_H

#include "Math.h"
#include "Vector3.h"

namespace Math
{
	class Tween3
	{
	public:
		Tween3(Math::Vector3& start, Math::Vector3& end, float endTime)
		{
			mCurrentTime		= 0;
			mEndTime			= endTime;
			mStart				= start;
			mEnd				= end;
		}
		inline void addTime(float amount) { mCurrentTime += amount; }
		
		inline bool timeExpired() { return mCurrentTime >= mEndTime; }
		inline Math::Vector3 getPosition() { return Math::lerp<Math::Vector3>(mStart, mEnd, mCurrentTime/mEndTime); }
	private:
		float				mCurrentTime;
		float				mEndTime;
		Math::Vector3		mStart;
		Math::Vector3		mEnd;
	};
}

#endif