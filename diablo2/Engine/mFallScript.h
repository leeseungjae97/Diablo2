#pragma once
#include "mSkillScript.h"

namespace m
{
	class MoveAbleObject;
	class FallScript :
		public SkillScript
	{
	public:
		FallScript(eAccessorySkillType type = eAccessorySkillType::END, MoveAbleObject* target = nullptr);
		virtual ~FallScript();

		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
		virtual void Initialize() override;

		void SkillFire() { bSkillFire = true; }
		void Arrival() { bArrival = true; }

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;
	private:
		eAccessorySkillType mACType;
		eSkillCrashType mCrashType;
		MoveAbleObject* mTarget;

		bool bSkillFire;
		bool bArrival;
	};
}