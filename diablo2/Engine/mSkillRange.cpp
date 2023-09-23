#include "mSkillRange.h"

#include "mRangeScript.h"

namespace m
{
	SkillRange::SkillRange(eSkillType type, GameObject* owner, eLayerType layerType, Camera* camera)
		: Skill(type, GET_POS(owner), false, true)
		, mCenterOwner(owner)
	{
		SetCamera(camera);

		SET_MESH(this, L"PointMesh");
		SET_MATERIAL(this, L"noneRect");
		mRS = AddComponent<RangeScript>(type, layerType);

		rangeCollider->SetScale(Vector3(500.f, 250.f, 1.f));
	}

	SkillRange::~SkillRange()
	{
	}

	void SkillRange::Initialize()
	{
		Skill::Initialize();
	}

	void SkillRange::Update()
	{
		Skill::Update();
		SET_POS_VEC(this, GET_POS(mCenterOwner));
		if(bSkillFire)
		{
			mRS->ActiveRange();
			bSkillFire = false;
		}
		if(mRS->GetAttackEnd())
		{
			SetState(eState::Delete);
		}
	}

	void SkillRange::LateUpdate()
	{
		Skill::LateUpdate();
	}

	void SkillRange::Render()
	{
		Skill::Render();
	}
}
