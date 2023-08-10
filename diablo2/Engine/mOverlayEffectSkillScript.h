#pragma once
#include "mSkillScript.h"
namespace m
{
    class Animation;
    class OverlayEffectSkillScript :
        public SkillScript
    {
    public:
        OverlayEffectSkillScript(int index);
        virtual ~OverlayEffectSkillScript();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;

        virtual void OnCollisionEnter(Collider2D* other) override;
        virtual void OnCollisionStay(Collider2D* other) override;
        virtual void OnCollisionExit(Collider2D* other) override;

        void UpdateOverlaySkill();

        void PlayOverlaySkill() { bPlaySkill = true; }
    private:
        Animator* mAnimator;
        int skillIndex;
        bool bPlaySkill;
    };
}

