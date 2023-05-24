#pragma once
#include "_Engine.h"
#include "mGraphicsDevice_DX11.h"
namespace m
{
	class Application
	{
	public:
		Application();
		~Application();

		void Run();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

		void SetWindow(HWND hwnd, UINT width, UINT height);

		UINT GetWidth() { return mWidth; }
		UINT GetHeight() { return mHeight; }
		HWND GetHwnd() { return mHwnd; }

	private:
		bool mbInitialize = false;

		// 스마트 포인터 하나의 객체만 생성됨 (static)
		std::unique_ptr<m::graphics::GraphicsDevice_DX11> graphicsDevice;
		HWND mHwnd;
		UINT mWidth;
		UINT mHeight;
	};
}


