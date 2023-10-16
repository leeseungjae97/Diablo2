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
			BGM,
			Ambient,
			UI,
			SFX,
			Voice,
			Fire,
			End,
		};
		static FMOD::Sound* Load(const std::wstring& path);
		static FMOD::Sound* Get(const std::wstring& path);
		static void Initialize();
		static void Update();
		static void Release();
		static void FireAdd();
		static void FireErase();

		static void ExternFireSound();
		static void ExternBGMSound();
		static void ExternUISound(eUISoundType type, bool loop, float vol);
		static void ExternSFXSound(int index);
		static void ExternAmbientSound(eAmbientType type, bool loop, float vol);
        static void ExternVoiceSound(int index, bool loop);

        static void ResetPlayed(eExternAudioType type);
		static void ResetAllPlayed();
        static void StopExtern(eExternAudioType sfx);

        static int iFireCount;
		static int iCurPlayMusic;
		static bool bPlayed[(int)eExternAudioType::End];

		static std::vector<AudioClip*> externAudioClips;
		static std::map<std::wstring, FMOD::Sound*> sounds;
	};
}


