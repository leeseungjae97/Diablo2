#pragma once
#include "_Engine.h"
#include "../External/Fmod/Include_/fmod_studio.hpp"
#include "../External/Fmod/Include_/fmod.hpp"
#include "../External/Fmod/Include_/fmod_common.h"
#include "../External/Fmod/Include_/fmod_codec.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\External\\Fmod\\Library_\\Debug\\fmodL_vc.lib")
#pragma comment(lib, "..\\External\\Fmod\\Library_\\Debug\\fmodstudioL_vc.lib")
#else
#pragma comment(lib, "..\\External\\Fmod\\Library_\\Debug\\fmod_vc.lib")
#pragma comment(lib, "..\\External\\Fmod\\Library_\\Release\\fmodstudio_vc.lib")
#endif

namespace m
{
	class Fmod
	{
	public:
		static void Initialize();
		static bool CreateSound(const std::string& path, FMOD::Sound** sound);
		static void SoundPlay(FMOD::Sound* sound, FMOD::Channel** channel);
		static void Set3DListenerAttributes(const Vector3* pos, const Vector3* vel, const Vector3* forward, const Vector3* up);
		static void Release();

	private:
		static FMOD::Studio::System* mSystem;
		static FMOD::System* mCoreSystem;
	};
}

