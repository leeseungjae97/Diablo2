#pragma once
#include "mScript.h"

#include "../engine_source/SummonsLookUpTables.h"

namespace m
{
    class Overlay;
    class Skill;
	template <typename T>
	class SummonsScript :
		public Script
	{
	public:
		
		SummonsScript(float summonTime);
		virtual ~SummonsScript();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void SetAttackDelay(float delay) { fAttackDelay = delay; }
		void SetAnimationType(SummonsData::eSummonsAnimationType type) { mAnimationType = type; }
    private:
		void makeSkill(eSkillType skillType, Vector3 initPos, eLayerType fireLayerType);
		void makeDirection();
        void checkAttack();

    private:
		T curSummonsData;
		SummonsData::eSummonsAnimationType mAnimationType;
		Animator* mAnimator;
		int mDirection;

		Overlay* mOL1;
		Overlay* mOL2;

		float fSummonTime;
		Skill* mSkill;
		bool skillMake;

		float fAttackDelay;
		float fAttackAcc;
	};

}

