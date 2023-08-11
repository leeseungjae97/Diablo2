#pragma once
#include "_Engine.h"
#include <random>
#include <ctime>

namespace m
{
	class Time
	{
	public:
		static void Initiailize();
		static void Update();
		static void Render();

		__forceinline static double DeltaTime() { return mDeltaTime; }
		__forceinline static float fDeltaTime() { return (float)mDeltaTime; }

	private:
		static double mDeltaTime;
		static double mSecond;
		static LARGE_INTEGER mCpuFrequency;
		static LARGE_INTEGER mPrevFrequency;
		static LARGE_INTEGER mCurFrequency;
	};
}
