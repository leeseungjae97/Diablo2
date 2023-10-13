#include "mAudioSource.h"
#include "mAudioClip.h"
#include "mTransform.h"
#include "mGameObject.h"
#include "mSoundManager.h"
#include "mTime.h"

namespace m
{
	AudioSource::AudioSource()
		: Component(eComponentType::AudioSource)
	    , mButtonSoundType(eButtonSoundType::End)
	    , iRunIndex(0)
	    , fRunAcc(0.f)
	    , bRun(false)
	    , bGroupSound(false)
	    , bNextPlay(true)
	    , iRandPlayIndex(0)
	{
		mAudioClips.resize((int)eAudioClipType::End);
	}

	AudioSource::~AudioSource()
	{
		if(!mAudioClipGroup.empty())
		{
			for (AudioClip* ac : mAudioClipGroup)
			{
				delete ac;
				ac = nullptr;
			}
		}
		mAudioClipGroup.clear();

		for(AudioClip* ac : mAudioClips)
		{
		    if(nullptr != ac)
		    {
				delete ac;
				ac = nullptr;
		    }
		}
		mAudioClips.clear();
	}

	void AudioSource::Initialize()
	{
	}

	void AudioSource::Update()
	{
	}

	void AudioSource::LateUpdate()
	{
		for(int i = 0 ; i < (int)eAudioClipType::End; ++i)
		{
			if(bActiveAudioClip[i])
			{
				if (mAudioClips[i] && bAudioClip3DAtr[i])
				{
					Transform* tr = GetOwner()->GetComponent<Transform>();
					Vector3 pos = tr->GetPosition();
					Vector3 foward = tr->Foward();

					mAudioClips[i]->Set3DAttributes(pos, foward);
				}
			}
			
		}
		if (bGroupSound && !mAudioClipGroup.empty())
		{
			for (AudioClip* ac : mAudioClipGroup)
			{
				if(!ac->IsPlaying())
				{
					delete ac;
					ac = nullptr;
					std::erase(mAudioClipGroup, ac);
				}
			}
			
		}

		if (bRun)
		{
			fRunAcc += Time::fDeltaTime();
			if (fRunAcc >= 0.2f)
			{
				++iRunIndex;
				iRunIndex %= 4;

				fRunAcc = 0.f;
				bNextPlay = true;
			}
			else bNextPlay = false;
		}
		else
		{
			fRunAcc = 0.f;
		}
	}
	void AudioSource::ReleaseClips()
	{
		if (mAudioClipGroup.empty()) return;

		for(AudioClip* ac : mAudioClipGroup)
		{
			delete ac;
			ac = nullptr;
		}
		mAudioClipGroup.clear();
	}
	FMOD::Sound* AudioSource::FindSound(ePlayerVoiceSoundType type)
	{
		const std::wstring& name = playerVoiceAudioPath[(int)type][iRandPlayIndex];

		FMOD::Sound* sound = SoundManager::Get(name);
		if (nullptr == sound)
		{
			sound = SoundManager::Load(name);
		}

		return sound;
	}
	FMOD::Sound* AudioSource::FindSound(eButtonSoundType type)
	{
		const std::wstring& name = buttonAudioPaths[(int)type];
		
		FMOD::Sound* sound = SoundManager::Get(name);
		if (nullptr == sound)
		{
			sound = SoundManager::Load(name);
		}

		return sound;
	}
	FMOD::Sound* AudioSource::FindSound(ePlayerRunSoundType type)
	{
		const std::wstring& name = playerRunAudioPath[(int)type][iRunIndex];

		FMOD::Sound* sound = SoundManager::Get(name);
		if (nullptr == sound)
		{
			sound = SoundManager::Load(name);
		}

		return sound;
	}
	FMOD::Sound* AudioSource::FindSound(const std::wstring& name)
	{
		FMOD::Sound* sound = SoundManager::Get(name);
		if (nullptr == sound)
		{
			sound = SoundManager::Load(name);
		}

		return sound;
	}

    void AudioSource::StopAll()
    {
		if (!mAudioClipGroup.empty())
		{
			for (AudioClip* ac : mAudioClipGroup)
			{
				ac->Stop();
			}
		}

		for (AudioClip* ac : mAudioClips)
		{
			if (nullptr != ac)
			{
				ac->Stop();
			}
		}
    }

    void AudioSource::Render()
	{
	}
	void AudioSource::Play(ePlayerVoiceSoundType type, bool loop, bool b3DAt)
	{
		
		if (nullptr == mAudioClips[(int)eAudioClipType::Voice]
			|| !mAudioClips[(int)eAudioClipType::Voice]->IsPlaying())
		{
			FMOD::Sound* sound = FindSound(type);
			if (sound)
			{
				if (nullptr == mAudioClips[(int)eAudioClipType::Voice])
				{
					mAudioClips[(int)eAudioClipType::Voice] = new AudioClip();
				}
			    mAudioClips[(int)eAudioClipType::Voice]->SetSound(sound);
				iRandPlayIndex = rand() % 4;
				bAudioClip3DAtr[(int)eAudioClipType::Voice] = true;
				mAudioClips[(int)eAudioClipType::Voice]->SetLoop(loop);
				mAudioClips[(int)eAudioClipType::Voice]->Play();
			}
		}
	}
	void AudioSource::PlaySounds(ePlayerRunSoundType type, bool loop, bool b3DAt)
	{
		bRun = true;
		if(bNextPlay)
		{
			FMOD::Sound* sound = FindSound(type);
			if (sound)
			{
				if(nullptr == mAudioClips[(int)eAudioClipType::FootStep])
				{
					mAudioClips[(int)eAudioClipType::FootStep] = new AudioClip();
				}
				mAudioClips[(int)eAudioClipType::FootStep]->SetSound(sound);
				mAudioClips[(int)eAudioClipType::FootStep]->SetVolume(10.f);
				bActiveAudioClip[(int)eAudioClipType::FootStep] = true;
				bAudioClip3DAtr[(int)eAudioClipType::FootStep] = true;
				mAudioClips[(int)eAudioClipType::FootStep]->SetLoop(loop);
				mAudioClips[(int)eAudioClipType::FootStep]->PlayRun();
			}
		}
	}

    void AudioSource::Play(const std::wstring& name, bool loop, bool b3DAt)
    {
		if (nullptr == mAudioClips[(int)eAudioClipType::Fire]
			|| !mAudioClips[(int)eAudioClipType::Fire]->IsPlaying())
		{
			FMOD::Sound* sound = FindSound(name);
			if (sound)
			{
				if (nullptr == mAudioClips[(int)eAudioClipType::Fire])
				{
					mAudioClips[(int)eAudioClipType::Fire] = new AudioClip();
				}
				mAudioClips[(int)eAudioClipType::Fire]->SetSound(sound);
				mAudioClips[(int)eAudioClipType::Fire]->SetVolume(50.f);

				bActiveAudioClip[(int)eAudioClipType::Fire] = true;
				bAudioClip3DAtr[(int)eAudioClipType::Fire] = true;
				mAudioClips[(int)eAudioClipType::Fire]->SetLoop(loop);
				mAudioClips[(int)eAudioClipType::Fire]->Play();
			}
		}
    }
	void AudioSource::PlayGroup(const std::wstring& name, bool loop, bool b3DAt)
	{
		FMOD::Sound* sound = FindSound(name);
		if (nullptr == sound) return;

		bGroupSound = true;
		AudioClip* audioClip = new AudioClip();
		
		audioClip->SetSound(sound);
		audioClip->SetLoop(loop);
		audioClip->Play();
		mAudioClipGroup.push_back(audioClip);
	}
    void AudioSource::PlayNoDelay(const std::wstring& name, bool loop, bool b3DAt, float vol)
    {
		if(mAudioClips[(int)eAudioClipType::Fire])
		    mAudioClips[(int)eAudioClipType::Fire]->Stop();

		FMOD::Sound* sound = FindSound(name);
		if (sound)
		{
			if (nullptr == mAudioClips[(int)eAudioClipType::Fire])
			{
				mAudioClips[(int)eAudioClipType::Fire] = new AudioClip();
			}

			mAudioClips[(int)eAudioClipType::Fire]->SetSound(sound);
			bActiveAudioClip[(int)eAudioClipType::Fire] = true;
			bAudioClip3DAtr[(int)eAudioClipType::Fire] = true;
			mAudioClips[(int)eAudioClipType::Fire]->SetVolume(vol);
			mAudioClips[(int)eAudioClipType::Fire]->SetLoop(loop);
			mAudioClips[(int)eAudioClipType::Fire]->Play();
		}
    }

    void AudioSource::Play(eButtonSoundType type, bool loop, bool b3DAt)
	{
		bRun = false;
		if (nullptr == mAudioClips[0] || !mAudioClips[0]->IsPlaying())
		{
			FMOD::Sound* sound = FindSound(type);
			if(sound)
			{
				if (nullptr == mAudioClips[0])
				{
					mAudioClips[0] = new AudioClip();
				}

				mAudioClips[0]->SetSound(sound);
				bActiveAudioClip[0] = true;
				bAudioClip3DAtr[0] = true;
				mAudioClips[0]->SetLoop(loop);
				mAudioClips[0]->Play();
			}
		}
	}
	void AudioSource::Stop()
	{
		bRun = false;
		bActiveAudioClip[0] = false;

		if (nullptr == mAudioClips[0]) return;

		mAudioClips[0]->Stop();
	}
	void AudioSource::Stop(eAudioClipType type)
	{
		bRun = false;
		bActiveAudioClip[(int)type] = false;

		if (nullptr == mAudioClips[(int)type]) return;

		mAudioClips[(int)type]->Stop();
	}
}
