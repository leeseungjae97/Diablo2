#include "mSkillFall.h"

#include "../engine_source/mAnimator.h"
#include "../engine_source/mMeshRenderer.h"
#include "../engine_source/mTime.h"

namespace m
{
	SkillFall::SkillFall(eSkillType type, Vector3 iniPos, float fallHeight
		, bool diagonalFall, bool deco, eAccessorySkillType _acType, MoveAbleObject* targetObject
	)
		: Skill(type, iniPos)
	    , fInitYValue(iniPos.y)
	    , bDiagonalFall(diagonalFall)
	    , mFallHeight(fallHeight)
	    , degreeUpdate(false)
	    , mSkillType(type)
	    , mAcType(_acType)
	{
		ADD_COMP(this, Animator);
		//if(!deco)
		    //

		SET_MESH(this, L"RectMesh");
		SET_MATERIAL(this, L"AnimationMaterial");

		if (mAcType != eAccessorySkillType::END)
		{
			if (mSkillType == eSkillType::blizzard)
				mAcType = (eAccessorySkillType)(rand() % 2);

			SET_SCALE_XYZ(this, accessorySkillAnimSize[(UINT)mAcType].x
				, accessorySkillAnimSize[(UINT)mAcType].y, 1.f);
			mFs = AddComponent<FallScript>(mAcType);
		}
		else
		{
			SET_SCALE_XYZ(this, skillSizes[(UINT)mSkillType].x
				, skillSizes[(UINT)mSkillType].y, 1.f);
			mFs = AddComponent<FallScript>(eAccessorySkillType::END, targetObject);
		}
	}
	SkillFall::~SkillFall()
	{
	}
	void SkillFall::Update()
	{
		Skill::Update();
		
		fallArrival();

		if (bSkillFire)
		{
			adjustmentPosition();
			
			bSkillFire = false;
			if(mFs)
				mFs->SkillFire();
			bMove = true;
		}
		if (bMove)
		{
			fall();
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
	void SkillFall::fallArrival()
	{
		Vector3 mPos = GET_POS(this);
		if (Arrival(fInitYValue - mFallHeight, mPos.y, fInitYValue))
		{
			bMove = false;
			if (mFs)
				mFs->Arrival();
			//SetArrival(true);
		}
	}
	void SkillFall::fall()
	{
		Vector3 mPos = GET_POS(this);
		if (bDiagonalFall)
		{
			//mPos.x += cosf(DegreeToRadian(mFallDegree));

			//mPos.y -= mPos.y - fSpeed * Time::fDeltaTime();
		}
		mPos.y += vDirection.y * fSpeed * Time::fDeltaTime();
		mPos.x += vDirection.x * fSpeed * Time::fDeltaTime();
		SET_POS_VEC(this, mPos);
	}
	void SkillFall::adjustmentPosition()
	{
		Vector3 mPos = GET_POS(this);
		if (bDiagonalFall)
		{
		    destPosition = mPos;
			destPosition.y -= mFallHeight;

			mPos.x -= mFallHeight / 4.f;

			Vector3 curPosition = mPos;
			SET_POS_VEC(this, curPosition);

			vDirection = destPosition - curPosition;
			vDirection.Normalize();
		}else
		{
			destPosition = mPos;
			destPosition.y -= mFallHeight;

			Vector3 curPosition = mPos;
			SET_POS_VEC(this, curPosition);

			vDirection = destPosition - curPosition;
			vDirection.Normalize();
		}
	}
}