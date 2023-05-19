#pragma once
#include "_Engine.h"
#include "mGraphicsDevice_DX11.h"
namespace m {
	class Application {
	public:
		//Application(std::unique_ptr<m::graphics::GraphicsDevice_DX11> _graphicsDevice);
		Application();
		~Application();

		void Run();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

		void SetWindow(HWND hwnd, UINT width, UINT height);

		UINT GetWidth() { return mWidth ; }
		UINT GetHeight() { return mHeight ; }
		HWND GetHwnd() { return mHwnd; }
		
	private:
		bool mboInitialize = false;

		// ����Ʈ ������ �ϳ��� ��ü�� ������ (static)
		std::unique_ptr<m::graphics::GraphicsDevice_DX11> graphicsDevice;
		HWND mHwnd;
		UINT mWidth;
		UINT mHeight;
	};
}


