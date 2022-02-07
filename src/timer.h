#ifndef TIMER_H
#define TIMER_H

#include "MMSystem.h"

class Timer
{
public:
	void start()
	{
		DWORD t				= timeGetTime();
		mBaseTime			= t;
		mPrevTime			= t;
		mSavedTime			= 0;
		mIsPaused			= false;
	}
	
	void pause()
	{
		if(!mIsPaused) {
			mSavedTime = timeGetTime();

			mIsPaused = true;
		}
	}

	void unpause()
	{
		if(mIsPaused) {
			DWORD t = timeGetTime();
			DWORD delta = t - mSavedTime;
			mBaseTime += delta;
			mPrevTime = t;

			mIsPaused = false;
		}
	}

	inline void tick()
	{
		if(!mIsPaused) {
			mPrevTime = timeGetTime();
		}
	}

	inline DWORD getMilliseconds()			{ return timeGetTime() - mBaseTime; }
	inline float getSeconds()				{ return getMilliseconds() / 1000.0f; }
	inline DWORD getDeltaMilliseconds()		{ return timeGetTime() - mPrevTime; }
	inline float getDeltaSeconds()			{ return getDeltaMilliseconds() / 1000.0f; }
	inline bool isPaused()					{ return mIsPaused; }
private:
	DWORD mBaseTime;
	DWORD mPrevTime;
	DWORD mSavedTime;
	bool mIsPaused;
};

#endif