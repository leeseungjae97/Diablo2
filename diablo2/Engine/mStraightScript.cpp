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
		: SkillScript()
		, mDirectionCount(_directionCount)
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
		if (dynamic_cast<Skill*>(GetOwner())->GetSkillCrash())
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

		Vector3 direction = dynamic_cast<SkillStraight*>(GetOwner())->GetDirection();

		float degree = RadianToDegree(atan2(direction.x, direction.y));
		float fDivideDegree = 0.f;
		if (mDirectionCount == 16)
		{
			fDivideDegree = 180.f / 9.f;
			if (degree > -fDivideDegree && degree < fDivideDegree) mDirection = eSixTeenDirection::Up;
			else if (degree < -fDivideDegree && degree > -fDivideDegree * 2) mDirection = eSixTeenDirection::LeftUp3;
			else if (degree < -fDivideDegree * 2 && degree > -fDivideDegree * 3) mDirection = eSixTeenDirection::LeftUp2;
			else if (degree < -fDivideDegree * 3 && degree > -fDivideDegree * 4) mDirection = eSixTeenDirection::LeftUp1;
			else if (degree < -fDivideDegree * 4 && degree > -fDivideDegree * 5) mDirection = eSixTeenDirection::Left;
			else if (degree < -fDivideDegree * 5 && degree > -fDivideDegree * 6) mDirection = eSixTeenDirection::LeftDown3;
			else if (degree < -fDivideDegree * 6 && degree > -fDivideDegree * 7) mDirection = eSixTeenDirection::LeftDown2;
			else if (degree < -fDivideDegree * 7 && degree > -fDivideDegree * 8) mDirection = eSixTeenDirection::LeftDown1;
			else if (degree < -fDivideDegree * 8 && degree > -fDivideDegree * 9) mDirection = eSixTeenDirection::Down;
			else if (degree <  fDivideDegree * 9 && degree >  fDivideDegree * 8) mDirection = eSixTeenDirection::Down;
			else if (degree <  fDivideDegree * 8 && degree >  fDivideDegree * 7) mDirection = eSixTeenDirection::RightDown3;
			else if (degree <  fDivideDegree * 7 && degree >  fDivideDegree * 6) mDirection = eSixTeenDirection::RightDown2;
			else if (degree <  fDivideDegree * 6 && degree >  fDivideDegree * 5) mDirection = eSixTeenDirection::RightDown1;
			else if (degree <  fDivideDegree * 5 && degree >  fDivideDegree * 4) mDirection = eSixTeenDirection::Right;
			else if (degree <  fDivideDegree * 4 && degree >  fDivideDegree * 3) mDirection = eSixTeenDirection::RightUp3;
			else if (degree <  fDivideDegree * 3 && degree >  fDivideDegree * 2) mDirection = eSixTeenDirection::RightUp2;
			else if (degree <  fDivideDegree * 2 && degree >  fDivideDegree) mDirection = eSixTeenDirection::RightUp1;
		}
		else
		{
			fDivideDegree = 180.f / 5.f;

			if (degree > -fDivideDegree && degree < fDivideDegree) mDirection = eSixTeenDirection::Up;
			else if (degree < -fDivideDegree && degree > -fDivideDegree * 2) mDirection = eSixTeenDirection::LeftUp1;
			else if (degree < -fDivideDegree * 2 && degree > -fDivideDegree * 3) mDirection = eSixTeenDirection::Left;
			else if (degree < -fDivideDegree * 3 && degree > -fDivideDegree * 4) mDirection = eSixTeenDirection::LeftDown1;
			else if (degree < -fDivideDegree * 4 && degree > -fDivideDegree * 5) mDirection = eSixTeenDirection::Down;
			else if (degree <  fDivideDegree * 5 && degree >  fDivideDegree * 4) mDirection = eSixTeenDirection::Down;
			else if (degree <  fDivideDegree * 4 && degree >  fDivideDegree * 3) mDirection = eSixTeenDirection::RightDown1;
			else if (degree <  fDivideDegree * 3 && degree >  fDivideDegree * 2) mDirection = eSixTeenDirection::Right;
			else if (degree <  fDivideDegree * 2 && degree >  fDivideDegree) mDirection = eSixTeenDirection::RightUp1;
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