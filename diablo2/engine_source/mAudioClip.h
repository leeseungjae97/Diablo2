#pragma once
#include "mResource.h"
#include "SoundLookUpTables.h"

namespace FMOD
{
    class Sound;
    class Channel;
}

namespace m
{
    class AudioClip
    {
    public:
        AudioClip();
        virtual ~AudioClip();

        //virtual HRESULT Load(const std::wstring& path);
        void SetSound(FMOD::Sound* sound);

        void Play();
        void PlayCrash();
        void PlayFire();
        void PlayRun();
        void PlayExtern();

        void Stop();
        void SetVolume(float vol);
        void Set3DAttributes(const Vector3 pos, const Vector3 vel);
        void SetLoop(bool loop) { mbLoop = loop; }
        bool IsPlaying();

        FMOD::Sound* GetSound();

    private:
        FMOD::Channel* mChannel;
        FMOD::Sound* mSound;
        //std::wstring mPath;
        //std::map<std::wstring, FMOD::Sound*> mSounds;
        float mMinDistance;
        float mMaxDistance;
        bool mbLoop;

    };
}

