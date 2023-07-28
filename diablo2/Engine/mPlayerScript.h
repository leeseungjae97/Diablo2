#pragma once
#include "../engine_source/mScript.h"
#include "../engine_source/AnimLookUpTables.h"
#include "../engine_source/mGameObject.h"

namespace m
{
    class GameObject;
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
        void AnimationStart(GameObject::eBattleState state);
        void AnimationComplete(GameObject::eBattleState state);

        //virtual void OnCollisionEnter(Collider2D* other) override;
        //virtual void OnCollisionStay(Collider2D* other) override;
        //virtual void OnCollisionExit(Collider2D* other) override;
    private:
        Animator* mAnimator;
        eCharacterDirection mDirection;
        eSorceressAnimationType mAnimationType;
    };
}

