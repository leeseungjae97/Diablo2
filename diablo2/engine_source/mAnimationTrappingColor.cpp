#include "mAnimationTrappingColor.h"
namespace m
{
    AnimationTrappingColor::AnimationTrappingColor()
        : Component(eComponentType::MeshRenderer)
    {
    }

    AnimationTrappingColor::~AnimationTrappingColor()
    {
    }

    void AnimationTrappingColor::Initialize()
    {
        Component::Initialize();
    }

    void AnimationTrappingColor::Update()
    {
        Component::Update();
    }

    void AnimationTrappingColor::LateUpdate()
    {
        Component::LateUpdate();
        mTrappingColorBuffer->SetData(&mTrappingColor, 1);
    }

    void AnimationTrappingColor::Render()
    {
        Component::Render();
        mTrappingColorBuffer->Clear();
        mTrappingColorBuffer->BindSRV(eShaderStage::PS, 20);
        mTrappingColorBuffer->BindSRV(eShaderStage::VS, 20);
    }
}
