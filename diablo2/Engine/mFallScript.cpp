#include "mFallScript.h"

#include "mSkill.h"
#include "mMonster.h"
#include "mOverlayEffectSkillScript.h"
#include "mPlayer.h"
#include "mPlayerScript.h"
#include "mPlayerStatus.h"
#include "mSkillOverlay.h"

namespace m
{
	FallScript::FallScript(eAccessorySkillType type, MoveAbleObject* target)
		: mACType(type)
		, bSkillFire(false)
		, bArrival(false)
		, mTarget(target)
	{
	}
	FallScript::~FallScript()
	{
	}
	void FallScript::Initialize()
	{
		mAnimator = GET_COMP(GetOwner(), Animator);

		Skill* dSkill = dynamic_cast<Skill*>(GetOwner());
		if (nullptr == dSkill) mType = eSkillType::normalAttack;
		else mType = dSkill->GetSkillType();

		if (mACType == eAccessorySkillType::END)
		{
			mCrashType = skillCrashTypes[(int)mType];
			SHARED_MAT mat = RESOURCE_FIND(Material, skillAnimNames[(int)mType]);
			mAnimator->Create(
				skillAnimNames[(int)mType] + L"anim"
				, mat->GetTexture()
				, Vector2::Zero
				, skillSizes[(int)mType]
				, skillAnimLength[(int)mType]
				, Vector2::Zero
				, 0.03f
			);
			mAnimator->EndEvent(skillAnimNames[(int)mType] + L"anim") = std::make_shared<std::function<void()>>([this]()
			{
				if (mTarget)
				{
					if (crashFunction[(int)mCrashType] == eCrashType::Overlay)
					{
						Monster* monster = dynamic_cast<Monster*>(mTarget);

						if (monster)
						{
							OverlayEffectSkillScript* mOESS = monster->GetHSO()->GetComponent<OverlayEffectSkillScript>();
							if(mOESS)
							{
								mOESS->SetSkillType(mType);
								monster->GetHSO()->ActiveOverlay();
							}
						}
					}
					mTarget->Hit(PlayerStatus::damage);
					dynamic_cast<Skill*>(GetOwner())->SetSkillCrash(true);

					GetOwner()->ReleaseAnimators();
					GetOwner()->SetState(GameObject::eState::Delete);
				}
			});


			SHARED_MAT crashMat = RESOURCE_FIND(Material, crashNames[(int)mCrashType]);
			if (mType == eSkillType::meteor)
			{
				GetOwner()->CreateAnimators(
					4
					, mAnimator
					, crashNames[(int)mCrashType] + L"anim"
					, crashMat->GetTexture()
					, Vector2::Zero
					, crashSizes[(int)mCrashType]
					, crashLength[(int)mCrashType]
					, Vector2::Zero
					, 0.03f
				);
			}

			mAnimator->Create(
				crashNames[(int)mCrashType] + L"anim"
				, crashMat->GetTexture()
				, Vector2::Zero
				, crashSizes[(int)mCrashType]
				, crashLength[(int)mCrashType]
				, Vector2::Zero
				, 0.03f
			);
		}
		else
		{

			SHARED_MAT mat = RESOURCE_FIND(Material, accessorySkillNames[(int)mACType]);
			mAnimator->Create(
				accessorySkillNames[(int)mACType] + L"anim"
				, mat->GetTexture()
				, Vector2::Zero
				, accessorySkillAnimSize[(int)mACType]
				, accessorySkillAnimLength[(int)mACType]
				, Vector2::Zero
				, 0.03f
			);
			mAnimator->EndEvent(accessorySkillNames[(int)mACType] + L"anim") = std::make_shared<std::function<void()>>([this]()
			{
				dynamic_cast<Skill*>(GetOwner())->SetSkillCrash(true);
			});

			mCrashType = accessorySkillCrashTypes[(int)mACType];
			if (mCrashType != eSkillCrashType::END)
			{
				SHARED_MAT crashMat = RESOURCE_FIND(Material, crashNames[(int)mCrashType]);
				if (mType == eSkillType::meteor)
				{
					GetOwner()->CreateAnimators(
						4
						, mAnimator
						, crashNames[(int)mCrashType] + L"anim"
						, crashMat->GetTexture()
						, Vector2::Zero
						, crashSizes[(int)mCrashType]
						, crashLength[(int)mCrashType]
						, Vector2::Zero
						, 0.03f
					);
				}


				mAnimator->Create(
					crashNames[(int)mCrashType] + L"anim"
					, crashMat->GetTexture()
					, Vector2::Zero
					, crashSizes[(int)mCrashType]
					, crashLength[(int)mCrashType]
					, Vector2::Zero
					, 0.03f
				);
			}
		}
		if (mCrashType != eSkillCrashType::END
			&& crashFunction[(int)mCrashType] != eCrashType::Overlay)
		{
			mAnimator->StartEvent(crashNames[(int)mCrashType] + L"anim") = std::make_shared<std::function<void()>>([this]()
			{
				if (mCrashType == eSkillCrashType::IceCrash1)
				{
					Vector3 mPos = GET_POS(GetOwner());
					mPos.y -= 45.f;
					mPos.x += 20.f;
					SET_POS_VEC(GetOwner(), mPos);
				}
				if (crashProgress[(int)mCrashType] != 0)
					mAnimator->SetAnimationProgressIndex(crashProgress[(int)mCrashType]);
			});
			//mAnimator->ProgressEvent(crashNames[(int)mCrashType] + L"anim") = [=]()
			//{
				//Collider2D* col = GetOwner()->GetComponent<Collider2D>();
				//if(mTarget)
				//{
				//	if(col->SearchObjectGameObjectId(mTarget->GetGameObjectId()))
				//	{
				//		mTarget->Hit(10);
				//	}
				//}else
				//{
				//	if (col->GetOnStay())
				//	{
				//		for (Collider2D* otherCol : col->GetCollidereds())
				//		{
				//			if (otherCol->GetColliderFunctionType() == eColliderFunctionType::HitArea)
				//			{
				//				Monster* monster = dynamic_cast<Monster*>(otherCol->GetOwner());
				//				if (nullptr != monster)
				//					monster->Hit(10);
				//			}
				//		}
				//	}
				//}
			//};
			mAnimator->EndEvent(crashNames[(int)mCrashType] + L"anim") = std::make_shared<std::function<void()>>([this]()
			{
				GetOwner()->ReleaseAnimators();
				GetOwner()->SetState(GameObject::eState::Delete);
			});
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
		);

		mAnimator->PlayAnimation(L"noneRectAnim", true);
	}
	void FallScript::OnCollisionEnter(Collider2D* other)
	{
		if (mTarget) return;

		if (other->GetColliderFunctionType() == eColliderFunctionType::HitArea)
		{
			switch (dynamic_cast<Skill*>(GetOwner())->GetLayerType())
			{
			case m::enums::eLayerType::PlayerSkill:
			{
				if (crashFunction[(int)mCrashType] == eCrashType::Overlay)
				{
					Monster* monster = dynamic_cast<Monster*>(other->GetOwner());

					if (monster)
					{
						OverlayEffectSkillScript* mOESS = monster->GetHSO()->GetComponent<OverlayEffectSkillScript>();
						mOESS->SetSkillType(mType);
						monster->GetHSO()->ActiveOverlay();
					}

					GetOwner()->ReleaseAnimators();
					GetOwner()->SetState(GameObject::eState::Delete);
				}
				if (crashFunction[(int)mCrashType] == eCrashType::Addiction)
				{
					dynamic_cast<Monster*>(other->GetOwner())->Addiction(10, 10.f, 10);
				}
				dynamic_cast<Monster*>(other->GetOwner())->Hit(PlayerStatus::damage);
			}
			break;
			case m::enums::eLayerType::MonsterSkill:
			{
				if (crashFunction[(int)mCrashType] == eCrashType::Overlay)
				{
					PlayerScript* ps = other->GetOwner()->GetComponent<PlayerScript>();

					OverlayEffectSkillScript* mOESS = ps->GetHSO()->GetComponent<OverlayEffectSkillScript>();
					mOESS->SetSkillType(mType);
					//if(!mOESS->IsPlayHit())
					ps->GetHSO()->ActiveOverlay();

					GetOwner()->ReleaseAnimators();
					GetOwner()->SetState(GameObject::eState::Delete);
				}
				if (crashFunction[(int)mCrashType] == eCrashType::Addiction)
				{
					dynamic_cast<Player*>(other->GetOwner())->Addiction(10, 10.f, 10);
				}
				dynamic_cast<Player*>(other->GetOwner())->Hit(5);
			}
			break;
			default:
				break;
			}
			if (crashFunction[(int)mCrashType] != eCrashType::Overlay) dynamic_cast<Skill*>(GetOwner())->SetSkillCrash(true);
		}
	}
	void FallScript::OnCollisionStay(Collider2D* other)
	{
	}
	void FallScript::OnCollisionExit(Collider2D* other)
	{
	}
	void FallScript::Update()
	{
		if (bArrival)
		{
			eSkillCrashType crashType;
			if (mACType == eAccessorySkillType::END)
				crashType = skillCrashTypes[(int)mType];
			else
				crashType = accessorySkillCrashTypes[(int)mACType];

			if (crashType == eSkillCrashType::END)
			{
				GetOwner()->ReleaseAnimators();
				GetOwner()->SetState(GameObject::eState::Delete);
			}
			if (crashType != eSkillCrashType::END
				&&
				mAnimator->GetActiveAnimation()->GetKey() != crashNames[(int)crashType] + L"anim")
			{
				SET_SCALE_XYZ(GetOwner()
					, crashSizes[(int)crashType].x
					, crashSizes[(int)crashType].y
					, GET_POS(GetOwner()).z
				);

				ADD_COMP(GetOwner(), Collider2D);

				if (crashFunction[(int)crashType] != eCrashType::Overlay)
				{
					Collider2D* col = GetOwner()->GetComponent<Collider2D>();
					col->Resize();
					if (mType == eSkillType::meteor)
					{
						GetOwner()->PlayAnimators(crashNames[(int)crashType] + L"anim", false, crashSizes[(int)crashType], true, col);
					}
					mAnimator->PlayAnimation(crashNames[(int)crashType] + L"anim", false);
				}
				else
				{
					mAnimator->PlayAnimation(L"noneRectAnim", true);
				}
			}
			bArrival = false;
		}
		if (bSkillFire)
		{
			bSkillFire = false;
			if (mACType == eAccessorySkillType::END)
			{
				mAnimator->PlayAnimation(skillAnimNames[(int)mType] + L"anim", true);
			}
			else
			{
				mAnimator->PlayAnimation(accessorySkillNames[(int)mACType] + L"anim", true);

			}

		}

	}
	void FallScript::LateUpdate()
	{
	}
	void FallScript::Render()
	{
	}
}