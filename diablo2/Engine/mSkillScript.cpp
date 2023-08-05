#include "mSkillScript.h"

#include "../engine_source/mAnimator.h"
#include "../engine_source/mGameObject.h"

#include "mSkill.h"

namespace m
{
	SkillScript::SkillScript()
	{
		mAnimator = ADD_COMP(GetOwner(), Animator);
		Skill* dSkill = dynamic_cast<Skill*>(GetOwner());
		if (nullptr == dSkill) mType = eSkillType::normalAttack;
		else mType = dSkill->GetSkillType();
	}
	SkillScript::~SkillScript()
	{
	}
	void SkillScript::Initialize()
	{
	}
	void SkillScript::Update()
	{
	}
	void SkillScript::LateUpdate()
	{
	}
	void SkillScript::Render()
	{
	}
	void SkillScript::OnCollisionEnter(Collider2D* other)
	{
	}
	void SkillScript::OnCollisionStay(Collider2D* other)
	{
	}
	void SkillScript::OnCollisionExit(Collider2D* other)
	{
		
	}
}