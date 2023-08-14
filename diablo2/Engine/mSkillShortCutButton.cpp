#include "mSkillShortCutButton.h"

#include "../engine_source/mMeshRenderer.h"
#include "../engine_source/mTexture.h"

#include "mPlayerInfo.h"

namespace m
{
	SkillShortCutButton::SkillShortCutButton(int skillIndex)
		: mSkillType(eSkillType::normalAttack)
		, mSkillIndex(skillIndex)
	{
		SetClickMaterial(RESOURCE_FIND(Material, L"normalAttackClickIcon"));
		SetNormalMaterial(RESOURCE_FIND(Material, L"normalAttackIcon"));
	}
	SkillShortCutButton::~SkillShortCutButton()
	{
	}
	void SkillShortCutButton::Initialize()
	{
		Button::Initialize();

	}
	void SkillShortCutButton::Update()
	{
		Button::Update();
		if (PlayerInfo::GetSkill(mSkillIndex) != mSkillType)
		{
			mSkillType = PlayerInfo::GetSkill(mSkillIndex);
			
			SetClickMaterial(RESOURCE_FIND(Material, wsSkillClickIconNames[(int)mSkillType]));
			SetNormalMaterial(RESOURCE_FIND(Material, wsSkillIconNames[(int)mSkillType]));
		}
	}
	void SkillShortCutButton::LateUpdate()
	{
		Button::LateUpdate();
	}
	void SkillShortCutButton::Render()
	{
		Button::Render();
	}
}