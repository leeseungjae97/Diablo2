#include "mTorchScript.h"

#include "../engine_source/mMaterial.h"

namespace m
{
    TorchScript::TorchScript(eTorchType type)
        : mAnimator(nullptr)
        , mTorchType(type)
    {
    }

    TorchScript::~TorchScript()
    {
    }

    void TorchScript::Update()
    {
        Script::Update();
    }

    void TorchScript::LateUpdate()
    {
        Script::LateUpdate();
    }

    void TorchScript::Render()
    {
        Script::Render();
    }

    void TorchScript::Initialize()
    {
        Script::Initialize();
        mAnimator = GET_COMP(GetOwner(), Animator);

        SHARED_MAT mat = RESOURCE_FIND(Material, wsTorchNames[(int)mTorchType]);
        mAnimator->Create(
            wsTorchNames[(int)mTorchType] + L"anim",
            mat->GetTexture(),
            Vector2::Zero,
            vTorchSizes[(int)mTorchType],
            iTorchLength[(int)mTorchType],
            Vector2::Zero,
            vTorchCenterPos[(int)mTorchType],
            0.03f
        );
        mAnimator->PlayAnimation(wsTorchNames[(int)mTorchType] + L"anim", true);
    }
}
