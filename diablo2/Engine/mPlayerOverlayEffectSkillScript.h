#pragma once
#include "mSkillScript.h"
namespace m
{
    class PlayerOverlayEffectSkillScript :
        public SkillScript
    {
    public:
        PlayerOverlayEffectSkillScript();
        virtual ~PlayerOverlayEffectSkillScript();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;

        virtual void OnCollisionEnter(Collider2D* other) override;
        virtual void OnCollisionStay(Collider2D* other) override;
        virtual void OnCollisionExit(Collider2D* other) override;
    private:
        Animator* mAnimator;
        bool m
    };
}

