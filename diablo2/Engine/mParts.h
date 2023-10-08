#pragma once
#include "../engine_source/mGameObject.h"

#include "../engine_source/BodyPartsLookUpTables.h"
#include "../engine_source/mMaterial.h"
#include "../engine_source/MoveAbleObjectAnimLookUpTables.h"
#include "../engine_source/mMeshRenderer.h"
namespace m
{
    class Parts :
        public GameObject
    {
    public:
        Parts();
        virtual ~Parts();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;

    protected:
        GameObject* mPartsOwner;
        Animator* mPartsMasterAnimator;
    };
}