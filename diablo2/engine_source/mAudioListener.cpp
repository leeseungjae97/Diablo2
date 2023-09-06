#include "mAudioListener.h"

#include "mFmod.h"
#include "mGameObject.h"
#include "mTransform.h"

namespace m
{
    AudioListener::AudioListener()
        : Component(eComponentType::AudioListener)
    {
        
    }

    AudioListener::~AudioListener()
    {
    }

    void AudioListener::Initialize()
    {
        Component::Initialize();
    }

    void AudioListener::Update()
    {
        Component::Update();
    }

    void AudioListener::LateUpdate()
    {
        Transform* tr = GetOwner()->GetComponent<Transform>();
        Vector3 pos = tr->GetPosition();
        Vector3 foward = tr->Foward();
        Vector3 up = tr->Up();

        Vector3 vel = { 0.0f, 0.0f, 0.0f };
        Fmod::Set3DListenerAttributes(&pos, &vel, &foward, &up);
    }

    void AudioListener::Render()
    {
        Component::Render();
    }
}
