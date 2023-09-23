#include "mRangeScript.h"

#include "../engine_source/mSceneManager.h"

#include "mMonster.h"
#include "mOverlayEffectSkillScript.h"
#include "mPlayer.h"
#include "mSkillMultiFire.h"
#include "mSkillOverlay.h"

namespace m
{
	RangeScript::RangeScript(eSkillType type, eLayerType layerType)
		: mSkillType(type)
		, mLayerType(layerType)
	    , bActive(false)
	    , bAttackEnd(false)
	{
	}

	RangeScript::~RangeScript()
	{
	}

	void RangeScript::Initialize()
	{
		Script::Initialize();
	}

	void RangeScript::Update()
	{
		Script::Update();
		if(bActive)
		{
			rangeDamage();
		}
		
	}

	void RangeScript::LateUpdate()
	{
		Script::LateUpdate();
	}

	void RangeScript::Render()
	{
		Script::Render();
	}

	void RangeScript::rangeDamage()
	{
		MoveAbleObject* owner = dynamic_cast<MoveAbleObject*>(GetOwner());
		if (nullptr == owner) return;

		Collider2D* mCol = owner->GetRangeCollider();
		if (nullptr == mCol) return;
		if (mCol->GetCollidereds().empty()) return;

		for (Collider2D* col : mCol->GetCollidereds())
		{
			if (col->GetColliderFunctionType() != eColliderFunctionType::HitArea) continue;

			Monster* monster = dynamic_cast<Monster*>(col->GetOwner());

			if (monster)
			{
				OverlayEffectSkillScript* mOESS = monster->GetHSO()->GetComponent<OverlayEffectSkillScript>();
				mOESS->SetSkillType(mSkillType);
				monster->GetHSO()->ActiveOverlay();
				monster->Hit(10);

				SkillMultiFire* skill = new SkillMultiFire(GET_POS(monster), skillAddSkillTypes[(int)mSkillType], 1
					, (int)SkillMultiFire::eFireType::RadialRandomStraight, mLayerType
					, Vector2(0.f, 0.5f), GetOwner()->GetCamera(), true);
				skill->SetCamera(GetOwner()->GetCamera());

				SceneManager::GetActiveScene()->AddGameObject(eLayerType::AdapterSkill, skill);
			}
		}
		bActive = false;
		bAttackEnd = true;
	}
}

