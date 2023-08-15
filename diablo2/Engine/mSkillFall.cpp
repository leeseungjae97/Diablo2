#include "mSkillFall.h"

#include "../engine_source/mAnimator.h"
#include "../engine_source/mMeshRenderer.h"
#include "../engine_source/mInput.h"
#include "../engine_source/mTime.h"

namespace m
{
	SkillFall::SkillFall(eSkillType type, Vector3 iniPos, eAccessorySkillType _acType)
		: Skill(type, iniPos)
		, bMove(false)
	{
		//fSpeed = 100.f;
		ADD_COMP(this, Animator);
		Collider2D* col = ADD_COMP(this, Collider2D);

		SET_MESH(this, L"RectMesh");
		SET_MATERIAL(this, L"AnimationMaterial");
		eAccessorySkillType acType = _acType;
		if (type == eSkillType::blizzard)
		{
			int mr = rand() % 2;
			acType = (eAccessorySkillType)mr;
			SET_SCALE_XYZ(this, accessorySkillAnimSize[(UINT)acType].x
						  , accessorySkillAnimSize[(UINT)acType].y, 1.f);
			mFs = AddComponent<FallScript>(acType);
		}
		fInitYValue = iniPos.y;
	}
	SkillFall::~SkillFall()
	{
	}
	void SkillFall::Update()
	{
		Skill::Update();
		Vector3 mPos =GET_POS(this);

		if (Arrival(fInitYValue - 300, mPos.y, fInitYValue))
		{
			bMove = false;
			if(mFs)
				mFs->Arrival();
		}
		if (bSkillFire)
		{
			bSkillFire = false;
			if(mFs)
				mFs->SkillFire();
			bMove = true;
		}
		if (bMove)
		{
			mPos.y = mPos.y - fSpeed * Time::fDeltaTime();
			SET_POS_VEC(this, mPos);
		}
	}
	void SkillFall::LateUpdate()
	{
		Skill::LateUpdate();
	}
	void SkillFall::Render()
	{
		Skill::Render();
	}
	void SkillFall::Initialize()
	{
		Skill::Initialize();
	}
}