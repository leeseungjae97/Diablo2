#pragma once
#include "../engine_source/mScript.h"
#include "../engine_source/mResources.h"
#include "../engine_source/MoveAbleObjectAnimLookUpTables.h"
#include "../engine_source/mGameObject.h"

namespace m
{
    class Monster;
    class Animator;
    template <typename T>
    class MonsterScript :
        public Script
    {
    public:
        MonsterScript();
        virtual ~MonsterScript();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;

        //virtual void OnCollisionEnter(Collider2D* other) override;
        //virtual void OnCollisionStay(Collider2D* other) override;
        //virtual void OnCollisionExit(Collider2D* other) override;
        //void SetMonster(Monster* monster)
        void AttackProgress();
        void AnimationStart(GameObject::eBattleState state);
        void Hit(bool hit, GameObject::eBattleState state);
        void AnimationComplete(GameObject::eBattleState state);
    private:
        T curMonsterData;
        std::vector<SHARED_TEX> texs;
        Animator* mAnimator;
        eMonsterDirection mDirection;
        T::eAnimationType mAnimationType;
        bool bFire;
        bool bDamaged;
        float fDelay;
    };
}

