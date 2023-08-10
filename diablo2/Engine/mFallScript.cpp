#include "mFallScript.h"

#include "mSkill.h"

namespace m
{
	FallScript::FallScript(eAccessorySkillType type)
		: mAcType(type)
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

		if (mAcType == eAccessorySkillType::END)
		{
			SHARED_MAT mat = RESOURCE_FIND(Material, skillAnimNames[(int)mType]);
			mAnimator->Create(
				skillAnimNames[(int)mType] + L"anim"
				, mat->GetTexture()
				, Vector2::Zero
				, skillSizes[(int)mType]
				, skillAnimLength[(int)mType]
				, Vector2::Zero
				, 0.3f
				, 0.5f
			);
		}
		else
		{
			SHARED_MAT mat = RESOURCE_FIND(Material, AccessorySkillNames[(int)mAcType]);
			UINT height = mat->GetTexture()->GetMetaDataHeight();
			UINT width = mat->GetTexture()->GetMetaDataWidth();
			mAnimator->Create(
				skillAnimNames[(int)mType] + L"anim"
				, mat->GetTexture()
				, Vector2::Zero
				, Vector2(width, height)
				, AccessorySkillAnimLength[(int)mType]
				, Vector2::Zero
				, 0.3f
				, 0.5f
				);
		}

	}
	void FallScript::Update()
	{
	}
	void FallScript::LateUpdate()
	{
	}
	void FallScript::Render()
	{
	}
}