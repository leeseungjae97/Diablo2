#pragma once
#include "_Engine.h"
#include "SoundLookUpTables.h"

namespace FMOD
{
	class Sound;
}


namespace m
{
    class AudioClip;
    class GameObject;

    class SoundManager
	{
	public:
		enum class eExternAudioType
		{
			BackgroundMusic,
			Fire,
			End,
		};
		static FMOD::Sound* Load(const std::wstring& path);
		static FMOD::Sound* Get(const std::wstring& path);
		static void Initialize();
		static void Release();
		static void FireAdd();
		static void FireErase();
		static void ExternSound();

		static int iFireCount;

		static std::vector<AudioClip*> externAudioClips;
		static std::map<std::wstring, FMOD::Sound*> sounds;
	};
}


