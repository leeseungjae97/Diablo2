#pragma once

namespace m
{
	enum class eSkillCrashType
	{
		IceCrash1,
		FireCrash1,
		END
	};
	enum class eSkillCastType
	{
		IceCast1,
		IceCast2,
		IceCast3,
		FireCast1,
		END
	};
	std::wstring crashNames[(int)eSkillCrashType::END] = {
		L"iceCrash1",
		L"fireCrash1",
	};
	std::wstring castNames[(int)eSkillCastType::END] = {
		L"iceCast1",
		L"iceCast2",
		L"iceCast3",
		L"fireCast1",
	};
	m::math::Vector2 crashSizes[(int)eSkillCrashType::END] = {
		m::math::Vector2(113.f, 72.f),
		m::math::Vector2(78.f, 70.f),
	};
	int crashLength[(int)eSkillCrashType::END] = {
		6,
		12
	};

	m::math::Vector2 castSizes[(int)eSkillCastType::END] = {
		m::math::Vector2(97.f, 55.f),
		m::math::Vector2(115.f, 123.f),
		m::math::Vector2(127.f, 148.f),
		m::math::Vector2(145.f, 133.f),
	};
	int castLength[(int)eSkillCastType::END] = {
		15,
		15,
		16,
		16,
	};

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
		200.f,// blizzard
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

		15,
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

		m::math::Vector2(252.f, 190.f),
	};
	eSkillCrashType skillCrashTypes[(int)eSkillType::END] = {
		eSkillCrashType::IceCrash1,// iceBolt
		eSkillCrashType::END,// frozenArmor
		eSkillCrashType::END,// frostNova
		eSkillCrashType::END,// iceBlast
		eSkillCrashType::END,// shiverArmor
		eSkillCrashType::END,// clacialSpike
		eSkillCrashType::END,// blizzard
		eSkillCrashType::END,// chillingArmor
		eSkillCrashType::END,// frozenOrb
		eSkillCrashType::END,// coldMastery

		eSkillCrashType::END,// chargedBolt
		eSkillCrashType::END,// staticField
		eSkillCrashType::END,// telekinesis
		eSkillCrashType::END,// nove
		eSkillCrashType::END,// lightning
		eSkillCrashType::END,// chainLightning
		eSkillCrashType::END,// teleport
		eSkillCrashType::END,// thunderStorm
		eSkillCrashType::END,// energyShield
		eSkillCrashType::END,// lightningMastery

		eSkillCrashType::FireCrash1,// fireBolt
		eSkillCrashType::END,// warmth
		eSkillCrashType::END,// inferno
		eSkillCrashType::END,// blaze
		eSkillCrashType::END,// fireBall
		eSkillCrashType::END,// fireWall
		eSkillCrashType::END,// enchant
		eSkillCrashType::END,// meteor
		eSkillCrashType::END,// fireMastery
		eSkillCrashType::END,// hydra

		eSkillCrashType::END,// normalAttack
	};
	eSkillCastType skillCastTypes[(int)eSkillType::END] = {
		eSkillCastType::IceCast1,// iceBolt
		eSkillCastType::END,// frozenArmor
		eSkillCastType::END,// frostNova
		eSkillCastType::IceCast2,// iceBlast
		eSkillCastType::END,// shiverArmor
		eSkillCastType::END,// clacialSpike
		eSkillCastType::IceCast3,// blizzard
		eSkillCastType::END,// chillingArmor
		eSkillCastType::END,// frozenOrb
		eSkillCastType::END,// coldMastery

		eSkillCastType::END,// chargedBolt
		eSkillCastType::END,// staticField
		eSkillCastType::END,// telekinesis
		eSkillCastType::END,// nove
		eSkillCastType::END,// lightning
		eSkillCastType::END,// chainLightning
		eSkillCastType::END,// teleport
		eSkillCastType::END,// thunderStorm
		eSkillCastType::END,// energyShield
		eSkillCastType::END,// lightningMastery

		eSkillCastType::FireCast1,// fireBolt
		eSkillCastType::END,// warmth
		eSkillCastType::END,// inferno
		eSkillCastType::END,// blaze
		eSkillCastType::END,// fireBall
		eSkillCastType::END,// fireWall
		eSkillCastType::END,// enchant
		eSkillCastType::END,// meteor
		eSkillCastType::END,// fireMastery
		eSkillCastType::END,// hydra

		eSkillCastType::END,// normalAttack
	};
	
	enum class eAccessorySkillType {
		Blizzard1,
		Blizzard3,
		END
	};
	std::wstring accessorySkillNames[(int)eAccessorySkillType::END] = {
		L"blizzard1",
		L"blizzard3",
	};
	m::math::Vector2 accessorySkillAnimSize[(int)eAccessorySkillType::END] = {
		Vector2(97.f, 153.f),
		Vector2(59.f, 198.f),

	};
	int accessorySkillAnimLength[(int)eAccessorySkillType::END] = {
		8,
		6,
	};
	eSkillCrashType accessorySkillCrashTypes[(int)eAccessorySkillType::END] = {
		eSkillCrashType::IceCrash1,
		eSkillCrashType::IceCrash1,
	};
}