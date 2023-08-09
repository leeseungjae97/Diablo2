#include "mOverlayEffectSkillScript.h"

#include "mSkill.h"
#include "mPlayerInfo.h"

namespace m
{
	OverlayEffectSkillScript::OverlayEffectSkillScript()
	{
	}
	OverlayEffectSkillScript::~OverlayEffectSkillScript()
	{
	}
	void OverlayEffectSkillScript::Initialize()
	{
		mType = dynamic_cast<Skill*>(GetOwner())->GetSkillType();
		mAnimator = dynamic_cast<Skill*>(GetOwner())->GetCastAnimator();

		SHARED_MAT mat = RESOURCE_FIND(Material, skillCastNames[(int)mType]);
		mAnimator->Create(
			skillCastNames[(int)mType] + L"anim"
			, mat->GetTexture()
			, Vector2::Zero
			, skillCastSizes[(int)mType]
			, skillCastLength[(int)mType]
			, Vector2::Zero
			, 0.03f
		);
		mAnimator->EndEvent(skillCastNames[(int)mType] + L"anim") = [this]()
		{
			//std::vector<PlayerOverlayEffectSkillScript*> comps 
			//	= GetOwner()->GetComponents<PlayerOverlayEffectSkillScript>();
			//for (PlayerOverlayEffectSkillScript* comp : comps)
			//{
			//	std::erase(comps, comp);
			//}
			//DELETE_COMP(GetOwner(), this);
		};
	}
	void OverlayEffectSkillScript::Update()
	{

		if (GetOwner()->GetState() == GameObject::eBattleState::Cast)
		{
			if (nullptr == mAnimator->GetActiveAnimation() 
				|| mAnimator->GetActiveAnimation()->GetKey() != skillCastNames[(int)mType] + L"anim")
			{
				mAnimator->PlayAnimation(skillCastNames[(int)mType] + L"anim", false);
			}
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
}