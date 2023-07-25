#pragma once
#include "../engine_source/mScript.h"
#include "../engine_source/AnimLookUpTables.h"

namespace m
{
    class Animator;
    class PlayerScript :
        public Script
    {
    public:
        PlayerScript();
        ~PlayerScript();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;

        void Complete();
        void AttackStart();
        void AttackComplete();
    private:
        Animator* mAnimator;
        eCharacterDirection mDirection;
        eSorceressAnimationType mAnimationType;
    };
}

