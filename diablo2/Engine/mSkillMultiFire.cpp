#include "mSkillMultiFire.h"

#include "../engine_source/mSceneManager.h"
#include "../engine_source/mMeshRenderer.h"
#include "../engine_source/mTime.h"

namespace m
{
	SkillMultiFire::SkillMultiFire(
		Vector3 iniPos,
		eSkillType type,
		int count,
		int fireType,
		eLayerType layerType,
		Vector2 randFireRange
	)
		: Skill(type, iniPos)
		, mFireType((eFireType)fireType)
		, curIndex(0)
		, mCount(count)
		, mAccTime(0.f)
		, bFirstUpdate(false)
	{

		SET_MESH(this, L"PointMesh");
		SET_MATERIAL(this, L"noneRect");

		//initDegree -= (count / 2) * 20.f;
		Vector3 pos = iniPos;

		Vector3 playerPos = TileManager::GetPlayerPosition();
		Vector3 initDegreeVector3 = playerPos - pos;

		initDegreeVector3.Normalize();
		float initDegree = RadianToDegree(atan2(initDegreeVector3.y, initDegreeVector3.x));

		std::default_random_engine generator(std::time(nullptr));

		for (int i = 0; i < mCount; ++i)
		{
			Vector3 startPos = iniPos;
			Skill* sf = nullptr;
			if (mFireType == eFireType::Random)
			{
				sf = makeRandomFall(randFireRange, startPos, type, generator);
			}
			if (mFireType == eFireType::Linear)
			{
				mSkillFireTimes.push_back(0.05f);
				sf = new SkillStraight(type, startPos, 400.f);
			}
			if (mFireType == eFireType::Radial)
			{
				sf = makeRadialStraight(startPos, type, initDegree, (float)i);
			}
			SceneManager::GetActiveScene()->AddGameObject(layerType, sf);

			skills.push_back(sf);
		}
		std::reverse(skills.begin(), skills.end());
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
		if (!bFirstUpdate)
		{
			for (Skill* sf : skills)
			{
				sf->SetCamera(GetCamera());
			}
			bFirstUpdate = true;
		}
		if (mFireType == eFireType::Radial)
		{
			for (Skill* sf : skills) sf->SkillFire();
			SetState(GameObject::eState::Delete);
			bSkillFire = true;
		}
		if (mFireType == eFireType::Random)
		{
			if (mSkillFireTimes.size() <= curIndex)
			{
				SetState(GameObject::eState::Delete);
				bSkillFire = true;
				return;
			}
			mAccTime += Time::fDeltaTime();
			if (math::areAlmostEqual(mAccTime, mSkillFireTimes[curIndex]))
			{
				skills[curIndex]->SkillFire();
				++curIndex;
				mAccTime = 0.f;
			}
		}
		if (mFireType == eFireType::Linear)
		{
			if (mSkillFireTimes.size() <= curIndex)
			{
				SetState(GameObject::eState::Delete);
				bSkillFire = true;
				return;
			}
			mAccTime += Time::fDeltaTime();
			if (mAccTime >= mSkillFireTimes[curIndex])
			{
				skills[curIndex]->SkillFire();
				++curIndex;
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

	SkillFall* SkillMultiFire::makeRandomFall(Vector2 randFireRange, Vector3 startPos
		, eSkillType type, std::default_random_engine generator)
	{
		int randX = rand() % (int)randFireRange.x;
		int randY = rand() % (int)randFireRange.y;
		int randSignX = rand() % 2;
		int randSignY = rand() % 2;
		if (randSignX)randX *= -1;
		if (randSignY)randY *= -1;

		startPos.x += (float)randX;
		startPos.y += (float)randY;

		std::uniform_real_distribution<float> distribution(0.0f, 0.5f);
		mSkillFireTimes.push_back(distribution(generator));
		if (type == eSkillType::blizzard)
		{
			return new SkillFall(type, startPos, 300.f, false, false, eAccessorySkillType::Blizzard1);
		}
		return new SkillFall(type, startPos);
	}

	SkillStraight* SkillMultiFire::makeRadialStraight(Vector3 startPos, eSkillType type, float initDegree, float addDegree)
	{
		initDegree += (((float)mCount / 2.f) - addDegree) * 10.f;

		float theta = DegreeToRadian(initDegree);

		SkillStraight* skill = new SkillStraight(type, startPos, 300.f, true);

		skill->SetInitializePosition(startPos);

		startPos.x += cosf(theta);
		startPos.y += sinf(theta);

		skill->SetDestPosition(startPos);

		return skill;
	}
}
