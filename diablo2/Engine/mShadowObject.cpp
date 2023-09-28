#include "mShadowObject.h"

#include "../engine_source/mMeshRenderer.h"
namespace m
{
    ShadowObject::ShadowObject(GameObject* shadowOwner)
        : mShadowOwner(shadowOwner)
    {
        SET_MESH(this, L"RectMesh");
        SET_MATERIAL(this, L"ShadowAnimationMaterial");
        mAnimator = ADD_COMP(this, Animator);

    }

    ShadowObject::~ShadowObject()
    {
    }

    void ShadowObject::Update()
    {
        GameObject::Update();
        SET_POS_VEC(this, GET_POS(mShadowOwner));
        if (mShadowOwner->GetComponent<Animator>())
        {
            Animator* animator = mShadowOwner->GetComponent<Animator>();
            if(nullptr != animator->GetActiveAnimation())
            {
                if(nullptr != mAnimator->GetActiveAnimation()
                    && mAnimator->GetActiveAnimation()->GetKey() != animator->GetActiveAnimation()->GetKey()
                    )
                mAnimator->PlayAnimation(animator->GetActiveAnimation()->GetKey(), false);
                mAnimator->SetSyncAnimator(animator);
            }
            
        }
    }

    void ShadowObject::LateUpdate()
    {
        GameObject::LateUpdate();
    }

    void ShadowObject::Render()
    {
        GameObject::Render();
    }

    void ShadowObject::Initialize()
    {
        GameObject::Initialize();
    }
}
