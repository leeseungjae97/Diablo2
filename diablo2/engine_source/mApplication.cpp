#include "mApplication.h"
#include "mInput.h"
#include "mTime.h"
#include "mRenderer.h"
#include "mScene.h"
#include "mSceneManager.h"
#include "mMouseManager.h"
#include "mCollisionManager.h"
#include "mFmod.h"
#include "mFontWrapper.h"

#include "../Engine/mPlayerManager.h"
#include "../Engine/mPlayer.h"
#include "../Engine/mPlayerStatus.h"

#include "../editor_source/guiEditor.h"

#include "mGameObject.h"
#include "mInteractUIManager.h"
#include "mScreenEffectManager.h"
#include "mSoundManager.h"
#include "mTileDrawManager.h"
#include "mCheatManager.h"
#include "mSkillManager.h"
#include "mVideoManager.h"

namespace m
{
	Viewport Application::mViewPort = {};
	Application::Application()
		: graphicDevice(nullptr)
		, mHwnd(NULL)
		, mWidth(-1)
		, mHeight(-1)
	{

	}

	Application::~Application()
	{}

	void Application::Run()
	{
		Update();
		LateUpdate();
		Render();
		Destroy();
	}

	void Application::Initialize()
	{
		mViewPort = {
        0.f,
        0.f,
        RESOL_WID,
        RESOL_HEI,
        10.f,
        -1.f,
		};

		Time::Initiailize();
		Input::Initialize();
		Fmod::Initialize();
        FontWrapper::Initialize();
		//VideoManager::Initialize();

		renderer::Initialize();
		StashManager::Initialize();
		SceneManager::Initialize();
		SoundManager::Initialize();
		MouseManager::Initialize();
		//gui::Editor::Initialize();
	}

	void Application::Update()
	{
		Time::Update();
		Input::Update();
		
		MouseManager::Update();
		StashManager::Update();
		SceneManager::Update();
		PlayerStatus::Update();
		CollisionManager::Update();
		InteractUIManager::Update();
		ScreenEffectManager::Update();
		CheatManager::Update();

		TileDrawManager::Update();
		SoundManager::Update();
		Fmod::Update();
		VideoManager::Update();

		SkillManager::Update();
	}

	void Application::LateUpdate()
	{
		SceneManager::LateUpdate();
	}

	void Application::Render()
	{
		graphicDevice->ClearTarget();
		graphicDevice->UpdateViewPort();
		Time::Render();

		renderer::Render();
	}
	void Application::Destroy()
	{
		SceneManager::Destroy();
	}
	void Application::Present()
	{
		graphicDevice->Present();
	}

	void Application::SetWindow(HWND hwnd, UINT width, UINT height)
	{
		if (graphicDevice == nullptr)
		{
			mHwnd = hwnd;
			mWidth = width;
			mHeight = height;

			graphicDevice = std::make_unique<m::graphics::GraphicDevice_DX11>();
			m::graphics::GetDevice() = graphicDevice.get();
		}

		RECT rt = { 0, 0, (LONG)width , (LONG)height };
		AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);
		
		//SetWindowPos(mHwnd, nullptr, 2570, 1440 - 1080, rt.right - rt.left, rt.bottom - rt.top, 0);
		SetWindowPos(mHwnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0);
		ShowWindow(mHwnd, true);
		UpdateWindow(mHwnd);
	}
}
