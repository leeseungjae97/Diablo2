#include "mPortalScript.h"

#include "../engine_source/mMaterial.h"

namespace m
{
    PortalScript::PortalScript()
        : bStartAnim(true)
        , mAnimator(nullptr)
        , bPortal(false)
    {
    }

    PortalScript::~PortalScript()
    {
    }

    void PortalScript::Update()
    {
        Script::Update();
        if(bPortal)
        {
            if (bStartAnim)
            {
                if (mAnimator->GetActiveAnimation()->GetKey() != L"portalStartAnim")
                {
                    SET_SCALE_XYZ(GetOwner(), 204.f, 204.f, 1.f);
                    mAnimator->PlayAnimation(L"portalStartAnim", false);
                }
            }
            else
            {
                if (mAnimator->GetActiveAnimation()->GetKey() != L"portalLoopAnim")
                {
                    SET_SCALE_XYZ(GetOwner(), 115.f, 154.f, 1.f);
                    mAnimator->PlayAnimation(L"portalLoopAnim", true);
                }
            }
        }
        
    }

    void PortalScript::LateUpdate()
    {
        Script::LateUpdate();
    }

    void PortalScript::Initialize()
    {
        Script::Initialize();
        mAnimator = GET_COMP(GetOwner(), Animator);
        SHARED_MAT mat = RESOURCE_FIND(Material, L"portalStart");

        mAnimator->Create(
            L"portalStartAnim",
            mat->GetTexture(),
            Vector2::Zero,
            Vector2(204.f, 204.f),
            15,
            Vector2::Zero,
            0.03f
        );

        SHARED_MAT mat2 = RESOURCE_FIND(Material, L"portalLoop");
        mAnimator->Create(
            L"portalLoopAnim",
            mat2->GetTexture(),
            Vector2::Zero,
            Vector2(115.f, 154.f),
            15,
            Vector2::Zero,
            0.03f
        );
        SHARED_MAT noneMat = RESOURCE_FIND(Material, L"noneRect");
        mAnimator->Create(
            L"noneRectAnim"
            , noneMat->GetTexture()
            , Vector2::Zero
            , Vector2(20.f, 20.f)
            , 1
            , Vector2::Zero
            , 0.03f
        );

        mAnimator->PlayAnimation(L"noneRectAnim", true);

        mAnimator->EndEvent(L"portalStartAnim") = [=]()
        {
            bStartAnim = false;
        };
    }

    void PortalScript::Render()
    {
        Script::Render();
    }
}
