#include "mPlayerOverlayEffectSkillScript.h"

#include "mSkill.h"

namespace m
{
	PlayerOverlayEffectSkillScript::PlayerOverlayEffectSkillScript()
	{
	}
	PlayerOverlayEffectSkillScript::~PlayerOverlayEffectSkillScript()
	{
	}
	void PlayerOverlayEffectSkillScript::Initialize()
	{
		mAnimator = ADD_COMP(GetOwner(), Animator);
		Skill* dSkill = dynamic_cast<Skill*>(GetOwner());
		if (nullptr == dSkill) mType = eSkillType::normalAttack;
		else mType = dSkill->GetSkillType();

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
	void PlayerOverlayEffectSkillScript::Update()
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
	void PlayerOverlayEffectSkillScript::LateUpdate()
	{
	}
	void PlayerOverlayEffectSkillScript::Render()
	{
	}
	void PlayerOverlayEffectSkillScript::OnCollisionEnter(Collider2D* other)
	{
	}
	void PlayerOverlayEffectSkillScript::OnCollisionStay(Collider2D* other)
	{
	}
	void PlayerOverlayEffectSkillScript::OnCollisionExit(Collider2D* other)
	{
	}
}