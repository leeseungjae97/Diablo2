#include "mSkillMultiFall.h"

#include "../engine_source/mSceneManager.h"
#include "../engine_source/mMeshRenderer.h"
#include "../engine_source/mTime.h"

namespace m
{
	SkillMultiFall::SkillMultiFall(eSkillType type, Vector3 iniPos, int fallcount, bool bRandFall)
		: Skill(type, iniPos)
		, mbRandFall(bRandFall)
		, curFallIndex(0)
		, mAccTime(0.f)
	{
		std::default_random_engine generator(std::time(nullptr));
		SET_MESH(this, L"PointMesh");
		SET_MATERIAL(this, L"AnimationMaterial");
		for (int i = 0; i < 20; ++i)
		{

			int randX = rand() % 200;
			int randY = rand() % 50;
			int randSignX = rand() % 2;
			int randSignY = rand() % 2;
			if (randSignX)randX *= -1;
			if (randSignY)randY *= -1;

			Vector3 fallPos = iniPos;

			fallPos.x += (float)randX;
			fallPos.y += (float)randY;

			SkillFall* sf = new SkillFall(type, fallPos);
			SceneManager::GetActiveScene()->AddGameObject(eLayerType::Skill, sf);

			fallFragments.push_back(sf);
			std::uniform_real_distribution<float> distribution(0.0f, 0.5f);
			randFall.push_back(distribution(generator));
		}
		
	}
	SkillMultiFall::~SkillMultiFall()
	{
	}
	void SkillMultiFall::Initialize()
	{
		Skill::Initialize();
	}
	void SkillMultiFall::Update()
	{
		Skill::Update();
		if (nullptr == fallFragments.front()->GetCamera())
		{
			for (SkillFall* sf : fallFragments) sf->SetCamera(GetCamera());
		}
		if (mbRandFall)
		{
			if (randFall.size() == curFallIndex)
			{
				mbRandFall = false;
				SetState(GameObject::eState::Delete);
				return;
			}
			mAccTime += Time::fDeltaTime();			
			if (math::areAlmostEqual(mAccTime, randFall[curFallIndex]))
			{
				fallFragments[curFallIndex]->SkillFire();
				++curFallIndex;
				mAccTime = 0.f;
			}
		}

	}
	void SkillMultiFall::LateUpdate()
	{
		Skill::LateUpdate();
	}
	void SkillMultiFall::Render()
	{
		Skill::Render();
	}
}