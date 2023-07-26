//#pragma once
//#include "_Engine.h"
//
//#include "..\\External\\FW1FontWrapper\\Include\\FW1FontWrapper.h"
//#include "..\\External\\FW1FontWrapper\\Include\\FW1CompileSettings.h"
//
//#ifdef _DEBUG
//#pragma comment(lib, "..\\External\\FW1FontWrapper\\Library_\\Debug_\\FW1FontWrapperL.lib")
//#else
//#pragma comment(lib, "..\\External\\FW1FontWrapper\\Library_\\Release_\\FW1FontWrapper.lib")
//#endif
//
//#define FONT_RGBA(r, g, b, a) (((((BYTE)a << 24) | (BYTE)b << 16) | (BYTE)g << 8) | (BYTE)r)
//
//namespace m
//{
//	class FontWrapper
//	{
//	public:
//		static bool Initialize();
//		static void DrawFont(const wchar_t* str, float x, float y, float size, UINT rgb);
//		static void Release();
//
//	private:
//		static IFW1Factory* mFW1Factory;
//		static IFW1FontWrapper* mFontWrapper;
//	};
//}
//
