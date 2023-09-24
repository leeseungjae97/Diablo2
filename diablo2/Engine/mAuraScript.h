#pragma once
#include "mScript.h"
#include "SkillAnimLookUpTables.h"

namespace m
{
    class AuraScript :
        public Script
    {
    public:
        AuraScript(eAuraType type, float auraDuration, eLayerType layerType = eLayerType::End);
        virtual ~AuraScript();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;

        void SetAuraCollider(Collider2D* col) { mCol = col; }
        void SetAuraOwner(GameObject* owner) { mAuraOwner = owner; }
        void AuraActive() { bAuraActive = true; }
        void SetAura(eAuraType type, float auraDuration, eLayerType layerType);
    private:
        void colliderCollided();
        void targetDamage();

    private:
        Animator* mAnimator;
        eAuraType mAuraType;
        Collider2D* mCol;
        GameObject* mAuraOwner;
        eLayerType mFireSkillLayer;

        float fCollideAcc;
        float fAcc;
        float mDuration;

        float fAuraValue;
        bool bAuraActive;
        bool bStartCastAnim;

    };
}

