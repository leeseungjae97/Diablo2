#include "mSkillFallExplosion.h"

#include "../engine_source/mSceneManager.h"

#include "mSkillOverlay.h"
#include "mSkillIndicator.h"
#include "mTileAffectOverlay.h"

namespace m
{
	SkillFallExplosion::SkillFallExplosion(eSkillType type, Vector3 iniPos, eLayerType layerType)
		: Skill(type, iniPos)
		, mIndicator(nullptr)
	    , bAfterFall(false)
	{
		SET_MESH(this, L"PointMesh");
		SET_MATERIAL(this, L"noneRect");
		Vector3 initYpos = iniPos;
		initYpos.y += 1000.f;
		SetSkillOwnerLayer(layerType);

		SkillFall* body = new SkillFall(type, initYpos, 1000.f, true);
		SceneManager::GetActiveScene()->AddGameObject(layerType, body);
		body->Initialize();
		body->SetSpeed(1000.f / 2.f);
		skills.push_back(body);

		if (type == eSkillType::meteor)
		{
			Vector3 meteorHeadPos = Vector3(
				initYpos.x + 10.f
				, initYpos.y - 29.f
				, iniPos.z);
			SkillFall* acc = new SkillFall(type, meteorHeadPos, 1000.f
				, true, true
				, eAccessorySkillType::MeteorHead);
			acc->SetSpeed(1000.f / 2.f);
			skills.push_back(acc);
			SceneManager::GetActiveScene()->AddGameObject(layerType, acc);

			mIndicator = new SkillIndicator(iniPos, eIndicatorType::MeteorTargetIndicator);
			mIndicator->SetOwnerSkill(body);
			SceneManager::GetActiveScene()->AddGameObject(layerType, mIndicator);
			makeAffectOverlay(layerType);
		}
	}

	SkillFallExplosion::~SkillFallExplosion()
	{
	}
	void SkillFallExplosion::Initialize()
	{
		Skill::Initialize();
	}
	void SkillFallExplosion::Update()
	{
		Skill::Update();
		if(nullptr == overlays[0]->GetCamera())
		{
			for (TileAffectOverlay* tao : overlays)
				tao->SetCamera(GetCamera());
		}
		
		updateSkills();

		afterFall();
	}

	void SkillFallExplosion::LateUpdate()
	{
		Skill::LateUpdate();
	}

	void SkillFallExplosion::Render()
	{
		Skill::Render();
	}
	void SkillFallExplosion::afterFall()
	{
		if (bAfterFall) return;

		if (skills[0]->GetSkillCrash())
		{
			if (mSkillType == eSkillType::meteor)
			{
				bAfterFall = true;
				activeAffectOverlay();
			}
		}
	}
	void SkillFallExplosion::activeAffectOverlay()
	{
		for (TileAffectOverlay* tao : overlays)
		{
			tao->SetCamera(GetCamera());
			tao->ActiveOverlay();
		}
	}
	void SkillFallExplosion::makeAffectOverlay(eLayerType type)
	{
		Vector3 pos = GET_POS(this);
		Vector3 poss[15] = {
			Vector3(pos.x + 0.f, pos.y + 10.f, pos.z),
			Vector3(pos.x + 0.f, pos.y + 20.f, pos.z),
			Vector3(pos.x + 0.f, pos.y + -20.f, pos.z),
			Vector3(pos.x + 0.f, pos.y + -40.f, pos.z),
			Vector3(pos.x + -15.f, pos.y + 20.f, pos.z),
			Vector3(pos.x + -30.f, pos.y + -10.f, pos.z),
			Vector3(pos.x + -15.f, pos.y + -10.f, pos.z),
			Vector3(pos.x + -15.f, pos.y + -15.f, pos.z),
			Vector3(pos.x + -30.f, pos.y + -20.f, pos.z),
			Vector3(pos.x + -40.f, pos.y + 30.f, pos.z),
			Vector3(pos.x + 10.f, pos.y + 40.f, pos.z),
			Vector3(pos.x + 12.f, pos.y + -5.f, pos.z),
			Vector3(pos.x + 15.f, pos.y + 1.f, pos.z),
			Vector3(pos.x + 15.f, pos.y + 15.f, pos.z),
			Vector3(pos.x + 15.f, pos.y + 30.f, pos.z),
		};
		for (int i = 0; i < 15; ++i)
		{
			int randMaterial = rand() % 3;
			TileAffectOverlay* tileAffectOverlay = new TileAffectOverlay(poss[i]
				, (eAffectOverlayType)randMaterial
				, type);

			overlays.push_back(tileAffectOverlay);
			SceneManager::GetActiveScene()->AddGameObject(type, tileAffectOverlay);
		}
	}
	void SkillFallExplosion::updateSkills()
	{
		if (!bSkillFire) return;

		bSkillFire = false;

		if (mIndicator)
			mIndicator->SetCamera(GetCamera());

		for (int i = 0; i < skills.size(); ++i)
		{
			skills[i]->SetCamera(GetCamera());
			skills[i]->SkillFire();
		}
	}


}
