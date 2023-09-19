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

        void SetAuraCollider(Collider2D* col) { mCol = col; }
        void SetAuraOwner(GameObject* owner) { mAuraOwner = owner; }

    private:
        void colliderCollided();
    private:
        Animator* mAnimator;
        eAuraType mAuraType;
        Collider2D* mCol;
        GameObject* mAuraOwner;

        float fCollideAcc;
        float fAcc;
        float mDuration;
    };
}

