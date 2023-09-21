#include "mSkillMultiSummons.h"

#include "../engine_source/mSceneManager.h"

#include "mSkillSummons.h"

namespace m
{
	SkillMultiSummons::SkillMultiSummons(
		eSummonsType type,
		Vector3 initPos,
		Camera* camera,
		float summonTime,
		int count,
		eLayerType layerType
	)
	{
		if (type == eSummonsType::Hydra)
		{
			Vector3 pos[3] = {
				Vector3(initPos.x - 30.f, initPos.y + 20.f, initPos.z),
				Vector3(initPos.x - 15.f, initPos.y - 15.f, initPos.z),
				Vector3(initPos.x + 20.f, initPos.y, initPos.z),
			};
			Vector3 destPos[3] = {
			Vector3(pos[0].x - 30.f, pos[0].y + 20.f, initPos.z),
			Vector3(pos[1].x - 15.f, pos[1].y - 15.f, initPos.z),
			Vector3(pos[2].x + 20.f, pos[2].y, initPos.z),
			};
			for (int i = 0; i < count; ++i)
			{
				SkillSummons* ss = new SkillSummons((int)eSummonsType::Hydra, pos[i], destPos[i] ,summonTime);
				ss->SetCamera(camera);
				SceneManager::GetActiveScene()->AddGameObject(eLayerType::Summons, ss);
				skills.push_back(ss);
			}
		}
	}

	SkillMultiSummons::~SkillMultiSummons()
	{
	}

	void SkillMultiSummons::Initialize()
	{
		GameObject::Initialize();
	}

	void SkillMultiSummons::Update()
	{
		GameObject::Update();
		SetState(Delete);
	}
}
