#pragma once
#include "mScript.h"
#include "mMaterial.h"

namespace m
{
    class HandScript :
        public Script
    {
    public:
        HandScript(Vector2* sizes, Vector2* offset, int* lens, int maxLen, std::wstring* names);
        virtual ~HandScript();

        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;
        virtual void Initialize() override;

        int GetHandDirection() { return mHandDirection; }
        void SetHandDirection(int direction) { mHandDirection = direction; }
        void SetHandAnimation(int aniType) { mHandAnimationType = aniType; }

        void SetHandSizes(Vector2* vector2s) { mAnimationSize = vector2s; }
        void SetHandLengths(int* arr) { mAnimationLength = arr; }
        void SetAnimationLength(int end) { mAnimationMaxLength = end; }
        void RightHand() { bRightHand = true; }
        void LeftHand() { bRightHand = false; }

        bool GetRightHand() { return bRightHand; }
    protected:
        bool bRightHand;
        Animator* mAnimator;
        int mHandDirection;
        int mHandAnimationType;

        std::wstring* mHandnames;
        std::vector<std::shared_ptr<Material>> mMats;
        Vector2* mAnimationSize;
        Vector2* mAnimationOffset;

        int* mAnimationLength;
        int mAnimationMaxLength;

    };
}

