#include "mAudioClip.h"

#include "mFmod.h"

namespace m
{
    AudioClip::AudioClip()
        : Resource(enums::eResourceType::AudioClip)
        , mSound(nullptr)
        , mChannel(nullptr)
        , mMinDistance(1.0f)
        , mMaxDistance(1000.0f)
        , mbLoop(false)
    {

    }

    AudioClip::~AudioClip()
    {
    }

	HRESULT AudioClip::Load(const std::wstring& path)
	{
		std::string cPath(path.begin(), path.end());
		if (!Fmod::CreateSound(cPath, &mSound))
			return S_FALSE;

		mSound->set3DMinMaxDistance(mMinDistance, mMaxDistance);
		return S_OK;
	}
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
		if (mbLoop)
			mSound->setMode(FMOD_LOOP_NORMAL);
		else
			mSound->setMode(FMOD_LOOP_OFF);

		Fmod::SoundPlay(mSound, &mChannel);
	}

	void AudioClip::Stop()
	{
		mChannel->stop();
	}

	void AudioClip::Set3DAttributes(const Vector3 pos, const Vector3 vel)
	{
		FMOD_VECTOR fmodPos(pos.x, pos.y, pos.z);
		FMOD_VECTOR fmodVel(vel.x, vel.y, vel.z);

		mChannel->set3DAttributes(&fmodPos, &fmodVel);
	}
}
