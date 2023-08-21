#pragma once
#include "mGameObject.h"

#include "mHandScript.h"
#include "mTransform.h"
#include "mAnimator.h"
#include "mMeshRenderer.h"
#include "PlayerHandLookUpTables.h"
#include "MonsterHandLookUpTables.h"

namespace m
{
    class Hand :
        public GameObject
    {
    public:
        Hand(GameObject* parent, bool fh);
        virtual ~Hand();

        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;
        virtual void Initialize() override;

        //HandScript* GetHandScript() { return mHandScript; }
        //Animator* GetAnimator() { return mAnimator; }

        void RightHand() { bRightHand = true; }
        void LeftHand() { bRightHand = false; }

    protected:
        HandScript* mHandScript;
        Animator* mAnimator;

        bool bRightHand;
    };
}

