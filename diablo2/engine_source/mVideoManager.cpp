#include "mVideoManager.h"

#include "mApplication.h"
#include "mGraphicDevice_DX11.h"
#include "mSceneManager.h"

namespace m
{
	bool VideoManager::isPlayed = false;
	void VideoManager::Update()
	{
		MFP_MEDIAPLAYER_STATE pState = MFP_MEDIAPLAYER_STATE::MFP_MEDIAPLAYER_STATE_EMPTY;

		if(g_pPlayer)
		{
			g_pPlayer->GetState(&pState);
		}

		if (pState == MFP_MEDIAPLAYER_STATE::MFP_MEDIAPLAYER_STATE_PLAYING)
		{
			isPlayed = true;
		}

		if(pState == MFP_MEDIAPLAYER_STATE::MFP_MEDIAPLAYER_STATE_STOPPED)
		{
			if(isPlayed)
			{
				if (g_pPlayer)
				{
					g_pPlayer->Shutdown();
					g_pPlayer->Release();
					g_pPlayer = nullptr;
					PostQuitMessage(0);
				}
			}
		}
	}
	HRESULT VideoManager::PlayVideo(HWND hwnd)
	{
		std::wstring path = L"";
		wchar_t buffer[MAX_PATH];
		GetModuleFileName(NULL, buffer, MAX_PATH);
		int m = 0;
		int iLen = wcslen(buffer);
		for (int i = iLen - 1; i >= 0; i--)
		{
			if ('\\' == buffer[i])
			{
				buffer[i] = '\0';
				++m;
			}
			if(m >= 3)
			{
				break;
			}
		}
		path = buffer;
		path += L"\\Resources\\texture\\video\\end_video.mp4";
		
		OutputDebugString(path.c_str());

		HRESULT hr;
		hr = MFPCreateMediaPlayer(
			path.c_str(),
			TRUE,   // Start playback automatically?
			0,      // Flags.
			NULL,   // Callback pointer.
			hwnd,
			&g_pPlayer
		);
		if(FAILED(hr))
		{
			OutputDebugString(L"failed");
		}

		g_pPlayer->Play();

		
		return S_OK;
	}
}
