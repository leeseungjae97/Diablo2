#include "mSoundManager.h"

#include "mAudioClip.h"
#include "mResources.h"
#include "mGameObject.h"

namespace m
{
    void SoundManager::Initialize()
    {
        for(int i = 0 ; i < (int)eButtonSoundType::End; ++i )
        {
            std::wstring path = buttonAudioPaths[i];
            RESOURCE_LOAD(AudioClip, path, path);
        }

        for (int i = 0; i < (int)ePlayerRunSoundType::End; ++i)
        {
            for(int j = 0 ; j < 4; ++j)
            {
                std::wstring path = playerRunAudioPath[i][j];
                RESOURCE_LOAD(AudioClip, path, path);
            }
        }

    }
    void SoundManager::Play(GameObject* playObject, eButtonSoundType soundType, bool loop)
    {
        if (playObject->SoundPlay()) return;
        playObject->SetSoundPlay(true);

        std::wstring name = buttonAudioMaterialNames[(int)soundType];

        std::shared_ptr<AudioClip> mAudioClip = RESOURCE_FIND(AudioClip, name);

        mAudioClip->Play();
        mAudioClip->SetLoop(loop);
    }

    void SoundManager::Play(GameObject* playObject, const std::wstring& name, bool loop)
    {
        if (playObject->SoundPlay()) return;
        playObject->SetSoundPlay(true);

        std::shared_ptr<AudioClip> mAudioClip = RESOURCE_FIND(AudioClip, name);

        mAudioClip->Play();
        mAudioClip->SetLoop(loop);
    }

    void SoundManager::Play(eButtonSoundType soundType, bool loop)
    {
        std::wstring name = buttonAudioMaterialNames[(int)soundType];

        std::shared_ptr<AudioClip> mAudioClip = RESOURCE_FIND(AudioClip, name);

        mAudioClip->Play();
        mAudioClip->SetLoop(loop);
    }
    void SoundManager::Play(const std::wstring& name, bool loop)
    {
        std::shared_ptr<AudioClip> mAudioClip = RESOURCE_FIND(AudioClip, name);

        mAudioClip->Play();
        mAudioClip->SetLoop(loop);
    }

    void SoundManager::Stop(eButtonSoundType soundType)
    {
        std::wstring name = buttonAudioMaterialNames[(int)soundType];
        std::shared_ptr<AudioClip> mAudioClip = RESOURCE_FIND(AudioClip, name);
        mAudioClip->Stop();
    }

    void SoundManager::Stop(const std::wstring& name)
    {
        std::shared_ptr<AudioClip> mAudioClip = RESOURCE_FIND(AudioClip, name);
        mAudioClip->Stop();
    }
}
