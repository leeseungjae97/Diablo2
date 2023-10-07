#pragma once
#include "mSkill.h"
#include "../engine_source/mScript.h"
#include "../engine_source/MoveAbleObjectAnimLookUpTables.h"
#include "../engine_source/mGameObject.h"

#include "mMonsterHand.h"

namespace m
{
	class Aura;
    class SkillOverlay;
    class SkillBuff;
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

		void MakeDirection();
		void SpecialAttackAnimationConitnue();
		void SpecialAttackAnimation(int skillIndex);
		void DeadAnimation();
		void AttackAnimation();
		void HitAnimation();
		void ElseAnimationPlay();
		//virtual void OnCollisionEnter(Collider2D* other) override;
		//virtual void OnCollisionStay(Collider2D* other) override;
		//virtual void OnCollisionExit(Collider2D* other) override;
		//void SetMonster(Monster* monster)
		void AttackProgress();
		void AnimationStart(GameObject::eBattleState state);
		void Hit(bool hit, GameObject::eBattleState state);
		void AnimationComplete(GameObject::eBattleState state);

		Skill* GetSkill() { return mSkill; }
		void SetSkill(Skill* skill) { mSkill = skill; }

		eMonsterClass GetMonsterClass() { return mClass; }

		int GetDirection() { return mDirection; }
		float GetDegree() { return degree; }

		Aura* GetAura() { return mAura; }

		T GetcurMonsterData() { return curMonsterData; }

		void SetCenterPosY();
    private:
		void makeSkillCastAnimation(int type, int direction);
		void makeMonsterSkill(eSkillType skillType, Vector3 vector3Pos
			, eLayerType fireLayerType, int addFunction, int skillCount);
		Collider2D* getSkillActiveCollider();

	private:
		T curMonsterData;

		std::vector<SHARED_TEX> texs;
		Animator* mAnimator;
		T::eAnimationType mAnimationType;
		std::wstring wsDiabloDeadAnimationName;

		Skill* mSkill;
		SkillBuff* mSkillBuff;
		bool skillMake;
		int iCurSkillIndex;

		MonsterHand* mLeftHand;
		MonsterHand* mRightHand;

		Aura* mAura;

		Monster* mMonster;
		eMonsterClass mClass;

		int mDirection;
		int* mPlusDirections;
		int* mMinusDirections;
		
		std::wstring* animStrings;

		bool bFire;
		float fAttackDelay;
		float degree;

		float fSkillCenterPosY;
	};
}

