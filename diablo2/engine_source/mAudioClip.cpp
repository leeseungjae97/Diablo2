#include "mAudioClip.h"

#include "mFmod.h"

namespace m
{
    AudioClip::AudioClip()
        : mSound(nullptr)
        , mChannel(nullptr)
        , mMinDistance(1.0f)
        , mMaxDistance(1000.0f)
        , mbLoop(false)
    {

    }

    AudioClip::~AudioClip()
    {
    }

    void AudioClip::SetSound(FMOD::Sound* sound)
    {
		mSound = sound;
    }

    //HRESULT AudioClip::Load(const std::wstring& path)
	//{
	//	std::string cPath(path.begin(), path.end());
	//	if (!Fmod::CreateSound(cPath, &mSound))
	//		return S_FALSE;

	//	mSound->set3DMinMaxDistance(mMinDistance, mMaxDistance);
	//	return S_OK;
	//}
	bool AudioClip::IsPlaying()
    {
		if (nullptr == mSound) return false;
		if (nullptr == mChannel) return false;

		bool isPlaying = false;
		mChannel->isPlaying(&isPlaying);

		return isPlaying;
    }
	void AudioClip::Play()
	{
		if (nullptr == mSound) return;

		if (mbLoop)
			mSound->setMode(FMOD_LOOP_NORMAL);
		else
			mSound->setMode(FMOD_LOOP_OFF);

		mChannel->setVolume(45.f);
		Fmod::SoundPlay(mSound, &mChannel);	
	}

	void AudioClip::PlayRun()
	{
		if (nullptr == mSound) return;

		if (mbLoop)
			mSound->setMode(FMOD_LOOP_NORMAL);
		else
			mSound->setMode(FMOD_LOOP_OFF);

		mChannel->setVolume(45.f);
		Fmod::RunSoundPlay(mSound, &mChannel);
		
	}

	void AudioClip::PlayFire()
	{
		if (nullptr == mSound) return;

		if (mbLoop)
			mSound->setMode(FMOD_LOOP_NORMAL);
		else
			mSound->setMode(FMOD_LOOP_OFF);

		mChannel->setVolume(45.f);
		Fmod::SkillFireSoundPlay(mSound, &mChannel);
	}

	void AudioClip::PlayCrash()
	{
		if (nullptr == mSound) return;

		if (mbLoop)
			mSound->setMode(FMOD_LOOP_NORMAL);
		else
			mSound->setMode(FMOD_LOOP_OFF);

		mChannel->setVolume(45.f);
		Fmod::SkillCrashSoundPlay(mSound, &mChannel);
	}

	void AudioClip::SetVolume(float vol)
    {
		mChannel->setVolume(vol);
    }
	void AudioClip::Stop()
	{
		if (nullptr == mSound) return;

		if(mChannel)
		    mChannel->stop();
	}

	void AudioClip::Set3DAttributes(const Vector3 pos, const Vector3 vel)
	{
        if (nullptr == mSound) return;

		FMOD_VECTOR fmodPos(pos.x, pos.y, pos.z);
		FMOD_VECTOR fmodVel(vel.x, vel.y, vel.z);

		if(mChannel)
		    mChannel->set3DAttributes(&fmodPos, &fmodVel);
	}
}
