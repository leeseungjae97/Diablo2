#pragma once
#include "SkillLookUpTables.h"
namespace m
{
	enum class eSkillDirection
	{
		LeftDown1,
		LeftUp1,
		RightUp1,
		RightDown1,
		Down,
		Left,
		Up,
		Right,
		LeftDown2,
		LeftDown3,
		LeftUp2,
		LeftUp3,
		RightUp2,
		RightUp3,
		RightDown2,
		RightDown3,
		End
	};

	std::wstring skillDirectionString[(UINT)eSkillDirection::End] = {
		L"left_down_1",
		L"left_up_1",
		L"right_up_1",
		L"right_down_1",
		L"down",
		L"left",
		L"up",
		L"right",
		L"left_down_2",
		L"left_down_3",
		L"left_up_2",
		L"left_up_3",
		L"right_up_2",
		L"right_up_3",
		L"right_down_2",
		L"right_down_3",
	};
	float skillSpeed[(int)eSkillType::END] = {
		300.f,// iceBolt
		0.f,// frozenArmor
		0.f,// frostNova
		0.f,// iceBlast
		0.f,// shiverArmor
		0.f,// clacialSpike
		0.f,// blizzard
		0.f,// chillingArmor
		0.f,// frozenOrb
		0.f,// coldMastery
				//
		0.f,// chargedBolt
		0.f,// staticField
		0.f,// telekinesis
		0.f,// nove
		0.f,// lightning
		0.f,// chainLightning
		0.f,// teleport
		0.f,// thunderStorm
		0.f,// energyShield
		0.f,// lightningMastery
				//
		300.f,// fireBolt
		0.f,// warmth
		0.f,// inferno
		0.f,// blaze
		0.f,// fireBall
		0.f,// fireWall
		0.f,// enchant
		0.f,// meteor
		0.f,// fireMastery
		0.f,// hydra
				//
		0.f,// normalAttack

	};
	int skillAnimLength[(int)eSkillType::END] = {
		6, // iceBolt
		0, // frozenArmor
		0, // frostNova
		0, // iceBlast
		0, // shiverArmor
		0, // clacialSpike
		0, // blizzard
		0, // chillingArmor
		0, // frozenOrb
		0, // coldMastery
		//
		5, // chargedBolt
		0, // staticField
		0, // telekinesis
		0, // nove
		0, // lightning
		0, // chainLightning
		0, // teleport
		0, // thunderStorm
		0, // energyShield
		0, // lightningMastery
		//
		5, // fireBolt
		0, // warmth
		0, // inferno
		0, // blaze
		0, // fireBall
		0, // fireWall
		0, // enchant
		0, // meteor
		0, // fireMastery
		0, // hydra
		//
		0, // normalAttack
	};
	m::math::Vector2 skillSizes[(int)eSkillType::END] = {
		m::math::Vector2(92.f, 55.f),// iceBolt,
		m::math::Vector2(0.f, 0.f),// frozenArmor,
		m::math::Vector2(0.f, 0.f),// frostNova,
		m::math::Vector2(0.f, 0.f),// iceBlast,
		m::math::Vector2(0.f, 0.f),// shiverArmor,
		m::math::Vector2(0.f, 0.f),// clacialSpike,
		m::math::Vector2(0.f, 0.f),// blizzard,
		m::math::Vector2(0.f, 0.f),// chillingArmor,
		m::math::Vector2(0.f, 0.f),// frozenOrb,
		m::math::Vector2(0.f, 0.f),// coldMastery,
		
		m::math::Vector2(0.f, 0.f),// chargedBolt,
		m::math::Vector2(0.f, 0.f),// staticField,
		m::math::Vector2(0.f, 0.f),// telekinesis,
		m::math::Vector2(0.f, 0.f),// nove,
		m::math::Vector2(0.f, 0.f),// lightning,
		m::math::Vector2(0.f, 0.f),// chainLightning,
		m::math::Vector2(0.f, 0.f),// teleport,
		m::math::Vector2(0.f, 0.f),// thunderStorm,
		m::math::Vector2(0.f, 0.f),// energyShield,
		m::math::Vector2(0.f, 0.f),// lightningMastery,
		
		m::math::Vector2(116.f, 66.f),// fireBolt,
		m::math::Vector2(0.f, 0.f),// warmth,
		m::math::Vector2(0.f, 0.f),// inferno,
		m::math::Vector2(0.f, 0.f),// blaze,
		m::math::Vector2(0.f, 0.f),// fireBall,
		m::math::Vector2(0.f, 0.f),// fireWall,
		m::math::Vector2(0.f, 0.f),// enchant,
		m::math::Vector2(0.f, 0.f),// meteor,
		m::math::Vector2(0.f, 0.f),// fireMastery,
		m::math::Vector2(0.f, 0.f),// hydra,

		m::math::Vector2(0.f),// normalAttack,
	};
	m::math::Vector2 skillCrashSizes[(int)eSkillType::END] = {
		m::math::Vector2(0.f, 0.f),// iceBolt
		m::math::Vector2(0.f, 0.f),// frozenArmor
		m::math::Vector2(0.f, 0.f),// frostNova
		m::math::Vector2(0.f, 0.f),// iceBlast
		m::math::Vector2(0.f, 0.f),// shiverArmor
		m::math::Vector2(0.f, 0.f),// clacialSpike
		m::math::Vector2(0.f, 0.f),// blizzard
		m::math::Vector2(0.f, 0.f),// chillingArmor
		m::math::Vector2(0.f, 0.f),// frozenOrb
		m::math::Vector2(0.f, 0.f),// coldMastery

		m::math::Vector2(0.f, 0.f),// chargedBolt
		m::math::Vector2(0.f, 0.f),// staticField
		m::math::Vector2(0.f, 0.f),// telekinesis
		m::math::Vector2(0.f, 0.f),// nove
		m::math::Vector2(0.f, 0.f),// lightning
		m::math::Vector2(0.f, 0.f),// chainLightning
		m::math::Vector2(0.f, 0.f),// teleport
		m::math::Vector2(0.f, 0.f),// thunderStorm
		m::math::Vector2(0.f, 0.f),// energyShield
		m::math::Vector2(0.f, 0.f),// lightningMastery

		m::math::Vector2(78.f, 70.f),// fireBolt
		m::math::Vector2(0.f, 0.f),// warmth
		m::math::Vector2(0.f, 0.f),// inferno
		m::math::Vector2(0.f, 0.f),// blaze
		m::math::Vector2(0.f, 0.f),// fireBall
		m::math::Vector2(0.f, 0.f),// fireWall
		m::math::Vector2(0.f, 0.f),// enchant
		m::math::Vector2(0.f, 0.f),// meteor
		m::math::Vector2(0.f, 0.f),// fireMastery
		m::math::Vector2(0.f, 0.f),// hydra

		m::math::Vector2(0.f, 0.f),// normalAttack
	};
	m::math::Vector2 skillCastSizes[(int)eSkillType::END] = {
		m::math::Vector2(0.f, 0.f),// iceBolt
		m::math::Vector2(0.f, 0.f),// frozenArmor
		m::math::Vector2(0.f, 0.f),// frostNova
		m::math::Vector2(0.f, 0.f),// iceBlast
		m::math::Vector2(0.f, 0.f),// shiverArmor
		m::math::Vector2(0.f, 0.f),// clacialSpike
		m::math::Vector2(0.f, 0.f),// blizzard
		m::math::Vector2(0.f, 0.f),// chillingArmor
		m::math::Vector2(0.f, 0.f),// frozenOrb
		m::math::Vector2(0.f, 0.f),// coldMastery

		m::math::Vector2(0.f, 0.f),// chargedBolt
		m::math::Vector2(0.f, 0.f),// staticField
		m::math::Vector2(0.f, 0.f),// telekinesis
		m::math::Vector2(0.f, 0.f),// nove
		m::math::Vector2(0.f, 0.f),// lightning
		m::math::Vector2(0.f, 0.f),// chainLightning
		m::math::Vector2(0.f, 0.f),// teleport
		m::math::Vector2(0.f, 0.f),// thunderStorm
		m::math::Vector2(0.f, 0.f),// energyShield
		m::math::Vector2(0.f, 0.f),// lightningMastery

		m::math::Vector2(78.f, 70.f),// fireBolt
		m::math::Vector2(0.f, 0.f),// warmth
		m::math::Vector2(0.f, 0.f),// inferno
		m::math::Vector2(0.f, 0.f),// blaze
		m::math::Vector2(0.f, 0.f),// fireBall
		m::math::Vector2(0.f, 0.f),// fireWall
		m::math::Vector2(0.f, 0.f),// enchant
		m::math::Vector2(0.f, 0.f),// meteor
		m::math::Vector2(0.f, 0.f),// fireMastery
		m::math::Vector2(0.f, 0.f),// hydra

		m::math::Vector2(0.f, 0.f),// normalAttack
	};
	std::wstring skillCrashNames[(int)eSkillType::END] = {
		L"",// iceBolt
		L"",// frozenArmor
		L"",// frostNova
		L"",// iceBlast
		L"",// shiverArmor
		L"",// clacialSpike
		L"",// blizzard
		L"",// chillingArmor
		L"",// frozenOrb
		L"",// coldMastery

		L"",// chargedBolt
		L"",// staticField
		L"",// telekinesis
		L"",// nove
		L"",// lightning
		L"",// chainLightning
		L"",// teleport
		L"",// thunderStorm
		L"",// energyShield
		L"",// lightningMastery

		L"fireExplo1",// fireBolt
		L"",// warmth
		L"",// inferno
		L"",// blaze
		L"",// fireBall
		L"",// fireWall
		L"",// enchant
		L"",// meteor
		L"",// fireMastery
		L"",// hydra

		L"",// normalAttack
	};
	std::wstring skillCastNames[(int)eSkillType::END] = {
		L"",// iceBolt
		L"",// frozenArmor
		L"",// frostNova
		L"",// iceBlast
		L"",// shiverArmor
		L"",// clacialSpike
		L"",// blizzard
		L"",// chillingArmor
		L"",// frozenOrb
		L"",// coldMastery

		L"",// chargedBolt
		L"",// staticField
		L"",// telekinesis
		L"",// nove
		L"",// lightning
		L"",// chainLightning
		L"",// teleport
		L"",// thunderStorm
		L"",// energyShield
		L"",// lightningMastery

		L"fireBallCast",// fireBolt
		L"",// warmth
		L"",// inferno
		L"",// blaze
		L"",// fireBall
		L"",// fireWall
		L"",// enchant
		L"",// meteor
		L"",// fireMastery
		L"",// hydra

		L"",// normalAttack
	};
	int skillCrashLength[(int)eSkillType::END] = {
		0,// iceBolt
		0,// frozenArmor
		0,// frostNova
		0,// iceBlast
		0,// shiverArmor
		0,// clacialSpike
		0,// blizzard
		0,// chillingArmor
		0,// frozenOrb
		0,// coldMastery

		0,// chargedBolt
		0,// staticField
		0,// telekinesis
		0,// nove
		0,// lightning
		0,// chainLightning
		0,// teleport
		0,// thunderStorm
		0,// energyShield
		0,// lightningMastery

		12,// fireBolt
		0,// warmth
		0,// inferno
		0,// blaze
		0,// fireBall
		0,// fireWall
		0,// enchant
		0,// meteor
		0,// fireMastery
		0,// hydra

		0// normalAttack
	};
	int skillCastLength[(int)eSkillType::END] = {
		// iceBolt
		// frozenArmor
		// frostNova
		// iceBlast
		// shiverArmor
		// clacialSpike
		// blizzard
		// chillingArmor
		// frozenOrb
		// coldMastery

		// chargedBolt
		// staticField
		// telekinesis
		// nove
		// lightning
		// chainLightning
		// teleport
		// thunderStorm
		// energyShield
		// lightningMastery

		// fireBolt
		// warmth
		// inferno
		// blaze
		// fireBall
		// fireWall
		// enchant
		// meteor
		// fireMastery
		// hydra

		// normalAttack
	};
}