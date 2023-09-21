#include "mOverlayScript.h"

#include "SkillAnimLookUpTables.h"
#include "../engine_source/mMaterial.h"

namespace m
{
    OverlayScript::OverlayScript()
        : mAnimator(nullptr)
        , mDirection(0)
        , mLoop(false)
    {
    }

    OverlayScript::~OverlayScript()
    {
    }

    void OverlayScript::Initialize()
    {
        Script::Initialize();
        mAnimator = GET_COMP(GetOwner(), Animator);
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

        mAnimator->PlayAnimation(L"noneRectAnim", false);
    }

    void OverlayScript::Update()
    {
        Script::Update();
        if(mDirection != -1 )
        {
            if (mAnimator->GetActiveAnimation()
                && mAnimator->GetActiveAnimation()->GetKey() != wsOLname + pathSixteenDirectionString[mDirection])
            {
                mAnimator->PlayAnimation(wsOLname + pathSixteenDirectionString[mDirection], mLoop);
            }
        }else
        {
            if (mAnimator->GetActiveAnimation()
                && mAnimator->GetActiveAnimation()->GetKey() != wsOLname + L"anim")
            {
                mAnimator->PlayAnimation(wsOLname + L"anim", mLoop);
            }
        }
        
    }

    void OverlayScript::LateUpdate()
    {
        Script::LateUpdate();
    }

    void OverlayScript::Render()
    {
        Script::Render();
    }

    void OverlayScript::MakeOverlayAnimation(const std::wstring& overlayName, Vector2 size, Vector2 offset,
        Vector2 centerPos, int length, float duration, bool loop)
    {
        if (overlayName == L"") return;
        wsOLname = overlayName;
        SHARED_MAT mat = RESOURCE_FIND(Material, overlayName);

        SET_SCALE_XYZ(GetOwner(), size.x, size.y, 1.f);
        int directionSize = mat->GetTexture()->GetMetaDataHeight() / size.y;
        int m = 0;
        for(int i = 0 ; i < directionSize;++i)
        {
            std::wstring animName = L"";
            if(directionSize != 1)
            {
                m = pathEightDirections[i];
                animName = overlayName + pathSixteenDirectionString[m];
            }else
            {
                animName = overlayName + L"anim";
            }

            mAnimator->Create(
                animName,
                mat->GetTexture(),
                Vector2(0.f, size.y * i),
                size,
                length,
                offset,
                centerPos,
                duration
            );
        }
        mLoop = loop;
    }

    void OverlayScript::SetSyncPlay(Animator* animator)
    {
        mAnimator->SetSyncAnimator(animator);
    }
}
