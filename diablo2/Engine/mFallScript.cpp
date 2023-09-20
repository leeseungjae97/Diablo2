#include "mFallScript.h"

#include "mSkill.h"
#include "mMonster.h"

namespace m
{
	FallScript::FallScript(eAccessorySkillType type)
		: mACType(type)
		, bSkillFire(false)
		, bArrival(false)
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
			mAnimator->EndEvent(skillAnimNames[(int)mType] + L"anim") = [this]()
			{
				dynamic_cast<Skill*>(GetOwner())->SetSkillCrash(true);
			};

			SHARED_MAT crashMat = RESOURCE_FIND(Material, crashNames[(int)mCrashType]);
			if(mType == eSkillType::meteor)
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
			mAnimator->EndEvent(accessorySkillNames[(int)mACType] + L"anim") = [this]()
			{
				dynamic_cast<Skill*>(GetOwner())->SetSkillCrash(true);
			};
			
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
		if (mCrashType != eSkillCrashType::END)
		{
			mAnimator->StartEvent(crashNames[(int)mCrashType] + L"anim") = [this]()
			{
				if(mCrashType == eSkillCrashType::IceCrash1)
				{
					Vector3 mPos = GET_POS(GetOwner());
					mPos.y -= 45.f;
					mPos.x += 20.f;
					SET_POS_VEC(GetOwner(), mPos);
				}
				if(crashProgress[(int)mCrashType] != 0)
					mAnimator->SetAnimationProgressIndex(crashProgress[(int)mCrashType]);
			};
			mAnimator->ProgressEvent(crashNames[(int)mCrashType] + L"anim") = [=]()
			{
				Collider2D* col = GetOwner()->GetComponent<Collider2D>();
				if (col->GetOnStay())
				{
					for (Collider2D* otherCol : col->GetCollidereds())
					{
						if (otherCol->GetColliderFunctionType() == eColliderFunctionType::HitArea)
						{
							Monster* monster = dynamic_cast<Monster*>(otherCol->GetOwner());
							if (nullptr != monster)
								monster->Hit(10);
						}
					}
				}
			};
			mAnimator->EndEvent(crashNames[(int)mCrashType] + L"anim") = [this]()
			{
				GetOwner()->ReleaseAnimators();
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
		);

		mAnimator->PlayAnimation(L"noneRectAnim", false);
	}
	void FallScript::OnCollisionEnter(Collider2D* other)
	{
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
			if (mACType == eAccessorySkillType::END)
			{
				eSkillCrashType crashType = skillCrashTypes[(int)mType];
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
					Collider2D* col = GetOwner()->GetComponent<Collider2D>();
					col->Resize();
					mAnimator->PlayAnimation(crashNames[(int)crashType] + L"anim", false);
					if (mType == eSkillType::meteor)
					    GetOwner()->PlayAnimators(crashNames[(int)crashType] + L"anim", false, crashSizes[(int)crashType] , true, col);
				}	
			}
			else
			{
				eSkillCrashType crashType = accessorySkillCrashTypes[(int)mACType];
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
					Collider2D* col = GetOwner()->GetComponent<Collider2D>();
					col->Resize();
					mAnimator->PlayAnimation(crashNames[(int)crashType] + L"anim", false);

					if (mType == eSkillType::meteor)
					    GetOwner()->PlayAnimators(crashNames[(int)crashType] + L"anim", false, crashSizes[(int)crashType], true, col);
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