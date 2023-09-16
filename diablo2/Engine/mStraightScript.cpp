#include "mStraightScript.h"

#include "mPlayerManager.h"

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
	    , bNoHit(false)
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

		mSkillCrashType = skillCrashTypes[(UINT)mType];
		mCrashType = crashFunction[(int)mSkillCrashType];
		if(mDirectionCount == 0)
		{
			mAnimator->Create(
				skillAnimNames[(int)mType] + L"anim"
				, tex->GetTexture()
				, Vector2(0.0f, 0.f)
				, skillSizes[(int)mType]
				, skillAnimLength[(int)mType]
				, Vector2::Zero
				, 0.03f
			);
		}else
		{
			for (int i = 0; i < mDirectionCount; ++i)
			{
				if (mDirectionCount == 8)
				{
					int m = pathEightDirections[i];
					mAnimator->Create(
						skillAnimNames[(int)mType] + pathSixteenDirectionString[m]
						, tex->GetTexture()
						, Vector2(0.0f, skillSizes[(int)mType].y * i)
						, skillSizes[(int)mType]
						, skillAnimLength[(int)mType]
						, Vector2::Zero
						, 0.03f
					);
				}
				else
				{
					mAnimator->Create(
						skillAnimNames[(int)mType] + pathSixteenDirectionString[i]
						, tex->GetTexture()
						, Vector2(0.0f, skillSizes[(int)mType].y * i)
						, skillSizes[(int)mType]
						, skillAnimLength[(int)mType]
						, Vector2::Zero
						, 0.03f
					);
				}
			}
		}
		
		if (mCrashType == eCrashType::Overlay) return;
		if (mSkillCrashType == eSkillCrashType::END) return;

		SHARED_MAT mat1 = RESOURCE_FIND(Material, crashNames[(int)mSkillCrashType]);
		if(nullptr != mat1)
		{
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
				if (dynamic_cast<SkillStraight*>(GetOwner()))
					dynamic_cast<SkillStraight*>(GetOwner())->StopMove();
			};
			mAnimator->EndEvent(crashNames[(int)mSkillCrashType] + L"anim") = [this]()
			{
				if (this)
					GetOwner()->SetState(GameObject::eState::Delete);
			};
		}
		

		SHARED_MAT noneMat = RESOURCE_FIND(Material, L"noneRect");
		mAnimator->Create(
			L"noneRectAnim"
			, noneMat->GetTexture()
			, Vector2::Zero
			, Vector2(20.f, 20.f)
			, 1
			, Vector2::Zero
			, 0.03f
			, 0.3f
		);

		mAnimator->PlayAnimation(L"noneRectAnim", false);

		//mAnimator->Create();
		//mAnimator->PlayAnimation();
	}
	void StraightScript::Update()
	{
		//if (dynamic_cast<Skill*>(GetOwner())->GetSkillCrash())
		if(bSkillFire
			&& !skillLoops[(int)mType]
			&& mAnimator->GetActiveAnimation()
			&& mAnimator->GetActiveAnimation()->GetKey() == skillAnimNames[(int)mType] + pathSixteenDirectionString[mDirection])
		{
			if(mAnimator->GetActiveAnimation()->IsStop())
    			GetOwner()->SetState(GameObject::eState::Delete);
		}
		if (((Skill*)GetOwner())->GetSkillCrash() && !bNoHit)
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
			else
			{
				GetOwner()->SetState(GameObject::eState::Delete);
			}
		}

		//Vector3 direction = dynamic_cast<SkillStraight*>(GetOwner())->GetDirection();
		if(bSkillFire)
		{
			Vector3 direction = ((SkillStraight*)GetOwner())->GetDirection();

			float degree = RadianToDegree(atan2(direction.x, direction.y));

			int n = 0;
			if (mDirectionCount == 16)
			{
				n = degree / (180.f / 18.f);
				if (n > 17) n = 17;
				if (n > 0)
					mDirection = pathPlusSixteenDirections[n];
				else
					mDirection = pathMinusSixteenDirections[abs(n)];

				//if (degree > -fDivideDegree && degree < fDivideDegree) mDirection = ePathSixTeenDirection::Up;
				//else if (degree < -fDivideDegree && degree > -fDivideDegree * 2) mDirection = ePathSixTeenDirection::LeftUp3;
				//else if (degree < -fDivideDegree * 2 && degree > -fDivideDegree * 3) mDirection = ePathSixTeenDirection::LeftUp2;
				//else if (degree < -fDivideDegree * 3 && degree > -fDivideDegree * 4) mDirection = ePathSixTeenDirection::LeftUp1;
				//else if (degree < -fDivideDegree * 4 && degree > -fDivideDegree * 5) mDirection = ePathSixTeenDirection::Left;
				//else if (degree < -fDivideDegree * 5 && degree > -fDivideDegree * 6) mDirection = ePathSixTeenDirection::LeftDown3;
				//else if (degree < -fDivideDegree * 6 && degree > -fDivideDegree * 7) mDirection = ePathSixTeenDirection::LeftDown2;
				//else if (degree < -fDivideDegree * 7 && degree > -fDivideDegree * 8) mDirection = ePathSixTeenDirection::LeftDown1;
				//else if (degree < -fDivideDegree * 8 && degree > -fDivideDegree * 9) mDirection = ePathSixTeenDirection::Down;
				//else if (degree <  fDivideDegree * 9 && degree >  fDivideDegree * 8) mDirection = ePathSixTeenDirection::Down;
				//else if (degree <  fDivideDegree * 8 && degree >  fDivideDegree * 7) mDirection = ePathSixTeenDirection::RightDown3;
				//else if (degree <  fDivideDegree * 7 && degree >  fDivideDegree * 6) mDirection = ePathSixTeenDirection::RightDown2;
				//else if (degree <  fDivideDegree * 6 && degree >  fDivideDegree * 5) mDirection = ePathSixTeenDirection::RightDown1;
				//else if (degree <  fDivideDegree * 5 && degree >  fDivideDegree * 4) mDirection = ePathSixTeenDirection::Right;
				//else if (degree <  fDivideDegree * 4 && degree >  fDivideDegree * 3) mDirection = ePathSixTeenDirection::RightUp3;
				//else if (degree <  fDivideDegree * 3 && degree >  fDivideDegree * 2) mDirection = ePathSixTeenDirection::RightUp2;
				//else if (degree <  fDivideDegree * 2 && degree >  fDivideDegree) mDirection = ePathSixTeenDirection::RightUp1;
			}
			else
			{
				n = degree / (180.f / 5.f);
				if (n > 4) n = 4;
				if (n > 0)
					mDirection = pathPlusEightDirections[n];
				else
					mDirection = pathMinusEightDirections[abs(n)];
				//if (degree > -fDivideDegree && degree < fDivideDegree) mDirection = ePathSixTeenDirection::Up;
				//else if (degree < -fDivideDegree && degree > -fDivideDegree * 2) mDirection = ePathSixTeenDirection::LeftUp1;
				//else if (degree < -fDivideDegree * 2 && degree > -fDivideDegree * 3) mDirection = ePathSixTeenDirection::Left;
				//else if (degree < -fDivideDegree * 3 && degree > -fDivideDegree * 4) mDirection = ePathSixTeenDirection::LeftDown1;
				//else if (degree < -fDivideDegree * 4 && degree > -fDivideDegree * 5) mDirection = ePathSixTeenDirection::Down;
				//else if (degree <  fDivideDegree * 5 && degree >  fDivideDegree * 4) mDirection = ePathSixTeenDirection::Down;
				//else if (degree <  fDivideDegree * 4 && degree >  fDivideDegree * 3) mDirection = ePathSixTeenDirection::RightDown1;
				//else if (degree <  fDivideDegree * 3 && degree >  fDivideDegree * 2) mDirection = ePathSixTeenDirection::Right;
				//else if (degree <  fDivideDegree * 2 && degree >  fDivideDegree) mDirection = ePathSixTeenDirection::RightUp1;
			}
			if (mDirectionCount == 0)
			{
				if (nullptr == mAnimator->GetActiveAnimation() ||
					mAnimator->GetActiveAnimation()->GetKey() != skillAnimNames[(int)mType] + L"anim")
					mAnimator->PlayAnimation(skillAnimNames[(int)mType] + L"anim", true);
			}else
			{
				if (nullptr == mAnimator->GetActiveAnimation() ||
					mAnimator->GetActiveAnimation()->GetKey() != skillAnimNames[(int)mType] + pathSixteenDirectionString[mDirection])
					mAnimator->PlayAnimation(skillAnimNames[(int)mType] + pathSixteenDirectionString[mDirection], skillLoops[(int)mType]);
			}
			
		}
		
	}
	void StraightScript::LateUpdate()
	{

	}
	void StraightScript::Render()
	{
	}
	void StraightScript::OnCollisionEnter(Collider2D* other)
	{
		if (other->GetColliderFunctionType() == eColliderFunctionType::HitArea)
		{
			switch (dynamic_cast<Skill*>(GetOwner())->GetLayerType())
			{
			case m::enums::eLayerType::PlayerSkill:
			{
				if (dynamic_cast<Monster*>(other->GetOwner()))
					dynamic_cast<Monster*>(other->GetOwner())->Hit(10);
			}
			break;
			case m::enums::eLayerType::MonsterSkill:
			{
				if (mCrashType == eCrashType::Overlay)
				{
					//PlayerScript* ps = PlayerManager::player->GetComponent<PlayerScript>();
					PlayerScript* ps = other->GetOwner()->GetComponent<PlayerScript>();

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
				if (mCrashType == eCrashType::Addiction)
				{
					dynamic_cast<Player*>(other->GetOwner())->Addiction(10, 10.f, 10);
				}
				dynamic_cast<Player*>(other->GetOwner())->Hit(10);
			}
			break;
			default:
				break;
			}
			if (mCrashType != eCrashType::Overlay) dynamic_cast<Skill*>(GetOwner())->SetSkillCrash(true);
			//if (other->GetOwner()->GetLayerType() != dynamic_cast<Skill*>(GetOwner())->GetLayerType())
			//{
			//	
			//	//Monster* monster = dynamic_cast<Monster*>();
			//}
			
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