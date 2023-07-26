#include "mApplication.h"
#include "mInput.h"
#include "mTime.h"
#include "mRenderer.h"
#include "mScene.h"
#include "mSceneManager.h"
#include "mMouseManager.h"
#include "mCollisionManager.h"
//#include "mFontWrapper.h"

namespace m
{
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
	}

	void Application::Initialize()
	{
		Time::Initiailize();
		Input::Initialize();
		//FontWrapper::Initialize();
		renderer::Initialize();
		SceneManager::Initialize();
	}

	void Application::Update()
	{
		Time::Update();
		Input::Update();
		// Scene -> Layer -> Entity
		SceneManager::Update();
		MouseManager::Update();
		CollisionManager::Update();
	}

	void Application::LateUpdate()
	{
		SceneManager::LateUpdate();
	}

	void Application::Render()
	{
		Time::Render();

		graphicDevice->ClearTarget();
		graphicDevice->UpdateViewPort();

//#define FONT_RGBA(r, g, b, a) (((((BYTE)a << 24) | (BYTE)b << 16) | (BYTE)g << 8) | (BYTE)r)
//		FontWrapper::DrawFont(L"TEST", 10, 10, 100, FONT_RGBA(255, 0, 255, 255));
		//SceneManager::Render();
		renderer::Render();
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
		SetWindowPos(mHwnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0);
		ShowWindow(mHwnd, true);
		UpdateWindow(mHwnd);
	}

	//void Application::SetViewport(UINT width, UINT height)
	//{
	//	mViewport.x = 0.f;
	//	mViewport.y = 0.f;
	//	mViewport.height = height;
	//	mViewport.width = width;
	//	mViewport.maxDepth = 1000.f;
	//	mViewport.minDepth = -1.f;
	//}

}
