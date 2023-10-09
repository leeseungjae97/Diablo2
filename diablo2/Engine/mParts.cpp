#include "mParts.h"

#include "mMeshRenderer.h"

namespace m
{
    Parts::Parts()
        : mPartsOwner(nullptr)
        , mPartsMasterAnimator(nullptr)

    {
        ADD_COMP(this, MeshRenderer);
        ADD_COMP(this, Animator);
    }

    Parts::~Parts()
    {
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

    Vector2 Parts::GetSpriteSize()
    {
        Animator* animator = GET_COMP(this, Animator);

        if (animator)
        {
            if (animator->GetActiveAnimation())
            {
                Animation* animation = animator->GetActiveAnimation();
                Animation::Sprite sprite = animation->GetCurrentSprite();
                UINT tWid = animation->GetAtlas()->GetMetaDataWidth();
                UINT tHei = animation->GetAtlas()->GetMetaDataHeight();
                return Vector2(sprite.size.x * tWid, sprite.size.y * tHei);
            }
        }
        return Vector2::Zero;
    }
}
