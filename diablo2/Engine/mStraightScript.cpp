#include "mStraightScript.h"

#include "mPlayerInfo.h"

#include "mSkillStraight.h"
#include "mPlayerScript.h"
#include "mSkill.h"
#include "mPlayer.h"
#include "mMonster.h"

namespace m
{
	StraightScript::StraightScript()
		: SkillScript()
	{
	}
	StraightScript::~StraightScript()
	{
	}
	void StraightScript::Initialize()
	{
		mAnimator = GET_COMP(GetOwner(), Animator);
		Skill* dSkill = dynamic_cast<Skill*>(GetOwner());
		if (nullptr == dSkill) mType = eSkillType::normalAttack;
		else mType = dSkill->GetSkillType();


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
				, 0.05f
			);
		}
		SHARED_MAT mat1 = RESOURCE_FIND(Material, skillCrashNames[(UINT)mType]);
		mAnimator->Create(skillCrashNames[(UINT)mType] + L"anim"
						  , mat1->GetTexture()
						  , Vector2::Zero
						  , skillCrashSizes[(UINT)mType]
						  , skillCrashLength[(UINT)mType]
						  , Vector2::Zero
						  , 0.03f
						  , 0.7f);
		mAnimator->StartEvent(skillCrashNames[(UINT)mType] + L"anim") = [this]()
		{
			dynamic_cast<SkillStraight*>(GetOwner())->StopMove();
		};
		mAnimator->EndEvent(skillCrashNames[(UINT)mType] + L"anim") = [this]()
		{
			GetOwner()->SetState(GameObject::eState::Delete);
		};
	}
	void StraightScript::Update()
	{
		if (dynamic_cast<Skill*>(GetOwner())->GetSkillCrash())
		{
			if (mAnimator->GetActiveAnimation()->GetKey() != skillCrashNames[(UINT)mType] + L"Crash")
			{
				mAnimator->PlayAnimation(skillCrashNames[(UINT)mType] + L"anim", false);
			}
			return;
		}

		Vector3 direction = dynamic_cast<SkillStraight*>(GetOwner())->GetDirection();

		float degree = RadianToDegree(atan2(direction.x, direction.y));
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

		if(nullptr == mAnimator->GetActiveAnimation() ||
			mAnimator->GetActiveAnimation()->GetKey() != skillAnimNames[(int)mType] + skillDirectionString[(UINT)mDirection])
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
		Script::OnCollisionEnter(other);
		if (other->GetColliderFunctionType() == eColliderFunctionType::TilePos)
		{
			Monster* monster = dynamic_cast<Monster*>(other->GetOwner());
			monster->Hit(10);
			
			//mAnimator->StopAnimation();
			dynamic_cast<Skill*>(GetOwner())->SetSkillCrash(true);
		}
	}
	void StraightScript::OnCollisionStay(Collider2D* other)
	{
		Script::OnCollisionStay(other);
	}
	void StraightScript::OnCollisionExit(Collider2D* other)
	{
		Script::OnCollisionExit(other);
	}
}