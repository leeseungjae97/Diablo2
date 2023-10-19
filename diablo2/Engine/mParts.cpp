#include "mParts.h"

#include "mMeshRenderer.h"
#include "mShadowObject.h"

namespace m
{
    Parts::Parts()
        : mPartsOwner(nullptr)
        , mPartsMasterAnimator(nullptr)
        , mShadow(nullptr)
    {
        MeshRenderer* mr = ADD_COMP(this, MeshRenderer);
        mr->AddTrappingColorBuffer();

        ADD_COMP(this, Animator);
    }

    Parts::~Parts()
    {
        if (mShadow)
            mShadow->SetState(Delete);
    }

    void Parts::Initialize()
    {
        GameObject::Initialize();
    }

    void Parts::Update()
    {
        GameObject::Update();
    }

    void Parts::LateUpdate()
    {
        GameObject::LateUpdate();
    }

    void Parts::Render()
    {
        GameObject::Render();
    }
}
