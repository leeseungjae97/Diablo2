#pragma once
#include "_Engine.h"

#include "..\\External\\FW1FontWrapper\\Include_\\FW1FontWrapper.h"
#include "..\\External\\FW1FontWrapper\\Include_\\FW1CompileSettings.h"
//#include "..\\External\\Include\\Fmod\\common_platform.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\External\\FW1FontWrapper\\Library_\\Debug\\FW1FontWrapperL.lib")
#else
#pragma comment(lib, "..\\External\\FW1FontWrapper\\Library_\\Debug\\FW1FontWrapper.lib")
#endif

//#include <SpriteFont.h>
//#include <SpriteBatch.h>

namespace m
{
#define FONT_RGBA(r, g, b, a) (((((BYTE)a << 24 ) | (BYTE)b << 16) | (BYTE)g << 8) | (BYTE)r)

	class FontWrapper
	{
	public:
		static bool Initialize();
		static void DrawFont(const wchar_t* str, float x, float y, float size, UINT rgb);
		static void Release();


	private:
		static IFW1Factory* mFW1Factory;
		static IFW1FontWrapper* mFontWrapper;
	};
}
