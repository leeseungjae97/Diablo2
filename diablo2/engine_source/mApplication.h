#pragma once
#include "_Engine.h"
#include "mGraphicDevice_DX11.h"

namespace m
{
	class Scene;
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
		void Destroy();
		void Present();

		void SetWindow(HWND hwnd, UINT width, UINT height);
		//void SetViewport(UINT width, UINT height);

		UINT GetWidth() { return mWidth; }
		UINT GetHeight() { return mHeight; }
		HWND GetHwnd() { return mHwnd; }
		static Viewport GetViewPort() { return mViewPort; }

	private:
		bool mbInitialize = false;

		// ����Ʈ ������ �ϳ��� ��ü�� ������ (static)
		std::unique_ptr<m::graphics::GraphicDevice_DX11> graphicDevice;
		HWND mHwnd;
		UINT mWidth;
		UINT mHeight;

		static Viewport mViewPort;
		//Viewport mViewport;
	};
}


