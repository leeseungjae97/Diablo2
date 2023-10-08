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

        void ChangeHead();

        void SetAnimationType(int animationType) { mAnimationType = animationType; }
        void SetDirection(int direction) { mDriection = direction; }

    private:
        eBodyPartsType mBodyPartsType;
        GameObject* mPartsOwner;
        Animator* mAnimator;
        int mDriection;
        int mAnimationType;
    };
}

