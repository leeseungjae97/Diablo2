#include "mStraightScript.h"

#include "mPlayerManager.h"

#include "mSkillStraight.h"
#include "mPlayerScript.h"
#include "mSkill.h"
#include "mPlayer.h"
#include "mMonster.h"
#include "mSkillCurve.h"

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

		SHARED_MAT tex;
		Vector2 skillSize;
		Vector2 skillOffset;
		Vector2 skillCenterPos = Vector2::Zero;
		int animLength;
		float duration;

		if (mType == eSkillType::inferno)
		{
			int m = rand() % 2;
			if (m > 0)
			{
				tex = RESOURCE_FIND(Material, L"flame1");
				skillName = L"flame1anim";
				skillSize = Vector2(76.f, 77.f);
				skillCenterPos = Vector2(0, 50.f);
			}
			else
			{
				tex = RESOURCE_FIND(Material, L"flame2");
				skillName = L"flame2anim";
				skillSize = Vector2(76.f, 84.f);
				skillCenterPos = Vector2(0, 50.f);
			}
			animLength = 15;
			skillOffset = skillOffsets[(int)mType];
			duration = 0.03f;
		}
		else
		{
			tex = RESOURCE_FIND(Material, skillAnimNames[(int)mType]);
			skillName = skillAnimNames[(int)mType] + L"anim";
			skillSize = skillSizes[(int)mType];
			skillOffset = skillOffsets[(int)mType];
			animLength = skillAnimLength[(int)mType];
			duration = 0.03f;
		}

		SET_SCALE_XYZ(GetOwner(), skillSize.x, skillSize.y, 1.f);

		mSkillCrashType = skillCrashTypes[(UINT)mType];
		mCrashType = crashFunction[(int)mSkillCrashType];
		if (mDirectionCount == 0)
		{
			mAnimator->Create(
				skillName
				, tex->GetTexture()
				, Vector2(0.0f, 0.f)
				, skillSize
				, animLength
				, skillOffset
				, skillCenterPos
				, duration
			);
		}
		else
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
						, skillOffsets[(int)mType]
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
						, skillOffsets[(int)mType]
						, 0.03f
					);
				}
			}
		}

		if (mCrashType == eCrashType::Overlay) return;
		if (mSkillCrashType == eSkillCrashType::END) return;

		SHARED_MAT mat1 = RESOURCE_FIND(Material, crashNames[(int)mSkillCrashType]);
		if (nullptr != mat1)
		{
			mAnimator->Create(crashNames[(int)mSkillCrashType] + L"anim"
				, mat1->GetTexture()
				, Vector2::Zero
				, crashSizes[(int)mSkillCrashType]
				, crashLength[(int)mSkillCrashType]
				, Vector2::Zero
				, crashCenterPos[(int)mSkillCrashType]
				, 0.03f
				, 0.7f);
			mAnimator->StartEvent(crashNames[(int)mSkillCrashType] + L"anim") = [this]()
			{
				if (dynamic_cast<SkillStraight*>(GetOwner()))
					dynamic_cast<SkillStraight*>(GetOwner())->StopMove();

				if (dynamic_cast<SkillCurve*>(GetOwner()))
					dynamic_cast<SkillCurve*>(GetOwner())->StopMove();
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

		mAnimator->PlayAnimation(L"noneRectAnim", true);
	}
	void StraightScript::Update()
	{
		//if (dynamic_cast<Skill*>(GetOwner())->GetSkillCrash())
		if (bSkillFire
			&& !skillLoops[(int)mType]
			&& mAnimator->GetActiveAnimation()
			/*			&& mAnimator->GetActiveAnimation()->GetKey()
						== skillAnimNames[(int)mType] + pathSixteenDirectionString[mDirection]*/)
		{
			if (mAnimator->GetActiveAnimation()->IsStop())
				GetOwner()->SetState(GameObject::eState::Delete);
		}
	    if (dynamic_cast<Skill*>(GetOwner())->GetSkillCrash()
			&& mCrashType == eCrashType::Overlay)
		{
			GetOwner()->SetState(GameObject::eState::Delete);
		}

		if (((Skill*)GetOwner())->GetSkillCrash() && !bNoHit)
		{
			eSkillCrashType crashType = skillCrashTypes[(UINT)mType];
			if (crashType != eSkillCrashType::END
				&& crashFunction[(int)crashType] == eCrashType::Collide)
			{
				if (mAnimator->GetActiveAnimation()->GetKey() != crashNames[(int)crashType] + L"anim")
				{
					mAnimator->PlayAnimation(crashNames[(int)crashType] + L"anim", false);
				}
				return;
			}
			//else
			//{
			//	GetOwner()->SetState(GameObject::eState::Delete);
			//}
		}
		if (bSkillFire)
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
			}
			else
			{
				n = degree / (180.f / 5.f);
				if (n > 4) n = 4;
				if (n > 0)
					mDirection = pathPlusEightDirections[n];
				else
					mDirection = pathMinusEightDirections[abs(n)];
			}
			if (mDirectionCount == 0)
			{
				if (nullptr == mAnimator->GetActiveAnimation() ||
					mAnimator->GetActiveAnimation()->GetKey() != skillName)
					mAnimator->PlayAnimation(skillName, skillLoops[(int)mType]);
			}
			else
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
			if (bNoHit)
			{
				GetOwner()->SetState(GameObject::eState::Delete);
			}
			else
			{
				switch (dynamic_cast<Skill*>(GetOwner())->GetLayerType())
				{
				case m::enums::eLayerType::PlayerSkill:
				{
					/*if (dynamic_cast<Monster*>(other->GetOwner()))
						dynamic_cast<Monster*>(other->GetOwner())->Hit(10);*/
					if (mCrashType == eCrashType::Overlay)
					{
						//PlayerScript* ps = PlayerManager::player->GetComponent<PlayerScript>();
						Monster* monster = dynamic_cast<Monster*>(other->GetOwner());
						if (monster)
						{
							//SET_SCALE_XYZ(monster->GetHSO()
							//	, crashSizes[(int)mSkillCrashType].x
							//	, crashSizes[(int)mSkillCrashType].y
							//	, 1.f
							//);
							OverlayEffectSkillScript* mOESS = monster->GetHSO()->GetComponent<OverlayEffectSkillScript>();
							mOESS->SetSkillType(mType);
							//if(!mOESS->IsPlayHit())
							monster->GetHSO()->ActiveOverlay();
						}
						if (skillHitDestory[(int)mType])
						{
							dynamic_cast<Skill*>(GetOwner())->SetSkillCrash(true);
						}
					}
					if (mCrashType == eCrashType::Addiction)
					{
						dynamic_cast<Monster*>(other->GetOwner())->Addiction(10, 10.f, 10);
					}
					dynamic_cast<Monster*>(other->GetOwner())->Hit(10);
				}
				break;
				case m::enums::eLayerType::MonsterSkill:
				{
					if (mCrashType == eCrashType::Overlay)
					{
						//PlayerScript* ps = PlayerManager::player->GetComponent<PlayerScript>();
						PlayerScript* ps = other->GetOwner()->GetComponent<PlayerScript>();

						//SET_SCALE_XYZ(ps->GetHSO()
						//	, crashSizes[(int)mSkillCrashType].x
						//	, crashSizes[(int)mSkillCrashType].y
						//	, 1.f
						//);
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
			}
			if (mCrashType != eCrashType::Overlay) dynamic_cast<Skill*>(GetOwner())->SetSkillCrash(true);
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
