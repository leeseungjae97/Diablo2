#include "mApplication.h"
#include "mInput.h"
#include "mTime.h"
#include "mRenderer.h"

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

		renderer::Initialize();

		tempPos = Vector4(0.0f, 0.0f, 0.0f, 1.0f);

		mScene = new Scene();
		mScene->Initialize();
	}

	void Application::Update()
	{
		Time::Update();
		Input::Update();
		// Scene -> Layer -> Entity
		Vector4 pos = tempPos;
		if (KEY_PRESSED(eKeyCode::UP))
		{
			pos.y += 0.1f * (float)Time::DeltaTime();
		}
		if (KEY_PRESSED(eKeyCode::DOWN))
		{
			pos.y -= 0.1f * (float)Time::DeltaTime();
		}
		if (KEY_PRESSED(eKeyCode::LEFT))
		{
			pos.x -= 0.1f * (float)Time::DeltaTime();
		}
		if (KEY_PRESSED(eKeyCode::RIGHT))
		{
			pos.x += 0.1f * (float)Time::DeltaTime();
		}
		if (pos != tempPos)
		{
			tempPos = pos;

			//constantBuffer->SetData(&tempPos);
			//constantBuffer->Bind(eShaderStage::VS);
		}

		mScene->Update();
	}

	void Application::LateUpdate()
	{}

	void Application::Render()
	{
		Time::Render();

		graphicDevice->Draw();
		mScene->Render();
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

}
