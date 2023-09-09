#pragma once
#include "mSkill.h"
#include "../engine_source/mScript.h"
#include "../engine_source/MoveAbleObjectAnimLookUpTables.h"
#include "../engine_source/mGameObject.h"

#include "mMonsterHand.h"

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

		Skill* GetSkill() { return mSkill; }
		void SetSkill(Skill* skill) { mSkill = skill; }

		eMonsterClass GetMonsterClass() { return mClass; }

		int GetDirection() { return mDirection; }
		float GetDegree() { return degree; }
	private:
		T curMonsterData;
		std::vector<SHARED_TEX> texs;
		Animator* mAnimator;
		T::eAnimationType mAnimationType;

		Skill* mSkill;
		MonsterHand* mLeftHand;
		MonsterHand* mRightHand;

		Monster* mMonster;
		eMonsterClass mClass;

		int mDirection;
		int* mPlusDirections;
		int* mMinusDirections;
		std::wstring* animStrings;

		bool bFire;
		bool bDamaged;
		float fDelay;
		float degree;
	};
}

