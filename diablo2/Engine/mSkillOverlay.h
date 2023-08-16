#pragma once
#include "../engine_source/mGameObject.h"

#include "mOverlayEffectSkillScript.h"
namespace m
{
	class SkillOverlay
		: public GameObject
	{
	public:
		SkillOverlay(int index = -1);
		virtual ~SkillOverlay();

		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
		virtual void Initialize() override;

		void ActiveOverlay() { bActiveOverlay = true; }

		void SetActiveOwner(GameObject* owner);
	private:
		int mCurIndex;
		OverlayEffectSkillScript* mOESS;
		eBattleState mOwnerBattleState;
		GameObject* mActiveOwner;
		bool bActiveOverlay;
	};
}

