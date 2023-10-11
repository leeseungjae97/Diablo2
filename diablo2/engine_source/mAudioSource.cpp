#include "mAudioSource.h"
#include "mAudioClip.h"
#include "mTransform.h"
#include "mGameObject.h"
#include "mTime.h"

namespace m
{
	AudioSource::AudioSource()
		: Component(eComponentType::AudioSource)
	    , mButtonSoundType(eButtonSoundType::End)
	    , iRunIndex(0)
	    , fRunAcc(0.f)
	    , bRun(false)
	    , bLoopGroupSound(false)
	    , bNextPlay(true)
	    , iRandPlayIndex(0)
	{
		mAudioClips.resize((int)eAudioClipType::End);
	}

	AudioSource::~AudioSource()
	{

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
				if (mAudioClips[i])
				{
					Transform* tr = GetOwner()->GetComponent<Transform>();
					Vector3 pos = tr->GetPosition();
					Vector3 foward = tr->Foward();

					mAudioClips[i]->Set3DAttributes(pos, foward);
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
	std::shared_ptr<AudioClip> AudioSource::FindClip(ePlayerVoiceSoundType type)
	{
		const std::wstring& name = playerVoiceAudioPath[(int)type][iRandPlayIndex];

		std::shared_ptr<AudioClip> audioClip = RESOURCE_FIND(AudioClip, name);
		if (nullptr == audioClip)
		{
			RESOURCE_LOAD(AudioClip, name, name);

			audioClip = RESOURCE_FIND(AudioClip, name);
		}

		return audioClip;
	}
	std::shared_ptr<AudioClip> AudioSource::FindClip(eButtonSoundType type)
	{
		const std::wstring& name = buttonAudioPaths[(int)type];
		
		std::shared_ptr<AudioClip> audioClip =RESOURCE_FIND(AudioClip, name);
		if (nullptr == audioClip)
		{
			RESOURCE_LOAD(AudioClip, name, name);

			audioClip = RESOURCE_FIND(AudioClip, name);
		}

		return audioClip;
	}
	std::shared_ptr<AudioClip> AudioSource::FindClip(ePlayerRunSoundType type)
	{
		const std::wstring& name = playerRunAudioPath[(int)type][iRunIndex];

		std::shared_ptr<AudioClip> audioClip = RESOURCE_FIND(AudioClip, name);
		if (nullptr == audioClip)
		{
			RESOURCE_LOAD(AudioClip, name, name);

			audioClip = RESOURCE_FIND(AudioClip, name);
		}

		return audioClip;
	}

	void AudioSource::Render()
	{
	}
	void AudioSource::Play(ePlayerVoiceSoundType type, bool loop)
	{
		
		if (nullptr == mAudioClips[(int)eAudioClipType::Voice]
			|| !mAudioClips[(int)eAudioClipType::Voice]->IsPlaying())
		{
			iRandPlayIndex = rand() % 4;
			mAudioClips[(int)eAudioClipType::Voice] = FindClip(type);
			mAudioClips[(int)eAudioClipType::Voice]->SetLoop(loop);
			mAudioClips[(int)eAudioClipType::Voice]->Play();
		}
	}
	void AudioSource::PlaySounds(ePlayerRunSoundType type, bool loop)
	{
		bLoopGroupSound = true;
		bRun = true;
		if(bNextPlay)
		{
			bActiveAudioClip[(int)eAudioClipType::FootStep] = true;
			mAudioClips[(int)eAudioClipType::FootStep] = FindClip(type);
			mAudioClips[(int)eAudioClipType::FootStep]->SetLoop(loop);
			mAudioClips[(int)eAudioClipType::FootStep]->Play();
		}
	}
	void AudioSource::Play(ePlayerRunSoundType type, bool loop)
	{
		bRun = true;
		if(nullptr == mAudioClips[(int)eAudioClipType::FootStep] 
			|| mAudioClips[(int)eAudioClipType::FootStep]->IsPlaying())
		{
			bActiveAudioClip[(int)eAudioClipType::FootStep] = true;
			mAudioClips[(int)eAudioClipType::FootStep] = FindClip(type);
			mAudioClips[(int)eAudioClipType::FootStep]->SetLoop(loop);
			mAudioClips[(int)eAudioClipType::FootStep]->Play();
		}
	}
	void AudioSource::Play(eButtonSoundType type, bool loop)
	{
		bRun = false;
		if (nullptr == mAudioClips[0] || mAudioClips[0]->IsPlaying())
		{
			bActiveAudioClip[0] = true;
			mAudioClips[0] = FindClip(type);
			mAudioClips[0]->SetLoop(loop);
			mAudioClips[0]->Play();
		}
	}
	void AudioSource::Stop()
	{
		bRun = false;
		mAudioClips[0]->Stop();
		bActiveAudioClip[0] = false;
	}
	void AudioSource::Stop(eAudioClipType type)
	{
		bRun = false;
		mAudioClips[(int)type]->Stop();
		bActiveAudioClip[(int)type] = false;
	}
}
