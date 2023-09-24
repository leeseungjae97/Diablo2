#include "mSkillChain.h"

#include "../engine_source/mMonsterManager.h"
#include "../engine_source/mSceneManager.h"

#include "mChainScript.h"
#include "mMouseManager.h"
#include "mSkillMultiFire.h"

namespace m
{
	SkillChain::SkillChain(eSkillType type, Vector3 initPos, int chainCount, eLayerType layerType, Camera* camera)
		: Skill(type, initPos)
		, mTarget(nullptr)
		, mPrevTarget(nullptr)
	    , bFire(false)
	    , mLayerType(layerType)
	    , iChainCount(chainCount)
	{
		SetCamera(camera);

		SET_MESH(this, L"PointMesh");
		SET_MATERIAL(this, L"noneRect");

		//AddComponent<ChainScript>();
	}

	SkillChain::~SkillChain()
	{
	}

	void SkillChain::Initialize()
	{
		Skill::Initialize();
	}

	void SkillChain::Update()
	{
		Skill::Update();
		if(bSkillFire)
		{
			if(!bFire)
		    {
				SkillMultiFire* smf = new SkillMultiFire(GET_POS(this), eSkillType::chainLightning, 20
					, (int)SkillMultiFire::eFireType::HeadDamage, mLayerType, Vector2::Zero, GetCamera(), 0.08f);
				Vector3 moPos = MouseManager::UnprojectionMousePos(GET_POS(this).z, GetCamera());
				moPos.z = GET_POS(this).z;
				smf->SetOtherTargetPos(moPos);
				SceneManager::GetActiveScene()->AddGameObject(eLayerType::AdapterSkill, smf);
				bFire = true;
			}else
			{
				if (searchChain())
				{
					//SkillMultiFire* smf = new SkillMultiFire(GET_POS(mPrevTarget), eSkillType::chainLightning, iChainMissileCount
					//	, (int)SkillMultiFire::eFireType::FixedLinear, mLayerType, Vector2::Zero, GetCamera(), 0.08f);
					//SceneManager::GetActiveScene()->AddGameObject(eLayerType::AdapterSkill, smf);
				}
			}
		}
		
	}

	void SkillChain::LateUpdate()
	{
		Skill::LateUpdate();
	}

	void SkillChain::Render()
	{
		Skill::Render();
	}

	bool SkillChain::searchChain()
	{
		if (iChainCount <= 0)
		{
			SetState(eState::Delete);
			bSkillFire = false;
			return false;
		}

		Vector2 skillSize = skillSizes[(int)mSkillType];
		if (mTarget)
		{
			Vector3 pos = GET_POS(mTarget);

			float minDistance = D3D11_FLOAT32_MAX;
			Monster* minMonster = nullptr;
			for (Monster* monster : MonsterManager::monsters)
			{
				if (monster == mTarget
					|| monster ==mPrevTarget) continue;

				if (std::find(chainMonsters.begin(), chainMonsters.end(), monster)
					!= chainMonsters.end()) continue;

				chainMonsters.push_back(monster);

				Vector3 otherPos = GET_POS(monster);
				float maxX = max(pos.x, otherPos.x);
				float maxY = max(pos.y, otherPos.y);

                float minX = min(pos.x, otherPos.x);
                float minY = min(pos.y, otherPos.y);

                float distance = (Vector2(maxX, maxY) - Vector2(minX, minY)).Length();
				if(minDistance > distance)
				{
					minDistance = distance;
					minMonster = monster;
				}
			}
			if(minMonster)
			{
				float skillLen = skillSize.Length();
				iChainMissileCount = minDistance / skillLen;
				mPrevTarget = mTarget;
				mTarget = minMonster;
				--iChainCount;
				return true;
			}
			return false;
		}
		return false;
	}
}
