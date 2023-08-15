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
		Vector2 size = Vector2::Zero;
		
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
		eSkillCrashType crashType = skillCrashTypes[(UINT)mType];
		SHARED_MAT mat1 = RESOURCE_FIND(Material, crashNames[(int)crashType]);
		mAnimator->Create(crashNames[(int)crashType] + L"anim"
						  , mat1->GetTexture()
						  , Vector2::Zero
						  , crashSizes[(int)crashType]
						  , crashLength[(int)crashType]
						  , Vector2::Zero
						  , 0.03f
						  , 0.7f);
		mAnimator->StartEvent(crashNames[(int)crashType] + L"anim") = [this]()
		{
			dynamic_cast<SkillStraight*>(GetOwner())->StopMove();
		};
		mAnimator->EndEvent(crashNames[(int)crashType] + L"anim") = [this]()
		{
			GetOwner()->SetState(GameObject::eState::Delete);
		};
	}
	void StraightScript::Update()
	{
		if (dynamic_cast<Skill*>(GetOwner())->GetSkillCrash())
		{
			eSkillCrashType crashType = skillCrashTypes[(UINT)mType];
			if (mAnimator->GetActiveAnimation()->GetKey() != crashNames[(int)crashType] + L"anim")
			{
				mAnimator->PlayAnimation(crashNames[(int)crashType] + L"anim", false);
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
			if (other->GetOwner()->GetLayerType() != dynamic_cast<Skill*>(GetOwner())->GetSkillOwner())
			{

				switch (dynamic_cast<Skill*>(GetOwner())->GetSkillOwner())
				{
				case m::enums::eLayerType::Player: 
				{
					dynamic_cast<Monster*>(other->GetOwner())->Hit(10);
				}
					break;
				case m::enums::eLayerType::Monster:
				{
					dynamic_cast<Player*>(other->GetOwner())->Hit(10);
				}
					break;
				default:
					break;
				}
				//Monster* monster = dynamic_cast<Monster*>();
			}
			
			
			dynamic_cast<Skill*>(GetOwner())->SetSkillCrash(true);
			//mAnimator->StopAnimation();
			
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