#include "mOverlayEffectSkillScript.h"

#include "../engine_source/mMeshRenderer.h"

#include "mSkill.h"
#include "mPlayerInfo.h"

namespace m
{
	OverlayEffectSkillScript::OverlayEffectSkillScript(int index)
		: skillIndex(index)
		, bPlaySkill(false)
		, bHit(true)
		
	{
		mType = eSkillType::END;
	}
	OverlayEffectSkillScript::~OverlayEffectSkillScript()
	{
	}
	void OverlayEffectSkillScript::Initialize()
	{
		mAnimator = GET_COMP(GetOwner(), Animator);

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
	void OverlayEffectSkillScript::Update()
	{
		if (mAnimator->GetActiveAnimation()->IsComplete())mAnimator->PlayAnimation(L"noneRectAnim", true);
		if (bPlaySkill)
		{
			UpdateOverlaySkill();
			if (skillIndex == -1)
			{
				eSkillCrashType crashType = skillCrashTypes[(int)mType];
				if (crashNames[(int)crashType] != L"")
					mAnimator->PlayAnimation(crashNames[(int)crashType] + L"anim", false);
				bPlaySkill = false;
			}
			else
			{
				eSkillCastType castType = skillCastTypes[(int)mType];
				if (castNames[(int)castType] != L"")
				{
					if (mAnimator->GetActiveAnimation()->GetKey() != castNames[(int)castType] + L"anim")
						mAnimator->PlayAnimation(castNames[(int)castType] + L"anim", false);
				}
				bPlaySkill = false;
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
	void OverlayEffectSkillScript::UpdateOverlaySkill()
	{
		//if (mType == PlayerInfo::GetSkill(skillIndex)) return;
		if (skillIndex == -1)
		{
			if (eSkillType::END != mType)
			{
				eSkillCrashType crashType = skillCrashTypes[(int)mType];
				SHARED_MAT mat = RESOURCE_FIND(Material, crashNames[(int)crashType]);

				mAnimator->Create(
					crashNames[(int)crashType] + L"anim"
					, mat->GetTexture()
					, Vector2::Zero
					, crashSizes[(int)crashType]
					, crashLength[(int)crashType]
					, Vector2::Zero
					, 0.03f
					, 0.7f
				);
				//mAnimator->StartEvent(crashNames[(int)crashType] + L"anim")
				//	= [this]()
				//{
				//	bHit = true;
				//};
			}
		}
		else
		{
			mType = PlayerInfo::GetSkill(skillIndex);
			eSkillCastType castType = skillCastTypes[(int)mType];

			if (castNames[(int)castType] == L"") return;

			SHARED_MAT mat = RESOURCE_FIND(Material, castNames[(int)castType]);

			mAnimator->Create(
				castNames[(int)castType] + L"anim"
				, mat->GetTexture()
				, Vector2::Zero
				, castSizes[(int)castType]
				, castLength[(int)castType]
				, Vector2::Zero
				, 0.03f
				, 0.3f
			);
		}
		
		
	
		//mAnimator->StartEvent(skillCastNames[(int)mType] + L"anim") = [this]()
		//{
		//	bPlaySkill = false;
		//};
	}
}