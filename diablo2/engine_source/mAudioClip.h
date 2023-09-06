#pragma once
#include "mResource.h"

namespace FMOD
{
    class Sound;
    class Channel;
}

namespace m
{
    class AudioClip :
        public Resource
    {
    public:
        AudioClip();
        virtual ~AudioClip();

        virtual HRESULT Load(const std::wstring& path) override;

        void Play();
        void Stop();
        void Set3DAttributes(const Vector3 pos, const Vector3 vel);
        void SetLoop(bool loop) { mbLoop = loop; }

    private:
        FMOD::Sound* mSound;
        FMOD::Channel* mChannel;
        float mMinDistance;
        float mMaxDistance;
        bool mbLoop;

    };
}

