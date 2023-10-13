#include "mOverlayEffectSkillScript.h"

#include "../engine_source/mMeshRenderer.h"

#include "mSkill.h"
#include "mPlayerManager.h"

namespace m
{
	OverlayEffectSkillScript::OverlayEffectSkillScript(int index)
		: skillIndex(index)
		, bPlaySkill(false)
		, mCastType(eSkillCastType::END)
		, bHit(true)
		, bBack(false)
	{
		mType = eSkillType::END;
	}
	OverlayEffectSkillScript::~OverlayEffectSkillScript()
	{
	}
	void OverlayEffectSkillScript::Initialize()
	{
		mAnimator = GET_COMP(GetOwner(), Animator);
		mAudioSource = GET_COMP(GetOwner(), AudioSource);

		SHARED_MAT noneMat = RESOURCE_FIND(Material, L"noneRect");
		mAnimator->Create(
			L"noneRectAnim"
			, noneMat->GetTexture()
			, Vector2::Zero
			, Vector2(20.f, 20.f)
			, 1
			, Vector2::Zero
			, 0.03f
			, 0.8f
		);
		mAnimator->PlayAnimation(L"noneRectAnim", true);
	}
	void OverlayEffectSkillScript::Update()
	{
		if (mAnimator->GetActiveAnimation()->IsComplete()) mAnimator->PlayAnimation(L"noneRectAnim", true);
		if (mAnimator->GetActiveAnimation()->IsStop()) mAnimator->PlayAnimation(L"noneRectAnim", true);

		if (bPlaySkill)
		{
			if (bBack)
			{
				UpdateBackOverlaySkill();
			}
			else
			{
				UpdateOverlaySkill();
			}
		}
		//else mAnimator->PlayAnimation(L"noneRectAnim", true);
	}
	void OverlayEffectSkillScript::LateUpdate()
	{
	}
	void OverlayEffectSkillScript::Render()
	{
	}
	void OverlayEffectSkillScript::OnCollisionEnter(Collider2D* other)
	{
	}
	void OverlayEffectSkillScript::OnCollisionStay(Collider2D* other)
	{
	}
	void OverlayEffectSkillScript::OnCollisionExit(Collider2D* other)
	{
	}
	void OverlayEffectSkillScript::SetSkillType(eSkillType type)
	{
		SkillScript::SetSkillType(type);
	}

	void OverlayEffectSkillScript::UpdateBackOverlaySkill()
	{
		mType = PlayerManager::GetSkill(skillIndex);
		eSkillCastType castType = skillCastTypes[(int)mType];

		if (backCastNames[(int)castType] == L"") return;

		SHARED_MAT mat = RESOURCE_FIND(Material, backCastNames[(int)castType]);

		mAnimator->Create(
			backCastNames[(int)castType] + L"anim"
			, mat->GetTexture()
			, Vector2::Zero
			, backCastSizes[(int)castType]
			, backCastLength[(int)castType]
			, backCastOffset[(int)castType]
			, backCastCenterPos[(int)castType]
			, 0.03f
			, 0.8f
		);
		SET_SCALE_XYZ(GetOwner(), backCastSizes[(int)castType].x, backCastSizes[(int)castType].y, 1.f);

		if (backCastNames[(int)castType] != L"")
		{
			if (mAnimator->GetActiveAnimation()->GetKey() != backCastNames[(int)castType] + L"anim")
			{
				mAnimator->PlayAnimation(backCastNames[(int)castType] + L"anim", false);
			}
		}
		bPlaySkill = false;
	}

	void OverlayEffectSkillScript::UpdateOverlaySkill()
	{
		if (skillIndex == -1)
		{
			if (eSkillType::END != mType)
			{
				eSkillCrashType crashType = skillCrashTypes[(int)mType];
				if (crashType == eSkillCrashType::END) return;

				SHARED_MAT mat = RESOURCE_FIND(Material, crashNames[(int)crashType]);

				mAnimator->Create(
					crashNames[(int)crashType] + L"anim"
					, mat->GetTexture()
					, Vector2::Zero
					, crashSizes[(int)crashType]
					, crashLength[(int)crashType]
					, Vector2::Zero
					, crashCenterPos[(int)crashType]
					, 0.03f
					, 0.8f
				);
				SET_SCALE_XYZ(GetOwner(), crashSizes[(int)crashType].x, crashSizes[(int)crashType].y, 1.f);

				if (crashNames[(int)crashType] != L"")
				{
					mAnimator->PlayAnimation(crashNames[(int)crashType] + L"anim", crashLoop[(int)crashType]);
				}
				bPlaySkill = false;
			}
		}
		else
		{
			mType = PlayerManager::GetSkill(skillIndex);
			eSkillCastType castType = skillCastTypes[(int)mType];

			if (castNames[(int)castType] == L"") return;

			SHARED_MAT mat = RESOURCE_FIND(Material, castNames[(int)castType]);

			mAnimator->Create(
				castNames[(int)castType] + L"anim"
				, mat->GetTexture()
				, Vector2::Zero
				, castSizes[(int)castType]
				, castLength[(int)castType]
				, castOffset[(int)castType]
				, castCenterPos[(int)castType]
				, 0.03f
				, 0.8f
			);
			SET_SCALE_XYZ(GetOwner(), castSizes[(int)castType].x, castSizes[(int)castType].y, 1.f);

			if (castNames[(int)castType] != L"")
			{
				mAnimator->StartEvent(castNames[(int)castType] + L"anim")
					= std::make_shared<std::function<void()>>([=]()
					{
						int iRandIndex = rand() % 3;
				        std::wstring rand = L"";
				        rand = skillCastSoundPath[(int)castType];
				        if (rand != L"")
					        mAudioSource->PlayNoDelay(rand, false, false);
					}
				);
				if (mAnimator->GetActiveAnimation()->GetKey() != castNames[(int)castType] + L"anim")
				{
					mAnimator->PlayAnimation(castNames[(int)castType] + L"anim", false);
				}
			}
			bPlaySkill = false;
		}

	}

	void OverlayEffectSkillScript::StopOverlaySkill()
	{
		if (nullptr == mAnimator) return;

		mAnimator->PlayAnimation(L"noneRectAnim", true);
	}
}
