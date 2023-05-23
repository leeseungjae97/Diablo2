#include "mApplication.h"

namespace m
{
	Application::Application()
		: graphicsDevice(nullptr)
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
	{}
	void Application::Update()
	{}
	void Application::LateUpdate()
	{}
	void Application::Render()
	{
		graphicsDevice->Draw();
	}
	void Application::SetWindow(HWND hwnd, UINT width, UINT height)
	{
		if (nullptr == graphicsDevice)
		{
			mHwnd = hwnd;
			mWidth = width;
			mHeight = height;

			graphicsDevice = std::make_unique<m::graphics::GraphicsDevice_DX11>();
		}
		RECT rt = { 0, 0, (LONG)width , (LONG)height };
		AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);
		SetWindowPos(mHwnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0);
		ShowWindow(mHwnd, true);
		UpdateWindow(mHwnd);
	}
}