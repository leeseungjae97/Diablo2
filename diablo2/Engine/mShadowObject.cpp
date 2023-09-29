#include "mShadowObject.h"

#include "../engine_source/mRenderer.h"
#include "../engine_source/mMeshRenderer.h"
namespace m
{
    ShadowObject::ShadowObject(GameObject* shadowOwner)
        : mShadowOwner(shadowOwner)
    {
        ADD_COMP(this, MeshRenderer);
        SET_MESH(this, L"PMesh");
        SET_MATERIAL(this, L"ShadowAnimationMaterial");
        float theta = DegreeToRadian(45.f);
        //GetComponent<Transform>()->SetRotation(0.f, 0.f, theta);
    }

    ShadowObject::~ShadowObject()
    {
    }

    void ShadowObject::Update()
    {
        GameObject::Update();

        Vector3 pos = GET_POS(mShadowOwner);
        Vector3 scale = GET_SCALE(mShadowOwner);
        //pos.x -= scale.x /2.f;
        SET_SCALE_VEC(this, scale);
        SET_POS_VEC(this, pos);
        Animator* animator = mShadowOwner->GetComponent<Animator>();
        if (animator && nullptr != animator->GetActiveAnimation())
        {
            mOwnerTexture = animator->GetActiveAnimation()->GetAtlas();
            mOwnerSprite = animator->GetActiveAnimation()->GetCurrentSprite();
        }
    }

    void ShadowObject::LateUpdate()
    {
        GameObject::LateUpdate();
    }

    void ShadowObject::Render()
    {
        if (mOwnerTexture)
        {
            mOwnerTexture->BindShaderResource(eShaderStage::PS, 16);

            // AnimationCB
            renderer::AnimatorCB data = {};

            data.spriteLeftTop = mOwnerSprite.leftTop;
            data.spriteSize = mOwnerSprite.size;
            data.spriteOffset = mOwnerSprite.offset;
            data.atlasSize = mOwnerSprite.atlasSize;
            data.spriteOffsetOfCenterPos = mOwnerSprite.offsetOfCenterPos;
            data.animationType = 1;
            data.alpha = mOwnerSprite.alpha;

            ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Animator];
            cb->SetData(&data);

            cb->Bind(eShaderStage::VS);
            cb->Bind(eShaderStage::PS);
        }
        GameObject::Render();
    }

    void ShadowObject::Initialize()
    {
        GameObject::Initialize();
    }
}
