#pragma once
#include "../engine_source/mScript.h"
#include "../engine_source/MoveAbleObjectAnimLookUpTables.h"
#include "../engine_source/mGameObject.h"

#include "mOverlayEffectSkillScript.h"
#include "mSkill.h"
#include "mSkillBuff.h"
#include "mSkillOverlay.h"
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
        void MakeDirection();
        void SpecialCastAnimation(int skillIndex);
        void ElseAnimationPlay();
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;

        void Complete();
        void AnimationStart(GameObject::eBattleState state);
        void AnimationComplete(GameObject::eBattleState state);
        
        void Hit(bool hit, GameObject::eBattleState state);
        void AttackProgress();

        int GetDirection() { return mDirection; }
        //virtual void OnCollisionEnter(Collider2D* other) override;
        //virtual void OnCollisionStay(Collider2D* other) override;
        //virtual void OnCollisionExit(Collider2D* other) override;

        SkillOverlay* GetHSO() { return mHSO; }
        SkillOverlay* GetRSO() { return mRSO; }
        SkillOverlay* GetLSO() { return mLSO; }

    private:
        void makeSkill(eSkillType skill
            , int activeSkillIndex
            , Vector3 vector3Pos
            , eLayerType fireLayer);

    private:
        Animator* mAnimator;
        int mDirection;
        ePlayerAnimationType mAnimationType;

        SkillOverlay* mRSO;
        SkillOverlay* mLSO;
        SkillOverlay* mHSO;

        int activeSkillIndex;
        bool bFire;
    };
}

