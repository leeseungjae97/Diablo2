#pragma once
#include "mSkillScript.h"
namespace m
{
    class OverlayEffectSkillScript :
        public SkillScript
    {
    public:
        OverlayEffectSkillScript();
        virtual ~OverlayEffectSkillScript();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;

        virtual void OnCollisionEnter(Collider2D* other) override;
        virtual void OnCollisionStay(Collider2D* other) override;
        virtual void OnCollisionExit(Collider2D* other) override;

        void SetSkillIndex(int index) { skillIndex = index; }
        int GetSkillIndex() { return skillIndex; }
    private:
        Animator* mAnimator;
        int skillIndex;
    };
}

