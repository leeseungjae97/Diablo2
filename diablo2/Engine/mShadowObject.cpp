#include "mShadowObject.h"

#include "../engine_source/mRenderer.h"
#include "../engine_source/mMeshRenderer.h"
namespace m
{
    ShadowObject::ShadowObject(GameObject* shadowOwner, bool bBMesh, bool _bMergeShadow)
        : mShadowOwner(shadowOwner)
        , vShadowOffset(Vector2::One)
        , bMergerShadow(_bMergeShadow)
    {
        ADD_COMP(this, MeshRenderer);
        if(bBMesh)
            SET_MESH(this, L"BPMesh");
        else
            SET_MESH(this, L"PMesh");
        if(!_bMergeShadow)
            SET_MATERIAL(this, L"ShadowAnimationMaterial");
        else
        {
            mergerMaterial = std::make_shared<Material>();

            std::shared_ptr<Shader> shader = RESOURCE_FIND(Shader, L"ShadowSpriteShader");
            mergerMaterial->SetShader(shader);
            mergerMaterial->SetRenderingMode(eRenderingMode::Transparent);

            SET_MATERIAL_D(this, mergerMaterial);
            //SET_MATERIAL(this, L"testSc");
        }
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
        if(vShadowOffset != Vector2::One)
        {
            pos.x += vShadowOffset.x;
            pos.y += vShadowOffset.y;
        }
        SET_SCALE_VEC(this, scale);
        SET_POS_VEC(this, pos);

        if(bMergerShadow)
        {
            
        }else
        {
            Animator* animator = mShadowOwner->GetComponent<Animator>();
            if (animator && nullptr != animator->GetActiveAnimation())
            {
                mOwnerTexture = animator->GetActiveAnimation()->GetAtlas();
                mOwnerSprite = animator->GetActiveAnimation()->GetCurrentSprite();
            }
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
        }else
        {
            if(mergerMaterial)
                SET_MATERIAL_D(this, mergerMaterial);
        }
        GameObject::Render();
    }

    void ShadowObject::Initialize()
    {
        GameObject::Initialize();
    }

    void ShadowObject::AddMergeTexture(std::shared_ptr<Texture> tex, Vector2 pos)
    {
        shadowMerger.push_back(tex);
        mergerPos.push_back(pos);
    }

    void ShadowObject::MakeMergerShadow()
    {
        std::shared_ptr<Texture> mergeTexture = std::make_shared<Texture>();
        mergeTexture->MergeTex2(shadowMerger, mergerPos, 200, 500);

        //std::shared_ptr<Texture> tt = RESOURCE_FIND(Texture, L"test_sc");
        if(mergerMaterial->GetTexture())
            mergerMaterial->GetTexture()->Clear();

        mergerMaterial->SetTexture(mergeTexture);

        mergerPos.clear();
        shadowMerger.clear();
    }
}
