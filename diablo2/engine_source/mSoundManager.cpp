#include "mSoundManager.h"

#include "mAudioClip.h"
#include "mResources.h"
#include "mGameObject.h"

#include "mFmod.h"
#include "SkillLookUpTables.h"

namespace m
{
	std::map<std::wstring, FMOD::Sound*> SoundManager::sounds;
	std::vector<AudioClip*> SoundManager::externAudioClips;
	int SoundManager::iFireCount = 0;
	FMOD::Sound* SoundManager::Load(const std::wstring& path)
	{
		std::string cPath(path.begin(), path.end());
		FMOD::Sound* sound = nullptr;
		if (!Fmod::CreateSound(cPath, &sound))
			return nullptr;


		sound->set3DMinMaxDistance(1.f, 1000.f);
		return sound;
	}

	FMOD::Sound* SoundManager::Get(const std::wstring& path)
    {
		if (path == L"") return nullptr;

		std::map<std::wstring, FMOD::Sound*>::iterator iter
			= sounds.find(path);

		if (iter == sounds.end())
			return nullptr;

		return iter->second;
    }

    void SoundManager::Initialize()
	{
		externAudioClips.resize((int)eExternAudioType::End);
		for (int i = 0; i < (int)ePlayerRunSoundType::End; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				std::wstring path = playerRunAudioPath[i][j];
				FMOD::Sound* sound = Load(path);
				if (nullptr != sound)
					sounds.insert(std::make_pair(path,sound));
			}
		}
		for (int i = 0; i < (int)ePlayerVoiceSoundType::End; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				std::wstring path = playerVoiceAudioPath[i][j];
				FMOD::Sound* sound = Load(path);
				if (nullptr != sound)
					sounds.insert(std::make_pair(path, sound));
			}
		}
		for (int i = 0; i < (int)eSkillType::END; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				std::wstring path = skillSoundPath[i][j];
				FMOD::Sound* sound = Load(path);
				if (nullptr != sound)
					sounds.insert(std::make_pair(path, sound));
			}
		}
		for (int i = 0; i < (int)eSkillType::END; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				std::wstring path = skillCrashSoundPath[i][j];
				FMOD::Sound* sound = Load(path);
				if (nullptr != sound)
					sounds.insert(std::make_pair(path, sound));
			}
		}
		for( int i = 0 ; i < 3 ; ++i)
		{
			std::wstring path = fireSoundPath[i];
			FMOD::Sound* sound = Load(path);
			if (nullptr != sound)
				sounds.insert(std::make_pair(path, sound));
		}
	}

    void SoundManager::Release()
    {
		//std::map<std::wstring, FMOD::Sound*>::iterator iter
		//	= sounds.begin();
		//while(iter != sounds.end())
		//{
		//	if (iter->second)
		//	{
		//		delete iter->second;
		//		iter->second = nullptr;
		//	}
		//}
		if(!sounds.empty())
		    sounds.clear();
    }

    void SoundManager::FireAdd()
    {
		++iFireCount;
    }

    void SoundManager::FireErase()
    {
		--iFireCount;
    }

    void SoundManager::ExternSound()
    {
		if(iFireCount > 0)
		{
			if(nullptr == externAudioClips[(int)eExternAudioType::Fire])
			{
				FMOD::Sound* sound = Get(fireSoundPath[0]);
				if (nullptr == sound) return;

				externAudioClips[(int)eExternAudioType::Fire] = new AudioClip();
				externAudioClips[(int)eExternAudioType::Fire]->SetSound(sound);
				externAudioClips[(int)eExternAudioType::Fire]->SetLoop(true);
				externAudioClips[(int)eExternAudioType::Fire]->Play();
				//externAudioClips[(int)eExternAudioType::Fire]->SetVolume(20.f);
			}
		}
		if(iFireCount == 0)
		{
			if(nullptr != externAudioClips[(int)eExternAudioType::Fire])
			{
				externAudioClips[(int)eExternAudioType::Fire]->Stop();

				delete externAudioClips[(int)eExternAudioType::Fire];
				externAudioClips[(int)eExternAudioType::Fire] = nullptr;
			}
			
		}
    }
}
