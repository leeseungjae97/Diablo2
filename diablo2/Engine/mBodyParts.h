#pragma once
#include "mParts.h"

namespace m
{
    class BodyParts :
        public Parts
    {
    public:
        BodyParts(eBodyPartsType type, GameObject* _mPartsOwner);
        virtual ~BodyParts();
        virtual void Initialize() override;
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;

        void SetAnimationType(int animationType) { mAnimationType = animationType; }
        void SetDirection(int direction) { mDirection = direction; }

    private:
        void imageChangeEquiment();
        void changeAnimation();

        void shadowOffset();
        void partLeftDirectionAddZWeight(float* z);
        void partRightDirectionAddZWeight(float* z);
        void partAddZWeight();
        
    private:
        eBodyPartsType mBodyPartsType;
        GameObject* mPartsOwner;
        Animator* mAnimator;
        int mDirection;
        int mAnimationType;

        int iCurItem;
        int iPrevItem;

        Vector2* vCurSizes;
        Vector2* vPartsOffset;
        std::wstring* wsCurNames;
    };
}

