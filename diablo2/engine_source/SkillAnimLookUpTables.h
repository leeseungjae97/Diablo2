#pragma once

#include "SkillLookUpTables.h"

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
		IceCrash3,
		FireCrash1,
		FireCrash2,
		LightCrash1,
		IceCrash1Overlay,
		IceCrash2Overlay,
		FireCrash1Overlay,
		FireCrash2Overlay,
		RedLightningCrash,
		Poison,
		StunAttack,

		END
	};
	std::wstring crashNames[(int)eSkillCrashType::END] = {
	L"iceCrash1",
	L"iceCrash2",
	L"iceCrash3",
	L"fireCrash1",
	L"fireCrash2",
	L"lightCrash1",
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
		eCrashType::Collide,
		eCrashType::Overlay,
		eCrashType::Overlay,
		eCrashType::Overlay,
		eCrashType::Overlay,
		eCrashType::Overlay,
		eCrashType::Overlay,
		eCrashType::Addiction,
		eCrashType::Stun,
	};
	m::math::Vector2 crashSizes[(int)eSkillCrashType::END] = {
	m::math::Vector2(113.f, 72.f),
	m::math::Vector2(83.f, 110.f),
	m::math::Vector2(143.f, 107.f),
	m::math::Vector2(78.f, 70.f),
	m::math::Vector2(208.f, 174.f),
	m::math::Vector2(65.f, 71.f),
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
	15,
	12,
	16,
	20,
	6,
	16,
	12,
	16,
	20,
	0,
	12,
	};
	int crashProgress[(int)eSkillCrashType::END] = {
	0,  // IceCrash1
	0,  // IceCrash2
	0,  // IceCrash3
	0,  // FireCrash1
	3,  // FireCrash2
	0,
	0,  // IceCrash1Overlay
	0,  // IceCrash2Overlay
	0,  // FireCrash1Overlay
	0,  // FireCrash2Overlay
	0,  // RedLightningCrash
	0,  // Poison
	0,  // StunAttack
	};
	bool crashLoop[(int)eSkillCrashType::END] = {
		false,
		false,
		false,
		false,
		false,
		false,
		false,
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
		LightCast2,
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
	L"lightCast2Front",
	L"fireCast1",
	L"teleport",
	L"andarielSkillOverlay",
	};
	m::math::Vector2 castSizes[(int)eSkillCastType::END] = {
		m::math::Vector2(97.f, 55.f),
		m::math::Vector2(115.f, 123.f),
		m::math::Vector2(127.f, 148.f),
		m::math::Vector2(164.f, 144.f),
		m::math::Vector2(147.f, 190.f),
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
		m::math::Vector2(0.f, 0.f),
		m::math::Vector2(8.f, 0.f),
		m::math::Vector2(0.f, 0.f),
	};
	m::math::Vector2 castCenterPos[(int)eSkillCastType::END] = {
	m::math::Vector2(0.f, 0.f),
	m::math::Vector2(0.f, 0.f),
	m::math::Vector2(0.f, 0.f),
	m::math::Vector2(0.f, 0.f),
	m::math::Vector2(0.f, 40.f),
	m::math::Vector2(0.f, 0.f),
	m::math::Vector2(8.f, 0.f),
	m::math::Vector2(0.f, 0.f),
	};
	int castLength[(int)eSkillCastType::END] = {
		15,
		15,
		16,
		10,
		10,
		16,
		18,
		18,
	};
	bool castBack[(int)eSkillCastType::END] = {
		false,
		false,
		false,
		false,
		true,
		false,
		false,
		false,
	};
	std::wstring backCastNames[(int)eSkillCastType::END] = {
    L"",
    L"",
    L"",
    L"",
    L"lightCast2Back",
    L"",
    L"",
    L"",
	};
	m::math::Vector2 backCastSizes[(int)eSkillCastType::END] = {
		m::math::Vector2(0.f, 0.f),
		m::math::Vector2(0.f, 0.f),
		m::math::Vector2(0.f, 0.f),
		m::math::Vector2(0.f, 0.f),
		m::math::Vector2(101.f, 105.f),
		m::math::Vector2(0.f, 0.f),
		m::math::Vector2(0.f, 0.f),
		m::math::Vector2(0.f, 0.f),
	};
	m::math::Vector2 backCastOffset[(int)eSkillCastType::END] = {
		m::math::Vector2(0.f, 0.f),
		m::math::Vector2(0.f, 0.f),
		m::math::Vector2(0.f, 0.f),
		m::math::Vector2(0.f, 0.f),
		m::math::Vector2(0.f, 0.f),
		m::math::Vector2(0.f, 0.f),
		m::math::Vector2(0.f, 0.f),
		m::math::Vector2(8.f, 0.f),
	};
	m::math::Vector2 backCastCenterPos[(int)eSkillCastType::END] = {
m::math::Vector2(0.f, 0.f),
m::math::Vector2(0.f, 0.f),
m::math::Vector2(0.f, 0.f),
m::math::Vector2(0.f, 0.f),
m::math::Vector2(0.f, 40.f),
m::math::Vector2(0.f, 0.f),
m::math::Vector2(8.f, 0.f),
m::math::Vector2(0.f, 0.f),
	};
	int backCastLength[(int)eSkillCastType::END] = {
		0,
		0,
		0,
		0,
		10,
		0,
		0,
		0,
	};
#pragma endregion
#pragma region Aura
	enum class eAuraType
	{
		HolyFreeze,
		ThunderStorm,
		End,
	};
	enum class eAuraFunctionType
	{
		Slow,
		TargetDamage,
		End,
	};
	std::wstring auraNames[(int)eAuraType::End] = {
	L"holyFreeze",
	L"thunderStormLoop",
	};
	m::math::Vector2 auraSizes[(int)eAuraType::End] = {
		Vector2(114.f, 93.f),
		Vector2(81.f, 60.f),
	};
	m::math::Vector2 auraCenterPos[(int)eAuraType::End] = {
		Vector2(0.f, 0.f),
		Vector2(0.f, -10.f),
	};
	int auraLength[(int)eAuraType::End] = {
		15,
		19,
	};
	eAuraFunctionType auraFunction[(int)eAuraType::End] = {
		eAuraFunctionType::Slow,
		eAuraFunctionType::TargetDamage,
	};
	float auraFunctionValue[(int)eAuraFunctionType::End][2] = {
		{-200.f, 5.f},
		{1.f, 100.f},
	};
	std::wstring auraStartNames[(int)eAuraType::End] = {
	L"",
	L"thunderStormCast",
	};
	m::math::Vector3 auraColliderSizes[(int)eAuraType::End] = {
		Vector3(300.f, 150.f, 1.f),
		Vector3(1200.f, 600.f, 1.f),
	};
	m::math::Vector2 auraStartSizes[(int)eAuraType::End] = {
	Vector2(0, 0),
	Vector2(79.f, 52.f),
	};
	m::math::Vector2 auraStartCenterPos[(int)eAuraType::End] = {
		Vector2(0.f, 0.f),
		Vector2(0.f, 0.f),
	};
	int auraStartLength[(int)eAuraType::End] = {
		0,
		10,
	};
	eSkillType auraAddSkill[(int)eAuraType::End] = {
		eSkillType::END,
		eSkillType::thunderStorm,
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
	eAuraType skillAuraTypes[(int)eSkillType::END] = {
		eAuraType::End,// iceBolt
		eAuraType::End,// frozenArmor
		eAuraType::End,// frostNova
		eAuraType::End,// iceBlast
		eAuraType::End,// shiverArmor
		eAuraType::End,// clacialSpike
		eAuraType::End,// blizzard
		eAuraType::End,// chillingArmor
		eAuraType::End,// frozenOrb
		eAuraType::End,// coldMastery

		eAuraType::End,//chargedBolt
		eAuraType::End,//staticField
		eAuraType::End,//telekinesis
		eAuraType::End,//nova
		eAuraType::End,//lightning
		eAuraType::End,//chainLightning
		eAuraType::End,//teleport
		eAuraType::ThunderStorm,//thunderStorm
		eAuraType::End,//energyShield
		eAuraType::End,//lightningMastery

		eAuraType::End,//fireBolt
		eAuraType::End,//warmth
		eAuraType::End,//inferno
		eAuraType::End,//blaze
		eAuraType::End,//fireBall
		eAuraType::End,//fireWall
		eAuraType::End,//enchant
		eAuraType::End,//meteor
		eAuraType::End,//fireMastery
		eAuraType::End,//hydra

		eAuraType::End,//normalAttack

		eAuraType::End,//DiabloLightning
		eAuraType::End,//DiabloFireNova
		eAuraType::End,//DiabloFireStorm

		eAuraType::End,// AndarielPoisonAttack
		eAuraType::End,// DurielStunAttack
	};
	float skillSpeed[(int)eSkillType::END] = {
		300.f,// iceBolt
		0.f,// frozenArmor
		1000.f,// frostNova
		300.f,// iceBlast
		0.f,// shiverArmor
		300.f,// clacialSpike
		200.f,// blizzard
		0.f,// chillingArmor
		200.f,// frozenOrb
		0.f,// coldMastery
		//
		300.f,// chargedBolt
		0.f,// staticField
		0.f,// telekinesis
		1000.f,// nova
		500.f,// lightning
		800.f,// chainLightning
		0.f,// teleport
		1000.f,// thunderStorm
		0.f,// energyShield
		0.f,// lightningMastery
		//
		300.f,// fireBolt
		0.f,// warmth
		300.f,// inferno
		0.f,// blaze
		300.f,// fireBall
		300.f,// fireWall
		0.f,// enchant
		300.f,// meteor
		0.f,// fireMastery
		0.f,// hydra
		//
		0.f,// normalAttack

		300.f, // diablo lightning
		1000.f, // diablo firenova
		300.f, // diablo firestorm

		300.f, // andariel poison
		0,
	};
	int skillAnimLength[(int)eSkillType::END] = {
		6, // iceBolt
		0, // frozenArmor
		14, // frostNova
		5, // iceBlast
		0, // shiverArmor
		6, // clacialSpike
		0, // blizzard
		0, // chillingArmor
		16, // frozenOrb
		0, // coldMastery
		//
		10, // chargedBolt
		0, // staticField
		0, // telekinesis
		13, // nova
		8, // lightning
		8, // chainLightning
		18, // teleport
		8, // thunderStorm
		0, // energyShield
		0, // lightningMastery
		//
		5, // fireBolt
		0, // warmth
		0, // inferno
		8, // blaze
		5, // fireBall
		8, // fireWall
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
	bool skillLoops[(int)eSkillType::END] = {
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
		false, // inferno
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

	bool skillHitDestory[(int)eSkillType::END] = {
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
		false, // chargedBolt
		true, // staticField
		true, // telekinesis
		false, // nova
		false, // lightning
		true, // chainLightning
		false, // teleport
		true, // thunderStorm
		true, // energyShield
		true, // lightningMastery
		//
		true, // fireBolt
		true, // warmth
		false, // inferno
		false, // blaze
		true, // fireBall
		false, // fireWall
		true, // enchant
		true, // meteor
		true, // fireMastery
		true, // hydra
		//
		false, // normalAttack

		false,
		false,
		false,

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
		0, // thunderStorm
		16, // energyShield
		16, // lightningMastery
		//
		16, // fireBolt
		16, // warmth
		0, // inferno
		0, // blaze
		16, // fireBall
		0, // fireWall
		16, // enchant
		16, // meteor
		16, // fireMastery
		16, // hydra
		//
		0, // normalAttack

		8,
		0,
		0,

		16,
		16,
	};
	m::math::Vector2 skillSizes[(int)eSkillType::END] = {
		m::math::Vector2(92.f, 55.f),// iceBolt,
		m::math::Vector2(0.f, 0.f),// frozenArmor,
		m::math::Vector2(118.f, 69.f),// frostNova,
		m::math::Vector2(169.f, 94.f),// iceBlast,
		m::math::Vector2(0.f, 0.f),// shiverArmor,
		m::math::Vector2(180.f, 110.f),// clacialSpike,
		m::math::Vector2(0.f, 0.f),// blizzard,
		m::math::Vector2(0.f, 0.f),// chillingArmor,
		m::math::Vector2(54.f, 53.f),// frozenOrb,
		m::math::Vector2(0.f, 0.f),// coldMastery,

		m::math::Vector2(85.f, 78.f),// chargedBolt,
		m::math::Vector2(0.f, 0.f),// staticField,
		m::math::Vector2(0.f, 0.f),// telekinesis,
		m::math::Vector2(70.f, 48.f),// nova,
		m::math::Vector2(148.f, 106.f),// lightning,
		m::math::Vector2(148.f, 106.f),// chainLightning,
		m::math::Vector2(136.f, 154.f),// teleport,
		m::math::Vector2(36.f, 113.f),// thunderStorm,
		m::math::Vector2(0.f, 0.f),// energyShield,
		m::math::Vector2(0.f, 0.f),// lightningMastery,

		m::math::Vector2(116.f, 66.f),// fireBolt,
		m::math::Vector2(0.f, 0.f),// warmth,
		m::math::Vector2(0.f, 0.f),// inferno,
		m::math::Vector2(66.f, 167.f),// blaze,
		m::math::Vector2(146.f, 79.f),// fireBall,
		m::math::Vector2(66.f, 167.f),// fireWall,
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
	m::math::Vector2 skillOffsets[(int)eSkillType::END] = {
		m::math::Vector2(0.f, 0.f),// iceBolt,
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
		m::math::Vector2(0.f, 0.f),// nova,
		m::math::Vector2(0.f, 0.f),// lightning,
		m::math::Vector2(0.f, 0.f),// chainLightning,
		m::math::Vector2(0.f, 0.f),// teleport,
		m::math::Vector2(0.f, 0.f),// thunderStorm,
		m::math::Vector2(0.f, 0.f),// energyShield,
		m::math::Vector2(0.f, 0.f),// lightningMastery,

		m::math::Vector2(0.f, 0.f),// fireBolt,
		m::math::Vector2(0.f, 0.f),// warmth,
		m::math::Vector2(0.f, 0.f),// inferno,
		m::math::Vector2(0.f, 0.f),// blaze,
		m::math::Vector2(0.f, 0.f),// fireBall,
		m::math::Vector2(0.f, 0.f),// fireWall,
		m::math::Vector2(0.f, 0.f),// enchant,
		m::math::Vector2(0.f,0.f),// meteor,
		m::math::Vector2(0.f, 0.f),// fireMastery,
		m::math::Vector2(0.f, 0.f),// hydra,

		m::math::Vector2(0.f),// normalAttack,

		m::math::Vector2(0.f, 0.f),
		m::math::Vector2(0.f, 0.f),
		m::math::Vector2(0.f, 0.f),

		m::math::Vector2(0.f, 0.f),
		m::math::Vector2(0.f, 0.f),
	};
	eSkillCrashType skillCrashTypes[(int)eSkillType::END] = {
		eSkillCrashType::IceCrash2,// iceBolt
		eSkillCrashType::END,// frozenArmor
		eSkillCrashType::IceCrash2Overlay,// frostNova
		eSkillCrashType::IceCrash3,// iceBlast
		eSkillCrashType::END,// shiverArmor
		eSkillCrashType::IceCrash3,// clacialSpike
		eSkillCrashType::END,// blizzard
		eSkillCrashType::END,// chillingArmor
		eSkillCrashType::END,// frozenOrb
		eSkillCrashType::END,// coldMastery

		eSkillCrashType::LightCrash1,// chargedBolt
		eSkillCrashType::LightCrash1,// staticField
		eSkillCrashType::END,// telekinesis
		eSkillCrashType::END,// nova
		eSkillCrashType::END,// lightning
		eSkillCrashType::LightCrash1,// chainLightning
		eSkillCrashType::END,// teleport
		eSkillCrashType::LightCrash1,// thunderStorm
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
		eSkillCastType::IceCast3,// frozenArmor
		eSkillCastType::IceCast3,// frostNova
		eSkillCastType::IceCast2,// iceBlast
		eSkillCastType::IceCast3,// shiverArmor
		eSkillCastType::IceCast2,// clacialSpike
		eSkillCastType::IceCast3,// blizzard
		eSkillCastType::IceCast3,// chillingArmor
		eSkillCastType::IceCast3,// frozenOrb
		eSkillCastType::IceCast3,// coldMastery

		eSkillCastType::LightCast1,// chargedBolt
		eSkillCastType::LightCast1,// staticField
		eSkillCastType::LightCast2,// telekinesis
		eSkillCastType::LightCast1,// nova
		eSkillCastType::LightCast1,// lightning
		eSkillCastType::LightCast1,// chainLightning
		eSkillCastType::Teleport,// teleport
		eSkillCastType::LightCast2,// thunderStorm
		eSkillCastType::LightCast1,// energyShield
		eSkillCastType::LightCast1,// lightningMastery

		eSkillCastType::FireCast1,// fireBolt
		eSkillCastType::FireCast1,// warmth
		eSkillCastType::FireCast1,// inferno
		eSkillCastType::FireCast1,// blaze
		eSkillCastType::FireCast1,// fireBall
		eSkillCastType::FireCast1,// fireWall
		eSkillCastType::FireCast1,// enchant
		eSkillCastType::FireCast1,// meteor
		eSkillCastType::FireCast1,// fireMastery
		eSkillCastType::FireCast1,// hydra

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