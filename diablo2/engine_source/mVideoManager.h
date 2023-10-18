#pragma once
#include "_Engine.h"

namespace m
{
	class VideoManager
	{
	public:
        static void Update();
        static HRESULT PlayVideo(HWND hwnd);
        inline static IMFPMediaPlayer* g_pPlayer = NULL;

        static bool isPlayed;
    };
}


