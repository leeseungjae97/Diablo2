#pragma once
#include "SkillLookUpTables.h"

enum class eSummonsType
{
	Hydra,
	End,
};
struct SummonsData
{
	enum class eSummonsAnimationType
	{
		Natural,
		Summon,
		Attack,
		Dead,
		End
	};
	enum class eSummonsOverlayType
	{
		Attack,
		Summon,
		Dead,
		Natural,
		End,
	};

	std::wstring overlayMaterialString[(int)eSummonsOverlayType::End] = {};
	m::math::Vector2 overlaySize[(int)eSummonsOverlayType::End] = {};
	m::math::Vector2 overlayOffset[(int)eSummonsOverlayType::End] = {};
	m::math::Vector2 overlayCenterPos[(int)eSummonsOverlayType::End] = {};
	int overlayAnimLength[(int)eSummonsOverlayType::End] = {};
	int overlayStartIndex[(int)eSummonsOverlayType::End] = {};
	int overlayProgIndex[(int)eSummonsOverlayType::End] = {};
	int overlayEndIndex[(int)eSummonsOverlayType::End] = {};
	float overlayAnimDuration[(int)eSummonsOverlayType::End] = {};

	std::wstring overlay2MaterialString[(int)eSummonsOverlayType::End] = {};
	m::math::Vector2 overlay2Size[(int)eSummonsOverlayType::End] = {};
	m::math::Vector2 overlay2Offset[(int)eSummonsOverlayType::End] = {};
	m::math::Vector2 overlay2CenterPos[(int)eSummonsOverlayType::End] = {};
	int overlay2AnimLength[(int)eSummonsOverlayType::End] = {};
	int overlay2StartIndex[(int)eSummonsOverlayType::End] = {};
	int overlay2ProgIndex[(int)eSummonsOverlayType::End] = {};
	int overlay2EndIndex[(int)eSummonsOverlayType::End] = {};
	float overlay2AnimDuration[(int)eSummonsOverlayType::End] = {};

	std::wstring summonMaterialString[(int)eSummonsAnimationType::End] = {};
	m::math::Vector2 summonsSize[(int)eSummonsAnimationType::End] = {};
	m::math::Vector2 summonsOffset[(int)eSummonsAnimationType::End] = {};
	m::math::Vector2 summonsCenterPos[(int)eSummonsAnimationType::End] = {};
	int summonsAnimLength[(int)eSummonsAnimationType::End] = {};
	int summonsStartIndex[(int)eSummonsAnimationType::End] = {};
	int summonsProgIndex[(int)eSummonsAnimationType::End] = {};
	int summonsEndIndex[(int)eSummonsAnimationType::End] = {};
	int summonsOverlayType[(int)eSummonsAnimationType::End] = {};
	float summonsAnimDuration[(int)eSummonsAnimationType::End] = {};

	m::eSkillType summonSkill = m::eSkillType::END;
	m::math::Vector2 attackRange = m::math::Vector2::Zero;

};
struct Hydra : public SummonsData
{
	std::wstring summonMaterialString[(int)eSummonsAnimationType::End] = {
		L"hydraNatural",
		L"hydraSummon",
		L"hydraAttack",
		L"hydraDead",
	};
	m::math::Vector2 summonsSize[(int)eSummonsAnimationType::End] = {
		m::math::Vector2(85, 66),// Natural
		m::math::Vector2(84, 84),// Summon
		m::math::Vector2(104, 67),// Attack
		m::math::Vector2(88, 80),// Dead
	};
	m::math::Vector2 summonsOffset[(int)eSummonsAnimationType::End] = {
		m::math::Vector2(0.f, 0.f),// Natural
		m::math::Vector2(0.f, 0.f),// Summon
		m::math::Vector2(0.f, 0.f),// Attack
		m::math::Vector2(0.f, 0.f),// Dead
	};
	m::math::Vector2 summonsCenterPos[(int)eSummonsAnimationType::End] = {
		m::math::Vector2(0.f, 0.f),// Natural
		m::math::Vector2(0.f, 0.f),// Summon
		m::math::Vector2(0.f, 0.f),// Attack
		m::math::Vector2(0.f, 0.f),// Dead
	};
	int summonsAnimLength[(int)eSummonsAnimationType::End] = {
		12,// Natural
		12,// Summon
		12,// Attack
		10,// Dead
	};
	int summonsStartIndex[(int)eSummonsAnimationType::End] = {
		0,// Natural
		0,// Summon
		0,// Attack
		0,// Dead
	};
	int summonsProgIndex[(int)eSummonsAnimationType::End] = {
		0,// Natural
		0,// Summon
		8,// Attack
		0,// Dead
	};
	int summonsEndIndex[(int)eSummonsAnimationType::End] = {
		0,// Natural
		0,// Summon
		0,// Attack
		0,// Dead
	};
	int summonsOverlayType[(int)eSummonsAnimationType::End] = {
	};
	float summonsAnimDuration[(int)eSummonsAnimationType::End] = {
		0.05f,// Natural
		0.05f,// Summon
		0.05f,// Attack
		0.05f,// Dead
	};

	std::wstring overlayMaterialString[(int)eSummonsOverlayType::End] = {
		L"hydraNaturalFire",
		L"hydraSummonFire",
		L"hydraAttackFire",
		L"hydraDeadFire",
	};
	m::math::Vector2 overlaySize[(int)eSummonsOverlayType::End] = {
		m::math::Vector2(83.f, 78.f),
		m::math::Vector2(80.f, 87.f),
		m::math::Vector2(124.f, 82.f),
		m::math::Vector2(81.f, 88.f),
	};
	m::math::Vector2 overlayOffset[(int)eSummonsOverlayType::End] = {
		m::math::Vector2(0.f, 0.f),
		m::math::Vector2(0.f, 0.f),
		m::math::Vector2(0.f, 0.f),
		m::math::Vector2(0.f, 0.f),
	};
	m::math::Vector2 overlayCenterPos[(int)eSummonsOverlayType::End] = {
		m::math::Vector2(0.f, 0.f),
		m::math::Vector2(0.f, 0.f),
		m::math::Vector2(0.f, 0.f),
		m::math::Vector2(0.f, 0.f),
	};
	int overlayAnimLength[(int)eSummonsOverlayType::End] = {
		12,
		12,
		12,
		10,
	};
	int overlayStartIndex[(int)eSummonsOverlayType::End] = {
		0,
		0,
		0,
		0,
	};
	int overlayProgIndex[(int)eSummonsOverlayType::End] = {
		0,
		0,
		0,
		0,
	};
	int overlayEndIndex[(int)eSummonsOverlayType::End] = {
		0,
		0,
		0,
		0,
	};
	float overlayAnimDuration[(int)eSummonsOverlayType::End] = {
	summonsAnimDuration[(int)SummonsData::eSummonsAnimationType::Natural],
	summonsAnimDuration[(int)SummonsData::eSummonsAnimationType::Summon],
	summonsAnimDuration[(int)SummonsData::eSummonsAnimationType::Attack],
	summonsAnimDuration[(int)SummonsData::eSummonsAnimationType::Dead],
	};

	std::wstring overlay2MaterialString[(int)eSummonsOverlayType::End] = {
	L"hydraOverlayFireLoop",
	L"hydraOverlayFireStart",
	L"",
	L"hydraOverlayFireEnd",
	};
	m::math::Vector2 overlay2Size[(int)eSummonsOverlayType::End] = {
		m::math::Vector2(63.f, 90.f),
		m::math::Vector2(114.f,99.f),
		m::math::Vector2(),
		m::math::Vector2(60.f, 81.f),
	};
	m::math::Vector2 overlay2Offset[(int)eSummonsOverlayType::End] = {
		m::math::Vector2(0.f, 0.f),
		m::math::Vector2(0.f, 0.f),
		m::math::Vector2(0.f, 0.f),
		m::math::Vector2(0.f, 0.f),
	};
	m::math::Vector2 overlay2CenterPos[(int)eSummonsOverlayType::End] = {
		m::math::Vector2(0.f, 0.f),
		m::math::Vector2(0.f, 0.f),
		m::math::Vector2(0.f, 0.f),
		m::math::Vector2(0.f, 0.f),
	};
	int overlay2AnimLength[(int)eSummonsOverlayType::End] = {
		20,
		16,
		0,
		16,
	};
	int overlay2StartIndex[(int)eSummonsOverlayType::End] = {
		0,
		0,
		0,
		0,
	};
	int overlay2ProgIndex[(int)eSummonsOverlayType::End] = {
		0,
		0,
		0,
		0,
	};
	int overlay2EndIndex[(int)eSummonsOverlayType::End] = {
		0,
		0,
		0,
		0,
	};
	float overlay2AnimDuration[(int)eSummonsOverlayType::End] = {
	0.03f,
	0.03f,
	0.f,
	0.03f,
	};

	m::eSkillType summonSkill = m::eSkillType::fireBolt;
	m::math::Vector2 attackRange = m::math::Vector2(500.f, 200.f);
};
