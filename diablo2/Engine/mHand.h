#pragma once
#include "../engine_source/mGameObject.h"

#include "../engine_source/mTransform.h"
#include "../engine_source/mAnimator.h"
#include "../engine_source/mMeshRenderer.h"
#include "../engine_source/PlayerHandLookUpTables.h"
#include "../engine_source/MonsterHandLookUpTables.h"

#include "mHandScript.h"
#include "mParts.h"

namespace m
{
    class Hand :
        public Parts
    {
    public:
        Hand(GameObject* parent, bool _bRightHand);
        virtual ~Hand();

        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;
        virtual void Initialize() override;

        void RightHand() { bRightHand = true; }
        void LeftHand() { bRightHand = false; }

    protected:
        HandScript* mHandScript;

        bool bRightHand;
    };
}

