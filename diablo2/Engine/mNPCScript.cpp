#include "mNPCScript.h"

#include "mMaterial.h"

namespace m
{
    NPCScript::NPCScript(eNPCType type)
        : mNPCType(type)
    {
    }

    NPCScript::~NPCScript()
    {
    }

    void NPCScript::Initialize()
    {
        Script::Initialize();
        mAnimator = GET_COMP(GetOwner(), Animator);

        SHARED_MAT mat = RESOURCE_FIND(Material, NPCMaterialNames[(int)mNPCType]);
        //if (nullptr == mat) return;

        mAnimator->Create(
            NPCMaterialNames[(int)mNPCType] + L"anim",
            mat->GetTexture(),
            Vector2::Zero,
            NPCSizes[(int)mNPCType],
            NPCLength[(int)mNPCType],
            NPCOffsets[(int)mNPCType],
            NPCCenterPos[(int)mNPCType],
            0.03f
        );
        SET_SCALE_XYZ(GetOwner(), NPCSizes[(int)mNPCType].x, NPCSizes[(int)mNPCType].y, 1.f);
        mAnimator->PlayAnimation(NPCMaterialNames[(int)mNPCType] + L"anim", true);
    }

    void NPCScript::Update()
    {
        Script::Update();
    }

    void NPCScript::LateUpdate()
    {
        Script::LateUpdate();
    }

    void NPCScript::Render()
    {
        Script::Render();
    }
}
