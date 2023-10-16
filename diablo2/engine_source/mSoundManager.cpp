#include "mSoundManager.h"

#include "mAudioClip.h"
#include "mResources.h"
#include "mGameObject.h"

#include "mFmod.h"
#include "MoveAbleObjectAnimLookUpTables.h"
#include "mStageManager.h"
#include "SkillLookUpTables.h"

namespace m
{
	std::map<std::wstring, FMOD::Sound*> SoundManager::sounds;
	std::vector<AudioClip*> SoundManager::externAudioClips;
	int SoundManager::iFireCount = 0;
	int SoundManager::iCurPlayMusic = -1;
	bool SoundManager::bPlayed[(int)eExternAudioType::End] = { false, false, false, false, false, };
	FMOD::Sound* SoundManager::Load(const std::wstring& path)
	{
		std::string cPath(path.begin(), path.end());
		FMOD::Sound* sound = nullptr;
		if (!Fmod::CreateSound(cPath, &sound))
			return nullptr;


		sound->set3DMinMaxDistance(0.f, 500.f);
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

		for(int i = 0 ; i <(int)eUISoundType::End; ++i )
		{
			std::wstring path = buttonSoundPaths[i];
			FMOD::Sound* sound = Load(path);
			if (nullptr != sound)
				sounds.insert(std::make_pair(path, sound));
		}
		for (int i = 0; i < 6; ++i)
		{
			std::wstring path = itemDropSoundPaths[i];
			FMOD::Sound* sound = Load(path);
			if (nullptr != sound)
				sounds.insert(std::make_pair(path, sound));
		}
		for(int i = 0 ; i < (int)eBGMType::End; ++i)
		{
			std::wstring path = bgmSoundPaths[i];
			FMOD::Sound* sound = Load(path);
			if (nullptr != sound)
				sounds.insert(std::make_pair(path, sound));
		}
		for(int i = 0 ; i < (int)eSFXType::End; ++i)
		{
			std::wstring path = sfxSoundPaths[i];
			FMOD::Sound* sound = Load(path);
			if (nullptr != sound)
				sounds.insert(std::make_pair(path, sound));
		}
		for(int i = 0 ; i < (int)eMonsterType::End ; ++i)
		{
			for(int j = 0 ; j < 3; ++j)
			{
				std::wstring path = speachSoundPaths[i][j];
				FMOD::Sound* sound = Load(path);
				if (nullptr != sound)
					sounds.insert(std::make_pair(path, sound));
			}
		}
		for(int i = 0 ; i < (int)eAmbientType::End; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				std::wstring path = ambientSoundPaths[i][j];
				FMOD::Sound* sound = Load(path);
				if (nullptr != sound)
					sounds.insert(std::make_pair(path, sound));
			}
		}
		for(int i = 0 ; i < (int)eMonsterType::End; ++i)
		{
			for(int j = 0 ; j< (int)MonsterData::eAnimationType::End; ++j)
			{
			    for(int k = 0 ; k < 3; ++k)
			    {
					std::wstring path = monsterSoundPath[i][j][k];
					FMOD::Sound* sound = Load(path);
					if (nullptr != sound)
						sounds.insert(std::make_pair(path, sound));
			    }
			}
		}
	}

    void SoundManager::Release()
    {

		for(int i = 0; i < (int)eExternAudioType::End; ++i )
		{
		    if(externAudioClips[i])
		    {
				delete externAudioClips[i];
				externAudioClips[i] = nullptr;
		    }
		}
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
	void SoundManager::Update()
	{
		ExternFireSound();
		ExternBGMSound();
	}
    void SoundManager::ExternFireSound()
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
	void SoundManager::ExternBGMSound()
	{
		if (StageManager::stageNum == -1) return;

		if (iCurPlayMusic != StageManager::stageNum)
		{
			iCurPlayMusic = StageManager::stageNum;

			FMOD::Sound* sound = Get(bgmSoundPaths[iCurPlayMusic]);

			if (nullptr == sound) return;

			if (nullptr == externAudioClips[(int)eExternAudioType::BGM])
			{
				externAudioClips[(int)eExternAudioType::BGM] = new AudioClip();
			}

			externAudioClips[(int)eExternAudioType::BGM]->Stop();

			externAudioClips[(int)eExternAudioType::BGM]->SetSound(sound);
			externAudioClips[(int)eExternAudioType::BGM]->SetLoop(true);
			externAudioClips[(int)eExternAudioType::BGM]->PlayExtern();
		}
	}

    void SoundManager::ExternUISound(eUISoundType type, bool loop, float vol)
    {
		if (bPlayed[(int)eExternAudioType::UI]) return;

		bPlayed[(int)eExternAudioType::UI] = true;

		FMOD::Sound* sound = Get(buttonSoundPaths[(int)type]);

		if (nullptr == sound) return;

		if (nullptr == externAudioClips[(int)eExternAudioType::UI])
		{
			externAudioClips[(int)eExternAudioType::UI] = new AudioClip();
		}

		externAudioClips[(int)eExternAudioType::UI]->Stop();

		externAudioClips[(int)eExternAudioType::UI]->SetSound(sound);
		externAudioClips[(int)eExternAudioType::UI]->SetLoop(loop);
		externAudioClips[(int)eExternAudioType::UI]->SetVolume(vol);
		externAudioClips[(int)eExternAudioType::UI]->PlayExtern();
    }

    void SoundManager::ExternAmbientSound(eAmbientType type, bool loop, float vol)
	{
		if (bPlayed[(int)eExternAudioType::Ambient]) return;

		bPlayed[(int)eExternAudioType::Ambient] = true;

		int iRandIndex = rand() % 3;
		FMOD::Sound* sound = Get(ambientSoundPaths[(int)type][iRandIndex]);

		if (nullptr == sound) return;

		if (nullptr == externAudioClips[(int)eExternAudioType::Ambient])
		{
			externAudioClips[(int)eExternAudioType::Ambient] = new AudioClip();
		}

		externAudioClips[(int)eExternAudioType::Ambient]->Stop();

		externAudioClips[(int)eExternAudioType::Ambient]->SetSound(sound);
		externAudioClips[(int)eExternAudioType::Ambient]->SetLoop(loop);
		externAudioClips[(int)eExternAudioType::Ambient]->SetVolume(vol);
		externAudioClips[(int)eExternAudioType::Ambient]->PlayExtern();
	}
	void SoundManager::ExternSFXSound(int index)
	{
		if (bPlayed[(int)eExternAudioType::SFX]) return;

		bPlayed[(int)eExternAudioType::SFX] = true;

		FMOD::Sound* sound = Get(sfxSoundPaths[index]);

		if (nullptr == sound) return;

		if (nullptr == externAudioClips[(int)eExternAudioType::SFX])
		{
			externAudioClips[(int)eExternAudioType::SFX] = new AudioClip();
		}

		externAudioClips[(int)eExternAudioType::SFX]->Stop();

		externAudioClips[(int)eExternAudioType::SFX]->SetSound(sound);
		externAudioClips[(int)eExternAudioType::SFX]->SetLoop(true);
		externAudioClips[(int)eExternAudioType::SFX]->PlayExtern();
	}
	void SoundManager::ExternVoiceSound(int index, bool loop)
	{
		if (bPlayed[(int)eExternAudioType::Voice]) return;

		bPlayed[(int)eExternAudioType::Voice] = true;

		int iRandIndex = rand() % 3;

		FMOD::Sound* sound = Get(speachSoundPaths[index][iRandIndex]);

		if (nullptr == sound) return;

		if (nullptr == externAudioClips[(int)eExternAudioType::Voice])
		{
			externAudioClips[(int)eExternAudioType::Voice] = new AudioClip();
		}

		externAudioClips[(int)eExternAudioType::Voice]->Stop();

		externAudioClips[(int)eExternAudioType::Voice]->SetSound(sound);
		externAudioClips[(int)eExternAudioType::Voice]->SetLoop(loop);
		externAudioClips[(int)eExternAudioType::Voice]->PlayExtern();
	}
    void SoundManager::ResetPlayed(eExternAudioType type)
    {
		bPlayed[(int)type] = false;
    }
	void SoundManager::ResetAllPlayed()
	{
		for(int i = 0 ; i < (int)eExternAudioType::End; ++i)
		{
			bPlayed[i] = false;
		}
		
	}

    void SoundManager::StopExtern(eExternAudioType sfx)
    {
		if(externAudioClips[(int)sfx])
		{
			externAudioClips[(int)sfx]->Stop();
		}
    }
}
