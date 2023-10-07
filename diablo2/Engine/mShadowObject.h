#pragma once
#include "mGameObject.h"
namespace m
{
    class ShadowObject :
        public GameObject
    {
    public:
        ShadowObject(GameObject* shadowOwner, bool bBMesh = false);
        virtual ~ShadowObject();

        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;
        virtual void Initialize() override;

        void SetShadowOffset(Vector2 offset) { vShadowOffset = offset; }
    private:
        GameObject* mShadowOwner;
        Animation::Sprite mOwnerSprite;
        std::shared_ptr<Texture> mOwnerTexture;

        Vector2 vShadowOffset;
    };
}


