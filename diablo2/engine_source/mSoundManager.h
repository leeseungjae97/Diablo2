#pragma once
#include "_Engine.h"
#include "SoundLookUpTables.h"
namespace m
{
    class GameObject;

    class SoundManager
	{
	public:
		static void Initialize();
		static void Play(GameObject* playObject, eButtonSoundType soundType, bool loop = false);
		static void Play(GameObject* playObject, const std::wstring& name, bool loop = false);

		static void Play(eButtonSoundType soundType, bool loop = false);
		static void Play(const std::wstring& name, bool loop = false);

		static void Stop(eButtonSoundType soundType);
		static void Stop(const std::wstring& name);
	};
}


