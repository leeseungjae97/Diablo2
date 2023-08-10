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
			if (skillCastNames[(int)mType] != L"")
				mAnimator->PlayAnimation(skillCastNames[(int)mType] + L"anim", false);
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

		if (skillCastNames[(int)mType] == L"") return;

		SHARED_MAT mat = RESOURCE_FIND(Material, skillCastNames[(int)mType]);

		mAnimator->Create(
			skillCastNames[(int)mType] + L"anim"
			, mat->GetTexture()
			, Vector2::Zero
			, skillCastSizes[(int)mType]
			, skillCastLength[(int)mType]
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