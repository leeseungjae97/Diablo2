#pragma once
#include "../engine_source/mGameObject.h"

#include "mOverlayEffectSkillScript.h"
namespace m
{
	class SkillOverlay
		: public GameObject
	{
	public:
		SkillOverlay(int index = -1, eSkillCastType ecType = eSkillCastType::END);
		virtual ~SkillOverlay();

		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
		virtual void Initialize() override;

		virtual void ActiveOverlay() { bActiveOverlay = true; }
		void SetActiveOwner(GameObject* owner);
		GameObject* GetActiveOwner() { return mActiveOwner; }
		void SetSkillCastType(eSkillCastType type);
		void SetLoopSecond(float x) { fLoopSecond = x; }

    private:
		int mCurIndex;
		OverlayEffectSkillScript* mOESS;
		eBattleState mOwnerBattleState;
		GameObject* mActiveOwner;
		bool bActiveOverlay;
		float fLoopSecond;
		float fAccLoop;
	};
}

