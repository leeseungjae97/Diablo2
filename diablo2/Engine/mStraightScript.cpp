#include "mStraightScript.h"

#include "mPlayerInfo.h"

#include "mSkillStraight.h"
#include "mPlayerScript.h"
#include "mSkill.h"
#include "mPlayer.h"
#include "mMonster.h"

namespace m
{
	StraightScript::StraightScript(int _directionCount)
		: mDirectionCount(_directionCount)
		, mCrashType(eCrashType::END)
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
		
		mSkillCrashType = skillCrashTypes[(UINT)mType];
		mCrashType = crashFunction[(int)mSkillCrashType];

		
		for (int i = 0; i < mDirectionCount; ++i)
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
		if (mCrashType == eCrashType::Overlay) return;

		SHARED_MAT mat1 = RESOURCE_FIND(Material, crashNames[(int)mSkillCrashType]);
		mAnimator->Create(crashNames[(int)mSkillCrashType] + L"anim"
						  , mat1->GetTexture()
						  , Vector2::Zero
						  , crashSizes[(int)mSkillCrashType]
						  , crashLength[(int)mSkillCrashType]
						  , Vector2::Zero
						  , 0.03f
						  , 0.7f);
		mAnimator->StartEvent(crashNames[(int)mSkillCrashType] + L"anim") = [this]()
		{
			dynamic_cast<SkillStraight*>(GetOwner())->StopMove();
		};
		mAnimator->EndEvent(crashNames[(int)mSkillCrashType] + L"anim") = [this]()
		{
			GetOwner()->SetState(GameObject::eState::Delete);
		};
	}
	void StraightScript::Update()
	{
		//if (dynamic_cast<Skill*>(GetOwner())->GetSkillCrash())
		if (((Skill*)GetOwner())->GetSkillCrash())
		{
			eSkillCrashType crashType = skillCrashTypes[(UINT)mType];
			if (crashFunction[(int)crashType] == eCrashType::Collide)
			{
				if (mAnimator->GetActiveAnimation()->GetKey() != crashNames[(int)crashType] + L"anim")
				{
					mAnimator->PlayAnimation(crashNames[(int)crashType] + L"anim", false);
				}
				return;
			}
		}

		//Vector3 direction = dynamic_cast<SkillStraight*>(GetOwner())->GetDirection();
		Vector3 direction = ((SkillStraight*)GetOwner())->GetDirection();

		float degree = RadianToDegree(atan2(direction.x, direction.y));
		//float degree = 0;
		int n = 0;
		if (mDirectionCount == 16)
		{
			n = degree / (180.f / 9.f);
			if (n > 0) 
				mDirection = plusSkillSTDirections[n];
			else
				mDirection = minusSkillSTDirections[abs(n)];
			//if (degree > -fDivideDegree && degree < fDivideDegree) mDirection = ePathSkillSixTeenDirection::Up;
			//else if (degree < -fDivideDegree && degree > -fDivideDegree * 2) mDirection = ePathSkillSixTeenDirection::LeftUp3;
			//else if (degree < -fDivideDegree * 2 && degree > -fDivideDegree * 3) mDirection = ePathSkillSixTeenDirection::LeftUp2;
			//else if (degree < -fDivideDegree * 3 && degree > -fDivideDegree * 4) mDirection = ePathSkillSixTeenDirection::LeftUp1;
			//else if (degree < -fDivideDegree * 4 && degree > -fDivideDegree * 5) mDirection = ePathSkillSixTeenDirection::Left;
			//else if (degree < -fDivideDegree * 5 && degree > -fDivideDegree * 6) mDirection = ePathSkillSixTeenDirection::LeftDown3;
			//else if (degree < -fDivideDegree * 6 && degree > -fDivideDegree * 7) mDirection = ePathSkillSixTeenDirection::LeftDown2;
			//else if (degree < -fDivideDegree * 7 && degree > -fDivideDegree * 8) mDirection = ePathSkillSixTeenDirection::LeftDown1;
			//else if (degree < -fDivideDegree * 8 && degree > -fDivideDegree * 9) mDirection = ePathSkillSixTeenDirection::Down;
			//else if (degree <  fDivideDegree * 9 && degree >  fDivideDegree * 8) mDirection = ePathSkillSixTeenDirection::Down;
			//else if (degree <  fDivideDegree * 8 && degree >  fDivideDegree * 7) mDirection = ePathSkillSixTeenDirection::RightDown3;
			//else if (degree <  fDivideDegree * 7 && degree >  fDivideDegree * 6) mDirection = ePathSkillSixTeenDirection::RightDown2;
			//else if (degree <  fDivideDegree * 6 && degree >  fDivideDegree * 5) mDirection = ePathSkillSixTeenDirection::RightDown1;
			//else if (degree <  fDivideDegree * 5 && degree >  fDivideDegree * 4) mDirection = ePathSkillSixTeenDirection::Right;
			//else if (degree <  fDivideDegree * 4 && degree >  fDivideDegree * 3) mDirection = ePathSkillSixTeenDirection::RightUp3;
			//else if (degree <  fDivideDegree * 3 && degree >  fDivideDegree * 2) mDirection = ePathSkillSixTeenDirection::RightUp2;
			//else if (degree <  fDivideDegree * 2 && degree >  fDivideDegree) mDirection = ePathSkillSixTeenDirection::RightUp1;
		}
		else
		{
			n = degree / (180.f / 5.f);
			if (n > 0)
				mDirection = plusSkillEDirections[n];
			else
				mDirection = minusSkillEDirections[abs(n)];
			//if (degree > -fDivideDegree && degree < fDivideDegree) mDirection = ePathSkillSixTeenDirection::Up;
			//else if (degree < -fDivideDegree && degree > -fDivideDegree * 2) mDirection = ePathSkillSixTeenDirection::LeftUp1;
			//else if (degree < -fDivideDegree * 2 && degree > -fDivideDegree * 3) mDirection = ePathSkillSixTeenDirection::Left;
			//else if (degree < -fDivideDegree * 3 && degree > -fDivideDegree * 4) mDirection = ePathSkillSixTeenDirection::LeftDown1;
			//else if (degree < -fDivideDegree * 4 && degree > -fDivideDegree * 5) mDirection = ePathSkillSixTeenDirection::Down;
			//else if (degree <  fDivideDegree * 5 && degree >  fDivideDegree * 4) mDirection = ePathSkillSixTeenDirection::Down;
			//else if (degree <  fDivideDegree * 4 && degree >  fDivideDegree * 3) mDirection = ePathSkillSixTeenDirection::RightDown1;
			//else if (degree <  fDivideDegree * 3 && degree >  fDivideDegree * 2) mDirection = ePathSkillSixTeenDirection::Right;
			//else if (degree <  fDivideDegree * 2 && degree >  fDivideDegree) mDirection = ePathSkillSixTeenDirection::RightUp1;
		}


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
		if (other->GetColliderFunctionType() == eColliderFunctionType::TilePos)
		{
			if (other->GetOwner()->GetLayerType() != dynamic_cast<Skill*>(GetOwner())->GetSkillOwnerLayer())
			{

				switch (dynamic_cast<Skill*>(GetOwner())->GetSkillOwnerLayer())
				{
				case m::enums::eLayerType::PlayerSkill: 
				{
					if(dynamic_cast<Monster*>(other->GetOwner()))
						dynamic_cast<Monster*>(other->GetOwner())->Hit(10);
				}
					break;
				case m::enums::eLayerType::MonsterSkill:
				{
					if (mCrashType == eCrashType::Overlay)
					{
						PlayerScript* ps = PlayerInfo::player->GetComponent<PlayerScript>();
						
						SET_SCALE_XYZ(ps->GetHSO()
									  , crashSizes[(int)mSkillCrashType].x
									  , crashSizes[(int)mSkillCrashType].y
									  , 1.f
						);
						OverlayEffectSkillScript* mOESS = ps->GetHSO()->GetComponent<OverlayEffectSkillScript>();
						mOESS->SetSkillType(mType);
						//if(!mOESS->IsPlayHit())
						ps->GetHSO()->ActiveOverlay();

					}
					PlayerInfo::player->Hit(10);
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