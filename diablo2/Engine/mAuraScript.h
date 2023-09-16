#pragma once
#include "mScript.h"
#include "SkillAnimLookUpTables.h"

namespace m
{
    class AuraScript :
        public Script
    {
    public:
        AuraScript(eAuraType type, float auraDuration);
        virtual ~AuraScript();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;

        virtual void OnCollisionEnter(Collider2D* other);
        virtual void OnCollisionStay(Collider2D* other);
        virtual void OnCollisionExit(Collider2D* other);
    private:
        Animator* mAnimator;
        eAuraType mAuraType;

        float fCollideAcc;
        float fAcc;
        float mDuration;
    };
}

