#include "mSkillChain.h"

#include "../engine_source/mMonsterManager.h"
#include "../engine_source/mSceneManager.h"

#include "mChainScript.h"
#include "mMouseManager.h"
#include "mSkillMultiFire.h"
#include "mSkillStraight.h"

namespace m
{
	SkillChain::SkillChain(eSkillType type, Vector3 initPos, int chainCount, eLayerType layerType, Camera* camera)
		: Skill(type, initPos, false, true)
		, mTarget(nullptr)
		, mPrevTarget(nullptr)
		, bFire(false)
		, mFireLayerType(layerType)
		, iChainCount(chainCount)
		, mCurChainHead(nullptr)
	{
		SetCamera(camera);

		SET_MESH(this, L"PointMesh");
		SET_MATERIAL(this, L"noneRect");


		SkillMultiFire* smf = new SkillMultiFire(GET_POS(this), eSkillType::chainLightning, 10
			, (int)SkillMultiFire::eFireType::HeadDamage, mFireLayerType, Vector2::Zero, GetCamera(), 0.08f);
		Vector3 moPos = MouseManager::UnprojectionMousePos(GET_POS(this).z, GetCamera());
		moPos.z = GET_POS(this).z;
		smf->SetOtherTargetPos(moPos);

		rangeCollider->SetScale(Vector3(500.f, 250.f, 1.f));

		mCurChainHead = smf->GetHeadSkill();
		SceneManager::GetActiveScene()->AddGameObject(eLayerType::AdapterSkill, smf);

		//firstLinearCount(initPos);
		//mCS = AddComponent<ChainScript>(mTarget, mPrevTarget, chainCount);
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
			if (mCurChainHead->GetRangeCollider())
			{
				if (mCurChainHead->GetSkillCrash())
				{
					if(searchChain())
					{
						SkillStraight* ss = new SkillStraight(eSkillType::lightning, GET_POS(mPrevTarget), 300.f);
						ss->SetCamera(GetCamera());
						ss->SkillFire();
						ss->SetDestPosition(GET_POS(mTarget));
						mCurChainHead = ss;
						SceneManager::GetActiveScene()->AddGameObject(mFireLayerType, ss);
					}

					//mTarget->Hit(10);
					//SkillMultiFire* smf = new SkillMultiFire(GET_POS(mPrevTarget), eSkillType::chainLightning, 1
						//, (int)SkillMultiFire::eFireType::HeadDamage, mLayerType, Vector2::Zero, GetCamera(), 0.08f);
					//smf->SetOtherTargetPos(GET_POS(mTarget));
					//mCurChainHead = smf->GetHeadSkill();
					//SceneManager::GetActiveScene()->AddGameObject(eLayerType::AdapterSkill, smf);
				}
				else
				{
					SET_POS_VEC(this, GET_POS(mCurChainHead));
				}
			}
		}else
		{
		    
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

	void SkillChain::firstLinearCount(Vector3 initPos)
	{

	}
	bool SkillChain::searchChain()
	{
		if (iChainCount <= 0)
		{
			SetState(eState::Delete);
			bSkillFire = false;
			return false;
		}
		if(nullptr == mTarget
			&& nullptr == mPrevTarget)
		{
			for(Collider2D* col : mCurChainHead->GetRangeCollider()->GetCollidereds())
			{
				MoveAbleObject* mm = dynamic_cast<MoveAbleObject*>(col->GetOwner());
				if (mm) 
					mTarget = mm;
			}
		}
		MoveAbleObject* minM = nullptr;
		float minDistance = D3D11_FLOAT32_MAX;
		Vector3 pos = GET_POS(this);
		for (Collider2D* col : rangeCollider->GetCollidereds())
		{
			MoveAbleObject* m = dynamic_cast<MoveAbleObject*>(col->GetOwner());
			if (m)
			{
				if (m == mTarget
					|| m == mPrevTarget) continue;

				if (std::find(chainMonsters.begin(), chainMonsters.end(), m)
					!= chainMonsters.end()) continue;
				
				Vector3 otherPos = GET_POS(m);
				float maxX = max(pos.x, otherPos.x);
				float maxY = max(pos.y, otherPos.y);

				float minX = min(pos.x, otherPos.x);
				float minY = min(pos.y, otherPos.y);

				float distance = (Vector2(maxX, maxY) - Vector2(minX, minY)).Length();
				if (minDistance > distance)
				{
					minDistance = distance;
					minM = m;
				}
			}
		}
		if (minM)
		{
			mPrevTarget = mTarget;
			mTarget = minM;
			--iChainCount;
			return true;
		}
		return false;
	}
}
