#include "mSkillMultiFire.h"

#include "../engine_source/mAudioSource.h"
#include "../engine_source/mMouseManager.h"
#include "../engine_source/mSceneManager.h"
#include "../engine_source/mMeshRenderer.h"
#include "../engine_source/mTime.h"

#include "mSkillFall.h"
#include "mSkillStraight.h"
#include "mSkillFollower.h"

namespace m
{
	SkillMultiFire::SkillMultiFire(
		Vector3 iniPos,
		eSkillType type,
		int count,
		int fireType,
		eLayerType layerType,
		Vector2 randFireRange,
		Camera* camera,
		float skillGenTime,
		bool addSkill 
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

		SetCamera(camera);
		//initDegree -= (count / 2) * 20.f;
		Vector3 pos = iniPos;
		Vector3 targetPos = Vector3::Zero;

		if(addSkill)
		{
			Vector3 playerPos =TileManager::GetPlayerPosition();

			Vector3 vD = iniPos - playerPos;
			vD.Normalize();
			iniPos.x += vD.x;
			iniPos.y += vD.y;
			targetPos = iniPos;
		}else
		{
			if (layerType == eLayerType::MonsterSkill)
			{
				targetPos = TileManager::GetPlayerPosition();
			}
			else
			{
				Vector3 unprojMousePos = MouseManager::UnprojectionMousePos(iniPos.z, camera);
				unprojMousePos.z = iniPos.z;
				targetPos = unprojMousePos;
			}
		}

		if (mFireType == eFireType::HeadDamage)
		{
		}
		if (mFireType == eFireType::RandomFall)
		{
			ADD_COMP(this, AudioSource);
		}
		if (mFireType == eFireType::RandomLinear)
		{
			ADD_COMP(this, AudioSource);
		}
		if (mFireType == eFireType::Linear)
		{
			ADD_COMP(this, AudioSource);
		}
		if (mFireType == eFireType::FixedLinear)
		{
			ADD_COMP(this, AudioSource);
		}
		if (mFireType == eFireType::RadialRandomStraight)
		{
		}
		if (mFireType == eFireType::Radial)
		{
			ADD_COMP(this, AudioSource);
		}
		if (mFireType == eFireType::Circle)
		{
			ADD_COMP(this, AudioSource);
		}
		
		Vector3 initDegreeVector3 = targetPos - pos;

		initDegreeVector3.Normalize();
		float initDegree = RadianToDegree(atan2(initDegreeVector3.y, initDegreeVector3.x));

		
		SkillStraight* head = nullptr;
		for (int i = 0; i < mCount; ++i)
		{
			Vector3 startPos = iniPos;
			Skill* sf = nullptr;
			if (mFireType == eFireType::HeadDamage)
			{
				sf = makeHeadLinear(type, startPos, camera, skillGenTime, i);
				sf->Mute(true);
				bFirstUpdate = true;
			}
			if (mFireType == eFireType::RandomFall)
			{
				sf = makeRandomFall(randFireRange, startPos, type);
				sf->Mute(true);
			}
			if (mFireType == eFireType::RandomLinear)
			{
				sf = makeRandomLinear(randFireRange.y, startPos, type, camera, layerType);
				sf->Mute(true);
				bFirstUpdate = true;
			}
			if (mFireType == eFireType::Linear)
			{
				mSkillFireTimes.push_back(skillGenTime);
				sf = new SkillStraight(type, startPos, 400.f);
				sf->Mute(true);
			}
			if(mFireType == eFireType::FixedLinear)
			{
				mSkillFireTimes.push_back(skillGenTime);
				sf = new SkillStraight(type, startPos, 400.f);
				sf->SetSkillOwnerLayer(layerType);
				sf->Mute(true);

				sf->SetCamera(camera);
				sf->SetDestPosition(targetPos);
				bFirstUpdate = true;
			}
			if(mFireType == eFireType::RadialRandomStraight)
			{
				sf = makeRadialRandomStraight(randFireRange.y, startPos, type, camera, layerType, initDegree, (float)i);
				//sf->Mute(true);
				sf->SoundLoop();
				bFirstUpdate = true;
			}
			if (mFireType == eFireType::Radial)
			{
				sf = makeRadialStraight(startPos, type, initDegree, (float)i);
				sf->Mute(true);
			}
			if (mFireType == eFireType::Circle)
			{
				sf = makeCircleStraights(startPos, type, (float)i);
				sf->Mute(true);
			}
			SceneManager::GetActiveScene()->AddGameObject(layerType, sf);

			skills.push_back(sf);
		}
		//std::reverse(skills.begin(), skills.end());
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
		AudioSource* as = GET_COMP(this, AudioSource);

		if (!bFirstUpdate)
		{
			for (Skill* sf : skills)
			{
				sf->SetCamera(GetCamera());
			}
			bFirstUpdate = true;
		}
		if (mFireType == eFireType::Linear
			|| mFireType == eFireType::FixedLinear
			|| mFireType == eFireType::HeadDamage
			|| mFireType == eFireType::Radial
			|| mFireType == eFireType::Circle
			|| mFireType == eFireType::RandomLinear
			)
		{
			if(!IsSoundPlayed())
			{
				std::wstring name = skillSoundPath[(int)mSkillType][0];
				if (as)
					as->Play(name, skillSoundLoop[(int)mSkillType], true);
				SoundPlay(true);
			}	
		}else
		{
			std::wstring name = skillSoundPath[(int)mSkillType][0];
			if (as)
				as->Play(name, skillSoundLoop[(int)mSkillType], true);
		}

		if (mFireType == eFireType::Radial
			|| mFireType == eFireType::Circle
			|| mFireType == eFireType::RandomLinear
			|| mFireType == eFireType::RadialRandomStraight)
		{
			for (Skill* sf : skills) sf->SkillFire();
			SetState(GameObject::eState::Delete);
			bSkillFire = true;
		}
		if (mFireType == eFireType::RandomFall)
		{
			if (mSkillFireTimes.size() <= curIndex)
			{
				if (skillSoundLoop[(int)mSkillType] && as)
				    as->Stop(AudioSource::eAudioClipType::Fire);

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
		if (mFireType == eFireType::Linear
			|| mFireType == eFireType::FixedLinear
			|| mFireType == eFireType::HeadDamage)
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
				if (mFireType == eFireType::HeadDamage)
				{
					skills[curIndex]->SetDestPosition(vOtherTargetPos);
				}
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

    SkillStraight* SkillMultiFire::makeHeadLinear(eSkillType type
		, Vector3 startPos, Camera* camera
		,float genTime, int index)
    {
		mSkillFireTimes.push_back(genTime);
		SkillStraight* ss = new SkillStraight(type, startPos, 400.f);
		if (index == 0)
		{
			ss->Head();
		}
		else
		{
			ss->SetHead(dynamic_cast<SkillStraight*>(skills[0]));
		}
		ss->HeadLinear();
		ss->Initialize();
		ss->SetCamera(camera);
		
		return ss;
    }

    SkillStraight* SkillMultiFire::makeRadialRandomStraight(float randomY, Vector3 initPos, eSkillType type, Camera* camera,
                                                            eLayerType layerType, float initDegree, float addDegree)
    {
		initDegree += (((float)mCount / 2.f) - addDegree) * 5.f;

		float theta = DegreeToRadian(initDegree);

		SkillStraight* skill = new SkillStraight(type, initPos, 300.f);
		skill->SetRandomStraight(randomY, 0.3f);
		skill->SetSkillOwnerLayer(layerType);
		skill->SetCamera(camera);
		skill->SetInitializePosition(initPos);

		initPos.x += cosf(theta);
		initPos.y += sinf(theta);

		skill->SetDestPosition(initPos);

		return skill;
    }

    Skill* SkillMultiFire::makeRandomLinear(float randomY, Vector3 initPos, eSkillType type, Camera* camera, eLayerType layerType)
    {
		SkillFollower* skill = new SkillFollower(type, 40, initPos, initPos, camera);
		skill->SetRandomStraight(randomY, 0.5f);
		skill->SetFollowerGenerateTime(0.08f);
		skill->SetSkillOwnerLayer(layerType);
		skill->SetFollowerLoopCount(1);
		skill->Initialize();
		return skill;
    }

    SkillStraight* SkillMultiFire::makeCircleStraights(Vector3 vector3, eSkillType type, float addDegree)
    {
		float degree = (360.f / (float)mCount) * addDegree;
		float theta = DegreeToRadian(degree);
	    SkillStraight* skill = new SkillStraight(type, vector3, skillSpeed[(int)type], true);
		skill->SetInitializePosition(vector3);

		vector3.x += cosf(theta);
		vector3.y += sinf(theta);

		skill->SetDestPosition(vector3);
		return skill;
    }

    SkillFall* SkillMultiFire::makeRandomFall(Vector2 randFireRange, Vector3 startPos
                                              , eSkillType type)
	{
		int randX = rand() % (int)randFireRange.x;
		int randY = rand() % (int)randFireRange.y;
		int randSignX = rand() % 2;
		int randSignY = rand() % 2;
		if (randSignX)randX *= -1;
		if (randSignY)randY *= -1;

		startPos.x += (float)randX;
		startPos.y += (float)randY;


		int iRand =rand() % 5;
		float fRandN = static_cast<float>(iRand);
		fRandN /= 10;
		mSkillFireTimes.push_back(fRandN);

		if (type == eSkillType::blizzard)
		{
			return new SkillFall(type, startPos, skillSpeed[(int)type], false, false, eAccessorySkillType::Blizzard1);
		}
		return new SkillFall(type, startPos);
	}

	SkillStraight* SkillMultiFire::makeRadialStraight(Vector3 startPos, eSkillType type, float initDegree, float addDegree)
	{
		initDegree += (((float)mCount / 2.f) - addDegree) * 10.f;

		float theta = DegreeToRadian(initDegree);

		SkillStraight* skill = new SkillStraight(type, startPos, skillSpeed[(int)type], true);

		skill->SetInitializePosition(startPos);

		startPos.x += cosf(theta);
		startPos.y += sinf(theta);

		skill->SetDestPosition(startPos);

		return skill;
	}
}
