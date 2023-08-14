#include "mSkillMultiFire.h"

#include "../engine_source/mSceneManager.h"
#include "../engine_source/mMeshRenderer.h"
#include "../engine_source/mTime.h"

namespace m
{
	SkillMultiFire::SkillMultiFire(
		eSkillType type,
		Vector3 iniPos,
		int count,
		eFireType fireType,
		Vector2 randFireArange
	)
		: Skill(type, iniPos)
		, mFireType(fireType)
		, curFallIndex(0)
		, mAccTime(0.f)
	{
		std::default_random_engine generator(std::time(nullptr));
		SET_MESH(this, L"PointMesh");
		SET_MATERIAL(this, L"AnimationMaterial");
		
		for (int i = 0; i < count; ++i)
		{
			Vector3 startPos = iniPos;
			if (mFireType == eFireType::Random)
			{
				int randX = rand() % (int)randFireArange.x;
				int randY = rand() % (int)randFireArange.y;
				int randSignX = rand() % 2;
				int randSignY = rand() % 2;
				if (randSignX)randX *= -1;
				if (randSignY)randY *= -1;

				startPos.x += (float)randX;
				startPos.y += (float)randY;

				std::uniform_real_distribution<float> distribution(0.0f, 0.5f);
				mSkillFireTimes.push_back(distribution(generator));
			}
			if (mFireType == eFireType::Linear)
			{
				mSkillFireTimes.push_back(0.5f);
			}
			SkillFall* sf = new SkillFall(type, startPos);
			SceneManager::GetActiveScene()->AddGameObject(eLayerType::Skill, sf);
			skills.push_back(sf);
		}
		
	}
	SkillMultiFire::~SkillMultiFire()
	{
	}
	void SkillMultiFire::Initialize()
	{
		Skill::Initialize();
	}
	void SkillMultiFire::Update()
	{
		Skill::Update();
		if (nullptr == skills.front()->GetCamera())
		{
			for (SkillFall* sf : skills) sf->SetCamera(GetCamera());
		}
		if (mFireType == eFireType::Random)
		{
			if (mSkillFireTimes.size() == curFallIndex)
			{
				mFireType = eFireType::END;
				SetState(GameObject::eState::Delete);
				return;
			}
			mAccTime += Time::fDeltaTime();			
			if (math::areAlmostEqual(mAccTime, mSkillFireTimes[curFallIndex]))
			{
				skills[curFallIndex]->SkillFire();
				++curFallIndex;
				mAccTime = 0.f;
			}
		}
		if (mFireType == eFireType::Linear)
		{
			mAccTime += Time::fDeltaTime();
			if (math::areAlmostEqual(mAccTime, mSkillFireTimes[curFallIndex]), 0.05f)
			{
				skills[curFallIndex]->SkillFire();
				++curFallIndex;
				mAccTime = 0.f;
			}
		}

	}
	void SkillMultiFire::LateUpdate()
	{
		Skill::LateUpdate();
	}
	void SkillMultiFire::Render()
	{
		Skill::Render();
	}
}