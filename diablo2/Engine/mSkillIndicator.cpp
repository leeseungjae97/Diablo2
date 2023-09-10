#include "mSkillIndicator.h"

#include "mMeshRenderer.h"
#include "mSkill.h"

namespace m
{
    SkillIndicator::SkillIndicator(Vector3 initPos, eIndicatorType type)
    {
        ADD_COMP(this, MeshRenderer);
        mAnimator = ADD_COMP(this, Animator);

        SET_MESH(this, L"RectMesh");
        SET_MATERIAL(this, L"AnimationMaterial");

        SET_POS_VEC(this, initPos);
        

        if(type != eIndicatorType::END)
        {
            SHARED_MAT mat = RESOURCE_FIND(Material, indicatorNames[(int)type]);

            SET_SCALE_XYZ(this, indicatorSizes[(int)type].x, indicatorSizes[(int)type].y, initPos.z);

            mAnimator->Create(
                indicatorNames[(int)type] + L"anim"
                , mat->GetTexture()
                , Vector2::Zero
                , indicatorSizes[(int)type]
                , indicatorLength[(int)type]
                , Vector2::Zero
                , 0.03f
            );
        }
        mAnimator->EndEvent(indicatorNames[(int)type] + L"anim") = [this]()
        {
            SetState(eState::Delete);
        };
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
        mAnimator->PlayAnimation(indicatorNames[(int)type] + L"anim", true);
    }

    SkillIndicator::~SkillIndicator()
    {
    }

    void SkillIndicator::Initialize()
    {
        GameObject::Initialize();
    }

    void SkillIndicator::Update()
    {
        GameObject::Update();
        if(mOwner->GetSkillCrash())
        {
            IndicatorOff();
        }
    }

    void SkillIndicator::LateUpdate()
    {
        GameObject::LateUpdate();
    }

    void SkillIndicator::Render()
    {
        GameObject::Render();
    }

    void SkillIndicator::IndicatorOff()
    {
        if(nullptr != mAnimator->GetActiveAnimation()
            && mAnimator->GetActiveAnimation()->GetKey() != L"")
        {
            mAnimator->PlayAnimation(L"noneRectAnim", false);
        }
    }
}
