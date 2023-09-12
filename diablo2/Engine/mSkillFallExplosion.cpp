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
		}

		//iniPos;
		//int randX = rand() % (int)randFireArange.x;
		//int randY = rand() % (int)randFireArange.y;
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
		if (bSkillFire)
		{
			updateSkills();
			bSkillFire = false;
		}

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
				for(int i = 0 ; i < 15; ++i)
				{
					int randMaterial = rand() % 3;
					TileAffectOverlay* tileAffectOverlay = new TileAffectOverlay(poss[i]
						, (eAffectOverlayType)randMaterial
						, GetSkillOwnerLayer());

					tileAffectOverlay->SetCamera(GetCamera());
					SceneManager::GetActiveScene()->AddGameObject(GetSkillOwnerLayer(), tileAffectOverlay);
				}


				/*Vector3 pos = GET_POS(this);
				SHARED_MAT fire1Mat = RESOURCE_FIND(Material, L"fire1s");
				SHARED_MAT fire2Mat = RESOURCE_FIND(Material, L"fire2s");
				SHARED_MAT fire3Mat = RESOURCE_FIND(Material, L"fire3s");

				std::vector<std::shared_ptr<Texture>> matTex;
				std::vector<Vector2> matPerSize;

				matTex.push_back(fire1Mat->GetTexture());
				matTex.push_back(fire2Mat->GetTexture());
				matTex.push_back(fire3Mat->GetTexture());

				matPerSize.push_back(Vector2(66, 89));
				matPerSize.push_back(Vector2(66, 167));
				matPerSize.push_back(Vector2(66, 136));

				std::vector<std::wstring> names;
				std::vector<std::shared_ptr<graphics::Texture>> textures;
				std::vector<Vector2> leftTops;
				std::vector<Vector2> sizes;
				std::vector<UINT> columnLengths;
				std::vector<Vector2> offsets;
				std::vector<float> durations;
				std::vector<float> alphas;
				std::vector<Vector3> poss;

				poss.push_back(Vector3(pos.x + 0.f, pos.y + 10.f, pos.z));
				poss.push_back(Vector3(pos.x + 0.f, pos.y + 20.f, pos.z));
				poss.push_back(Vector3(pos.x + 0.f, pos.y + -20.f, pos.z));
				poss.push_back(Vector3(pos.x + 0.f, pos.y + -40.f, pos.z));
				poss.push_back(Vector3(pos.x + -5.f, pos.y + 20.f, pos.z));
				poss.push_back(Vector3(pos.x + -10.f, pos.y + -10.f, pos.z));
				poss.push_back(Vector3(pos.x + -15.f, pos.y + -10.f, pos.z));
				poss.push_back(Vector3(pos.x + -15.f, pos.y + -15.f, pos.z));
				poss.push_back(Vector3(pos.x + -30.f, pos.y + -20.f, pos.z));
				poss.push_back(Vector3(pos.x + -40.f, pos.y + 30.f, pos.z));
				poss.push_back(Vector3(pos.x + 10.f, pos.y + 40.f, pos.z));
				poss.push_back(Vector3(pos.x + 12.f, pos.y + -5.f, pos.z));
				poss.push_back(Vector3(pos.x + 15.f, pos.y + 1.f, pos.z));
				poss.push_back(Vector3(pos.x + 15.f, pos.y + 15.f, pos.z));
				poss.push_back(Vector3(pos.x + 15.f, pos.y + 30.f, pos.z));
				poss.push_back(Vector3(pos.x + 20.f, pos.y + -10.f, pos.z));

				for (int i = 0; i < 15; ++i)
				{
					int randFireIndex = rand() % 3;

					names.push_back(matTex[randFireIndex]->GetKey() + L"anim");
					textures.push_back(matTex[randFireIndex]);
					leftTops.push_back(Vector2::Zero);
					sizes.push_back(matPerSize[randFireIndex]);
					columnLengths.push_back(37);
					offsets.push_back(Vector2::Zero);
					durations.push_back(0.03f);
					alphas.push_back(1.f);
				}


				CreateAnimators(
					15
					, names
					, textures
					, leftTops
					, sizes
					, columnLengths
					, offsets
					, durations
					, alphas
					, poss
				);
				PlayAnimators(names, true, poss);*/
			}
		}
	}
	bool SkillFallExplosion::ReturnCrash()
	{
		return skills[0]->GetSkillCrash();
	}
	void SkillFallExplosion::updateSkills()
	{
		if (mIndicator)
			mIndicator->SetCamera(GetCamera());

		for (int i = 0; i < skills.size(); ++i)
		{
			skills[i]->SetCamera(GetCamera());
			skills[i]->SkillFire();
		}
	}


}
