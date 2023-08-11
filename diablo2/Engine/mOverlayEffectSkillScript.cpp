#include "mOverlayEffectSkillScript.h"

#include "../engine_source/mMeshRenderer.h"

#include "mSkill.h"
#include "mPlayerInfo.h"

namespace m
{
	OverlayEffectSkillScript::OverlayEffectSkillScript(int index)
		: skillIndex(index)
		, bPlaySkill(false)
		
	{
		mType = eSkillType::END;
	}
	OverlayEffectSkillScript::~OverlayEffectSkillScript()
	{
	}
	void OverlayEffectSkillScript::Initialize()
	{
		mAnimator = GET_COMP(GetOwner(), Animator);

		UpdateOverlaySkill();
		//if (skillCastNames[(int)mType] != L"")
		mAnimator->PlayAnimation(L"noneRectAnim", true);
	}
	void OverlayEffectSkillScript::Update()
	{
		if (bPlaySkill)
		{
			UpdateOverlaySkill();
			eSkillCastType castType = skillCastTypes[(int)mType];
			if (castNames[(int)castType] != L"")
				mAnimator->PlayAnimation(castNames[(int)castType] + L"anim", false);
			bPlaySkill = false;
		}
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
	void OverlayEffectSkillScript::UpdateOverlaySkill()
	{
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

		if (mType == PlayerInfo::GetSkill(skillIndex)) return;

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
		
	
		//mAnimator->StartEvent(skillCastNames[(int)mType] + L"anim") = [this]()
		//{
		//	bPlaySkill = false;
		//};
	}
}