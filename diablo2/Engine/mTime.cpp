#include "mTime.h"
#include "mApplication.h"

namespace m {
	Application application;
	double Time::mDeltaTime = 0.0l;
	double Time::mSecond = 0.0f;
	int Time::iFrame = 0;
	LARGE_INTEGER Time::mCpuFrequency = {};
	LARGE_INTEGER Time::mPrevFrequency = {};
	LARGE_INTEGER Time::mCurFrequency = {};

	void Time::Initiailize() {
		// CPU 고유 진동수 가져오기
		QueryPerformanceFrequency(&mCpuFrequency);

		// 프로그램이 처음 시작할때 진동수
		QueryPerformanceCounter(&mPrevFrequency);
	}

	void Time::Update() {
		QueryPerformanceCounter(&mCurFrequency);

		double differnceFrequency = (double)mCurFrequency.QuadPart - (double)mPrevFrequency.QuadPart;

		mDeltaTime = differnceFrequency / (double)mCpuFrequency.QuadPart;

		mPrevFrequency.QuadPart = mCurFrequency.QuadPart;
		//#ifdef _DEBUG
		//		if (mDeltaTime > (1. / 60.)) mDeltaTime = (1. / 60.);
		//#endif
	}

	void Time::Render(HDC hdc) {
		iFrame++;
		mSecond += mDeltaTime;

		if (mSecond > 1.0f) {
			HWND hWnd = application.GetHwnd();

			wchar_t szFloat[50] = {};
			float FPS = 1.0f / (float)mDeltaTime;
			swprintf_s(szFloat, 50, L"FPS : %d", iFrame);
			size_t iLen = wcsnlen_s(szFloat, 50);
			SetWindowText(hWnd, szFloat);
			iFrame = 0;
			mSecond = 0.0f;
		}
	}
}