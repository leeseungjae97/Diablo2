#pragma once

//#include "MoveAbleObjectAnimLookUpTables.h"

namespace m
{

#pragma region Crash
	enum class eCrashType
	{
		Overlay,
		Collide,
		Addiction,
		Stun,
		END,
	};
	enum class eSkillCrashType
	{
		IceCrash1,
		IceCrash2,
		//LightCrash1,
		FireCrash1,
		FireCrash2,
		RedLightningCrash,
		Poison,
		StunAttack,

		END
	};
	std::wstring crashNames[(int)eSkillCrashType::END] = {
	L"iceCrash1",
	L"iceCrash2",
	L"fireCrash1",
	L"fireCrash2",
	L"redLightningCrash",
	L"", // Poison
	L"stun",
	};
	eCrashType crashFunction[(int)eSkillCrashType::END] = {
		eCrashType::Collide,
		eCrashType::Collide,
		eCrashType::Collide,
		eCrashType::Collide,
		eCrashType::Overlay,
		eCrashType::Addiction,
		eCrashType::Stun,
	};
	m::math::Vector2 crashSizes[(int)eSkillCrashType::END] = {
	m::math::Vector2(113.f, 72.f),
	m::math::Vector2(83.f, 110.f),
	m::math::Vector2(78.f, 70.f),
	m::math::Vector2(208.f, 174.f),
	m::math::Vector2(71.f, 88.f),
	m::math::Vector2(0.f, 0.f),
	m::math::Vector2(69.f, 49.f),

	};
	m::math::Vector2 crashCenterPos[(int)eSkillCrashType::END] = {
		m::math::Vector2(0.f, 0.f),
		m::math::Vector2(0.f, 0.f),
		m::math::Vector2(0.f, 0.f),
		m::math::Vector2(0.f, 0.f),
		m::math::Vector2(0.f, 0.f),
		m::math::Vector2(0.f, 0.f),
		m::math::Vector2(0.f, 30.f),

	};
	int crashLength[(int)eSkillCrashType::END] = {
	6,
	16,
	12,
	16,
	20,
	0,
	12,
	};
	bool crashLoop[(int)eSkillCrashType::END] = {
		false,
		false,
		false,
		false,
		false,
		true,
	};
#pragma endregion
#pragma region Cast
	enum class eSkillCastType
	{
		IceCast1,
		IceCast2,
		IceCast3,
		LightCast1,
		FireCast1,
		Teleport,

		AndarielPoisonCast,

		END
	};
	std::wstring castNames[(int)eSkillCastType::END] = {
	L"iceCast1",
	L"iceCast2",
	L"iceCast3",
	L"lightCast1",
	L"fireCast1",
	L"teleport",
	L"andarielSkillOverlay",
	};
	m::math::Vector2 castSizes[(int)eSkillCastType::END] = {
		m::math::Vector2(97.f, 55.f),
		m::math::Vector2(115.f, 123.f),
		m::math::Vector2(127.f, 148.f),
		m::math::Vector2(164.f, 144.f),
		m::math::Vector2(145.f, 133.f),
		m::math::Vector2(136.f, 154.f),
		m::math::Vector2(162.f, 107.f),
	};
	m::math::Vector2 castOffset[(int)eSkillCastType::END] = {
		m::math::Vector2(0.f, 0.f),
		m::math::Vector2(0.f, 0.f),
		m::math::Vector2(0.f, 0.f),
		m::math::Vector2(0.f, 0.f),
		m::math::Vector2(0.f, 0.f),
		m::math::Vector2(8.f, 0.f),
		m::math::Vector2(0.f, 0.f),
	};
	int castLength[(int)eSkillCastType::END] = {
		15,
		15,
		16,
		10,
		16,
		18,
		18,
	};
#pragma endregion
#pragma region Aura
	enum class eAuraType
	{
		HolyFreeze,
		End,
	};
	enum class eAuraFunctionType
	{
	    Slow,
		End,
	};
	std::wstring auraNames[(int)eAuraType::End] = {
    L"holyFreeze",
	};
	m::math::Vector2 auraSizes[(int)eAuraType::End] = {
		Vector2(114.f, 93.f),
	};
	m::math::Vector2 auraCenterPos[(int)eAuraType::End] = {
		Vector2(0.f, 0.f),
	};
	int auraLength[(int)eAuraType::End] = {
		15,
	};
	eAuraFunctionType auraFunction[(int)eAuraType::End] = {
		eAuraFunctionType::Slow,
	};
	float auraFunctionValue[(int)eAuraFunctionType::End][2] = {
		{-200.f, 5.f},
		
	};
#pragma endregion
#pragma region Indicator
	enum class eIndicatorType
	{
		MeteorTargetIndicator,
		End,
	};
	std::wstring indicatorNames[(int)eIndicatorType::End] = {
	L"meteorTargetIndicator",
	};
	m::math::Vector2 indicatorSizes[(int)eIndicatorType::End] = {
		Vector2(112.f, 74.f),
	};
	int indicatorLength[(int)eIndicatorType::End] = {
		17,
	};
#pragma endregion



	enum class ePathSixteenDirection
	{
		LeftDown2,
		LeftUp2,
		RightUp2,
		RightDown2,
		Down,
		Left,
		Up,
		Right,
		LeftDown1,
		LeftDown3,
		LeftUp1,
		LeftUp3,
		RightUp1,
		RightUp3,
		RightDown1,
		RightDown3,
		End
	};
	int pathEightDirections[8] = {
		(int)ePathSixteenDirection::LeftDown2,
		(int)ePathSixteenDirection::LeftUp2,
		(int)ePathSixteenDirection::RightUp2,
		(int)ePathSixteenDirection::RightDown2,
		(int)ePathSixteenDirection::Down,
		(int)ePathSixteenDirection::Left,
		(int)ePathSixteenDirection::Up,
		(int)ePathSixteenDirection::Right,
	};

	int pathPlusSixteenDirections[19] = {
		(int)ePathSixteenDirection::Up,
		(int)ePathSixteenDirection::RightUp1,
		(int)ePathSixteenDirection::RightUp1,
		(int)ePathSixteenDirection::RightUp2,
		(int)ePathSixteenDirection::RightUp2,
		(int)ePathSixteenDirection::RightUp2,
		(int)ePathSixteenDirection::RightUp2,
		(int)ePathSixteenDirection::RightUp3,
		(int)ePathSixteenDirection::Right,
		(int)ePathSixteenDirection::Right,
		(int)ePathSixteenDirection::RightDown1,
		(int)ePathSixteenDirection::RightDown2,
		(int)ePathSixteenDirection::RightDown2,
		(int)ePathSixteenDirection::RightDown2,
		(int)ePathSixteenDirection::RightDown3,
		(int)ePathSixteenDirection::RightDown3,
		(int)ePathSixteenDirection::RightDown3,
		(int)ePathSixteenDirection::Down,
		(int)ePathSixteenDirection::Down,
	};

	int pathMinusSixteenDirections[19] = {
		(int)ePathSixteenDirection::Up,
		(int)ePathSixteenDirection::LeftUp3,
		(int)ePathSixteenDirection::LeftUp3,
		(int)ePathSixteenDirection::LeftUp2,
		(int)ePathSixteenDirection::LeftUp2,
		(int)ePathSixteenDirection::LeftUp2,
		(int)ePathSixteenDirection::LeftUp1,
		(int)ePathSixteenDirection::LeftUp1,
		(int)ePathSixteenDirection::Left,
		(int)ePathSixteenDirection::Left,
		(int)ePathSixteenDirection::LeftDown3,
		(int)ePathSixteenDirection::LeftDown3,
		(int)ePathSixteenDirection::LeftDown2,
		(int)ePathSixteenDirection::LeftDown2,
		(int)ePathSixteenDirection::LeftDown2,
		(int)ePathSixteenDirection::LeftDown1,
		(int)ePathSixteenDirection::LeftDown1,
		(int)ePathSixteenDirection::Down,
		(int)ePathSixteenDirection::Down,
	};

	int pathPlusEightDirections[5] = {
		(int)ePathSixteenDirection::Up,
		(int)ePathSixteenDirection::RightUp2,
		(int)ePathSixteenDirection::Right,
		(int)ePathSixteenDirection::RightDown2,
		(int)ePathSixteenDirection::Down,

	};

	int pathMinusEightDirections[5] = {
		(int)ePathSixteenDirection::Up,
		(int)ePathSixteenDirection::LeftUp2,
		(int)ePathSixteenDirection::Left,
		(int)ePathSixteenDirection::LeftDown2,
		(int)ePathSixteenDirection::Down,
	};

	std::wstring pathSixteenDirectionString[16] = {
			L"left_down_2",
			L"left_up_2",
			L"right_up_2",
			L"right_down_2",
			L"down",
			L"left",
			L"up",
			L"right",
			L"left_down_1",
			L"left_down_3",
			L"left_up_1",
			L"left_up_3",
			L"right_up_1",
			L"right_up_3",
			L"right_down_1",
			L"right_down_3",
	};

	float skillSpeed[(int)eSkillType::END] = {
		300.f,// iceBolt
		0.f,// frozenArmor
		1000.f,// frostNova
		0.f,// iceBlast
		0.f,// shiverArmor
		0.f,// clacialSpike
		200.f,// blizzard
		0.f,// chillingArmor
		200.f,// frozenOrb
		0.f,// coldMastery
		//
		0.f,// chargedBolt
		0.f,// staticField
		0.f,// telekinesis
		1000.f,// nova
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
		300.f,// meteor
		0.f,// fireMastery
		0.f,// hydra
		//
		0.f,// normalAttack

		300.f, // diablo lightning
		500.f, // diablo firenova
		300.f, // diablo firestorm

		300.f, // andariel poison
		0,
	};
	int skillAnimLength[(int)eSkillType::END] = {
		6, // iceBolt
		0, // frozenArmor
		14, // frostNova
		0, // iceBlast
		0, // shiverArmor
		0, // clacialSpike
		0, // blizzard
		0, // chillingArmor
		16, // frozenOrb
		0, // coldMastery
		//
		5, // chargedBolt
		0, // staticField
		0, // telekinesis
		13, // nova
		0, // lightning
		0, // chainLightning
		18, // teleport
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
		12, // meteor
		0, // fireMastery
		0, // hydra
		//
		0, // normalAttack

		15,
		8,
		8,

		24,
		0,
	};
	int skillLoops[(int)eSkillType::END] = {
		true, // iceBolt
		true, // frozenArmor
		false, // frostNova
		true, // iceBlast
		true, // shiverArmor
		true, // clacialSpike
		true, // blizzard
		true, // chillingArmor
		true, // frozenOrb
		true, // coldMastery
		//
		true, // chargedBolt
		true, // staticField
		true, // telekinesis
		false, // nova
		true, // lightning
		true, // chainLightning
		false, // teleport
		true, // thunderStorm
		true, // energyShield
		true, // lightningMastery
		//
		true, // fireBolt
		true, // warmth
		true, // inferno
		true, // blaze
		true, // fireBall
		true, // fireWall
		true, // enchant
		true, // meteor
		true, // fireMastery
		true, // hydra
		//
		false, // normalAttack

		true,
		true,
		true,

		true,
		false,
	};

    int skillAnimDirections[(int)eSkillType::END] = {
		16, // iceBolt
		16, // frozenArmor
		16, // frostNova
		16, // iceBlast
		16, // shiverArmor
		16, // clacialSpike
		16, // blizzard
		16, // chillingArmor
		16, // frozenOrb
		16, // coldMastery
		//
		16, // chargedBolt
		16, // staticField
		16, // telekinesis
		16, // nova
		16, // lightning
		16, // chainLightning
		16, // teleport
		16, // thunderStorm
		16, // energyShield
		16, // lightningMastery
		//
		16, // fireBolt
		16, // warmth
		16, // inferno
		16, // blaze
		16, // fireBall
		16, // fireWall
		16, // enchant
		16, // meteor
		16, // fireMastery
		16, // hydra
		//
		0, // normalAttack

		8,
		0,
		16,

		16,
		16,
	};
	m::math::Vector2 skillSizes[(int)eSkillType::END] = {
		m::math::Vector2(92.f, 55.f),// iceBolt,
		m::math::Vector2(0.f, 0.f),// frozenArmor,
		m::math::Vector2(118.f, 69.f),// frostNova,
		m::math::Vector2(0.f, 0.f),// iceBlast,
		m::math::Vector2(0.f, 0.f),// shiverArmor,
		m::math::Vector2(0.f, 0.f),// clacialSpike,
		m::math::Vector2(0.f, 0.f),// blizzard,
		m::math::Vector2(0.f, 0.f),// chillingArmor,
		m::math::Vector2(54.f, 53.f),// frozenOrb,
		m::math::Vector2(0.f, 0.f),// coldMastery,

		m::math::Vector2(0.f, 0.f),// chargedBolt,
		m::math::Vector2(0.f, 0.f),// staticField,
		m::math::Vector2(0.f, 0.f),// telekinesis,
		m::math::Vector2(70.f, 48.f),// nova,
		m::math::Vector2(0.f, 0.f),// lightning,
		m::math::Vector2(0.f, 0.f),// chainLightning,
		m::math::Vector2(136.f, 154.f),// teleport,
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
		m::math::Vector2(77.f, 125.f),// meteor,
		m::math::Vector2(0.f, 0.f),// fireMastery,
		m::math::Vector2(0.f, 0.f),// hydra,

		m::math::Vector2(0.f),// normalAttack,

		m::math::Vector2(252.f, 190.f),
		m::math::Vector2(66.f, 167.f),
		m::math::Vector2(66.f, 167.f),

		m::math::Vector2(65.f, 65.f),
		m::math::Vector2(0.f, 0.f),
	};
	eSkillCrashType skillCrashTypes[(int)eSkillType::END] = {
		eSkillCrashType::IceCrash2,// iceBolt
		eSkillCrashType::END,// frozenArmor
		eSkillCrashType::IceCrash2,// frostNova
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
		eSkillCrashType::END,// nova
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
		eSkillCrashType::FireCrash2,// meteor
		eSkillCrashType::END,// fireMastery
		eSkillCrashType::END,// hydra

		eSkillCrashType::END,// normalAttack

		//Monster
		eSkillCrashType::RedLightningCrash,
		eSkillCrashType::END,
		eSkillCrashType::END,

		eSkillCrashType::Poison,
		eSkillCrashType::StunAttack,
	};
	eSkillCastType skillCastTypes[(int)eSkillType::END] = {
		eSkillCastType::IceCast1,// iceBolt
		eSkillCastType::END,// frozenArmor
		eSkillCastType::IceCast3,// frostNova
		eSkillCastType::IceCast2,// iceBlast
		eSkillCastType::END,// shiverArmor
		eSkillCastType::END,// clacialSpike
		eSkillCastType::IceCast3,// blizzard
		eSkillCastType::END,// chillingArmor
		eSkillCastType::IceCast3,// frozenOrb
		eSkillCastType::END,// coldMastery

		eSkillCastType::END,// chargedBolt
		eSkillCastType::END,// staticField
		eSkillCastType::END,// telekinesis
		eSkillCastType::LightCast1,// nova
		eSkillCastType::END,// lightning
		eSkillCastType::END,// chainLightning
		eSkillCastType::Teleport,// teleport
		eSkillCastType::END,// thunderStorm
		eSkillCastType::END,// energyShield
		eSkillCastType::END,// lightningMastery

		eSkillCastType::FireCast1,// fireBolt
		eSkillCastType::END,// warmth
		eSkillCastType::END,// inferno
		eSkillCastType::END,// blaze
		eSkillCastType::END,// fireBall
		eSkillCastType::FireCast1,// fireWall
		eSkillCastType::END,// enchant
		eSkillCastType::FireCast1,// meteor
		eSkillCastType::END,// fireMastery
		eSkillCastType::END,// hydra

		eSkillCastType::END,// normalAttack

		eSkillCastType::END,// diablo lightning
		eSkillCastType::END,// diablo firenova
		eSkillCastType::END,// diablo firestorm

		eSkillCastType::AndarielPoisonCast,// andariel poison
		eSkillCastType::END,// duriel stun attack
	};

	enum class eAccessorySkillType
	{
		Blizzard1,
		Blizzard3,
		MeteorHead,
		END
	};
	std::wstring accessorySkillNames[(int)eAccessorySkillType::END] = {
		L"blizzard1",
		L"blizzard3",
		L"meteorHead",

	};
	m::math::Vector2 accessorySkillAnimSize[(int)eAccessorySkillType::END] = {
		Vector2(97.f, 153.f),
		Vector2(59.f, 198.f),
		Vector2(22.f, 22.f),

	};
	int accessorySkillAnimLength[(int)eAccessorySkillType::END] = {
		8,
		6,
		12,
	};
	eSkillCrashType accessorySkillCrashTypes[(int)eAccessorySkillType::END] = {
		eSkillCrashType::IceCrash1,
		eSkillCrashType::IceCrash1,
		eSkillCrashType::END,
	};
}