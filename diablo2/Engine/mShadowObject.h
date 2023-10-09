#pragma once
#include "mGameObject.h"
namespace m
{
    namespace graphics
    {
        class Material;
    }

    class ShadowObject :
        public GameObject
    {
    public:
        ShadowObject(GameObject* shadowOwner, bool bBMesh = false, bool _bMergeShadow = false);
        virtual ~ShadowObject();

        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;
        virtual void Initialize() override;

        void SetShadowOffset(Vector2 offset) { vShadowOffset = offset; }

        void AddMergeTexture(std::shared_ptr<Texture> tex, Vector2 pos);
        void MakeMergerShadow();
    private:
        GameObject* mShadowOwner;
        Animation::Sprite mOwnerSprite;
        std::shared_ptr<Texture> mOwnerTexture;

        std::vector<std::shared_ptr<Texture>> shadowMerger;
        std::vector<Vector2> mergerPos;

        std::shared_ptr<Material> mergerMaterial;

        bool bMergerShadow;
        Vector2 vShadowOffset;
    };
}


