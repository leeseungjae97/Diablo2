#include "mStraightScript.h"

#include "mMoveAbleObject.h"

namespace m
{
	StraightScript::StraightScript()
		: SkillScript()
	{
		SHARED_MAT tex = RESOURCE_FIND(Material, skillAnimNames[(int)mType]);
		for (int i = 0; i < (int)eSkillDirection::End; ++i)
		{
			mAnimator->Create(
				skillAnimNames[(int)mType] + skillDirectionString[i]
				, tex->GetTexture()
				, Vector2(0.0f, skillSizes[(int)mType].y * i)
				, skillSizes[(int)mType]
				, skillAnimLength[(int)mType]
				, Vector2::Zero
				, 0.1f
			);
		}
	}
	StraightScript::~StraightScript()
	{
	}
	void StraightScript::Initialize()
	{
	}
	void StraightScript::Update()
	{
		if (mAnimator->GetActiveAnimation()) return;

		Vector3 initPos = GET_POS(GetOwner());
		Vector3 destPos = dynamic_cast<MoveAbleObject*>(GetOwner())->GetDestPosition();

		Vector3 moveVector = destPos - initPos;

		moveVector.Normalize();

		float degree = RadianToDegree(atan2(moveVector.x, moveVector.y));
		float fDivideDegree = 180.f / 9.f;

		if (degree > -fDivideDegree && degree < fDivideDegree) mDirection = eSkillDirection::Up;
		else if (degree < -fDivideDegree && degree > -fDivideDegree * 2) mDirection = eSkillDirection::LeftUp3;
		else if (degree < -fDivideDegree * 2 && degree > -fDivideDegree * 3) mDirection = eSkillDirection::LeftUp2;
		else if (degree < -fDivideDegree * 3 && degree > -fDivideDegree * 4) mDirection = eSkillDirection::LeftUp1;
		else if (degree < -fDivideDegree * 4 && degree > -fDivideDegree * 5) mDirection = eSkillDirection::Left;
		else if (degree < -fDivideDegree * 5 && degree > -fDivideDegree * 6) mDirection = eSkillDirection::LeftDown3;
		else if (degree < -fDivideDegree * 6 && degree > -fDivideDegree * 7) mDirection = eSkillDirection::LeftDown2;
		else if (degree < -fDivideDegree * 7 && degree > -fDivideDegree * 8) mDirection = eSkillDirection::LeftDown1;
		else if (degree < -fDivideDegree * 8 && degree > -fDivideDegree * 9) mDirection = eSkillDirection::Down;
		else if (degree <  fDivideDegree * 9 && degree >  fDivideDegree * 8) mDirection = eSkillDirection::Down;
		else if (degree <  fDivideDegree * 8 && degree >  fDivideDegree * 7) mDirection = eSkillDirection::RightDown3;
		else if (degree <  fDivideDegree * 7 && degree >  fDivideDegree * 6) mDirection = eSkillDirection::RightDown2;
		else if (degree <  fDivideDegree * 6 && degree >  fDivideDegree * 5) mDirection = eSkillDirection::RightDown1;
		else if (degree <  fDivideDegree * 5 && degree >  fDivideDegree * 4) mDirection = eSkillDirection::Right;
		else if (degree <  fDivideDegree * 4 && degree >  fDivideDegree * 3) mDirection = eSkillDirection::RightUp3;
		else if (degree <  fDivideDegree * 3 && degree >  fDivideDegree * 2) mDirection = eSkillDirection::RightUp2;
		else if (degree <  fDivideDegree * 2 && degree >  fDivideDegree) mDirection = eSkillDirection::RightUp1;

		mAnimator->PlayAnimation(skillAnimNames[(int)mType] + skillDirectionString[(UINT)mDirection], true);
	}
	void StraightScript::LateUpdate()
	{
	}
	void StraightScript::Render()
	{
	}
	void StraightScript::OnCollisionEnter(Collider2D* other)
	{
	}
	void StraightScript::OnCollisionStay(Collider2D* other)
	{
	}
	void StraightScript::OnCollisionExit(Collider2D* other)
	{
	}
}