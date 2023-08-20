#pragma once
#include "mMath.h"
#include "SkillLookUpTables.h"

namespace m
{
	enum class eSorceressAnimationType
	{
		Attack1,
		Attack2,
		Block,
		GetHit,
		Kick,
		Natural,
		Run,
		Special1,
		SpecialCast,
		TownNatural,
		TownWalk,
		Walk,
		Dead,
		End,
	};
	std::wstring sorceressAnimationString[(UINT)eSorceressAnimationType::End] = {
		L"sorceressAttack1_anim",     
		L"sorceressAttack2_anim", 
		L"sorceressBlock_anim", 
		L"sorceressGetHit_anim", 
		L"sorceressKick_anim", 
		L"sorceressNatural_anim", 
		L"sorceressRun_anim", 
		L"sorceressSpecial1_anim", 
		L"sorceressSpecialCast_anim", 
		L"sorceressTownNatural_anim", 
		L"sorceressTownWalk_anim", 
		L"sorceressWalk_anim", 
		L"sorceressDead_anim", 
	};
	enum class eCharacterDirection
	{
		Down,
		LeftDown1,
		LeftDown2,
		LeftDown3,
		Left,
		LeftUp1,
		LeftUp2,
		LeftUp3,
		Up,
		RightUp1,
		RightUp2,
		RightUp3,
		Right,
		RightDown1,
		RightDown2,
		RightDown3,
		End
	};
	enum class eEightDirection
	{
		Down,
		LeftDown,
		Left,
		LeftUp,
		Up,
		RightUp,
		Right,
		RightDown,
		End
	};
	std::wstring characterDirectionString[(UINT)eCharacterDirection::End] = {
		L"down",
		L"left_down_1",
		L"left_down_2",
		L"left_down_3",
		L"left",
		L"left_up_1",
		L"left_up_2",
		L"left_up_3",
		L"up",
		L"right_up_1",
		L"right_up_2",
		L"right_up_3",
		L"right",
		L"right_down_1",
		L"right_down_2",
		L"right_down_3",
	};
	std::wstring monsterDirectionString[(UINT)eCharacterDirection::End] = {
		L"down",
		L"left_down",
		L"left",
		L"left_up",
		L"up",
		L"right_up",
		L"right",
		L"right_down"
	};
	math::Vector2 sorceressAnimationSizes[(UINT)eSorceressAnimationType::End] = {
		math::Vector2(2500.f / 20.f, 1263.f / 16.f),		// Attack1
		math::Vector2(2400.f / 20.f, 1471.f / 16.f),		// Attack2
		math::Vector2(329.f / 5.f, 1167.f / 16.f),		// Block
		math::Vector2(528.f / 8.f, 1167.f / 16.f),		// GetHit
		math::Vector2(1248.f / 12.f, 1247.f / 16.f),		// Kick
		math::Vector2(528.f / 8.f, 1151.f / 16.f),		// Natural
		math::Vector2(488.f / 8.f, 1215.f / 16.f),		// Run
		math::Vector2(1246.f / 14.f, 1467.f / 16.f),		// Special1
		math::Vector2(1358.f / 14.f , 1471.f / 16.f),	// SpecialCast
		math::Vector2(669.f / 8.f, 1165.f / 16.f),		// TownNatural
		math::Vector2(384.f / 8.f, 1199.f / 16.f),		// TownWalk
		math::Vector2(480.f / 8.f, 1215.f / 16.f),		// Walk
		math::Vector2(192.f, 1664.f / 16.f),				// Dead
	};
	int sorceressAnimationLength[(UINT)eSorceressAnimationType::End] = {
		20,
		20,
		5,
		8,
		12,
		8,
		8,
		14,
		14,
		8,
		8,
		8,
		1,
	};
	//enum class eCharacterDirection
	//{
	//	Down,
	//	LeftDown1,
	//	LeftDown2,
	//	LeftDown3,
	//	Left,
	//	LeftUp1,
	//	LeftUp2,
	//	LeftUp3,
	//	Up,
	//	RightUp1,
	//	RightUp2,
	//	RightUp3,
	//	Right,
	//	RightDown1,
	//	RightDown2,
	//	RightDown3,
	//	End
	//};
	//enum class eEightDirection
	//{
	//	Down,
	//	LeftDown,
	//	Left,
	//	LeftUp,
	//	Up,
	//	RightUp,
	//	Right,
	//	RightDown,
	//	End
	//};
	eCharacterDirection plusCharacterDirections[((int)eCharacterDirection::End / 2) + 1] = {
		eCharacterDirection::RightUp1,
		eCharacterDirection::RightUp2,
		eCharacterDirection::RightUp3,
		eCharacterDirection::Right,
		eCharacterDirection::RightDown1,
		eCharacterDirection::RightDown2,
		eCharacterDirection::RightDown3,
		eCharacterDirection::Down
	};
	eCharacterDirection minusCharacterDirections[((int)eCharacterDirection::End / 2) + 1] = {
		eCharacterDirection::Up,
		eCharacterDirection::LeftUp3,
		eCharacterDirection::LeftUp2,
		eCharacterDirection::LeftUp1,
		eCharacterDirection::Left,
		eCharacterDirection::LeftDown3,
		eCharacterDirection::LeftDown2,
		eCharacterDirection::LeftDown1,
		eCharacterDirection::Down,
	};
	eEightDirection plusEightDirection[((int)eEightDirection::End) + 1] = {
		eEightDirection::RightUp,
		eEightDirection::Right,
		eEightDirection::RightDown,
		eEightDirection::Down,
	};
	eEightDirection minusEightDirection[((int)eEightDirection::End) + 1] = {
		eEightDirection::Up,
		eEightDirection::LeftUp,
		eEightDirection::Left,
		eEightDirection::LeftDown,
		eEightDirection::Down,
	};

	enum class eMonsterType
	{
		Diablo,
		End,
	};
	enum class eMonsterClass
	{
		Boss,
		Normal,
	};
	eMonsterClass monsterClasses[(int)eMonsterType::End] = {
		eMonsterClass::Boss,

	};
	struct MonsterData
	{
		MonsterData(){}
		~MonsterData(){}
		enum class eAnimationType {};
		std::wstring textureString[5] = {};
		std::wstring animationString[5] = {};
		math::Vector2 animationOffset[5] = {};
		m::math::Vector2 animationSizes[5] = {};
		float animationDuration[5] = {};
		int animationLength[5] = {};
		int animStartIndex[5] = {};
		int animEndIndex[5] = {};
		int animProgressStartIndex[5] = {};

		float fSpeed = 100.f;
		float fAttackDelay = 1.5f;
		float hp = 100;
		float hpCapacity = hp;
		eSkillType mSpecialCastSkillType = eSkillType::END;
		int mSpecialCastSkillCount = 0;
		eMonsterType mMonsterType = eMonsterType::End;
		eMonsterClass mClass = eMonsterClass::Normal;
	};
	struct MDDiablo : public MonsterData
	{
		MDDiablo() {}
		~MDDiablo() {}

		float fSpeed = 200.f;
		float fAttackDelay = 2.5f;
		float hp = 100;
		float hpCapacity = hp;
		eSkillType mSpecialCastSkillType = eSkillType::DiabloLightning;
		int mSpecialCastSkillCount = 20;
		eMonsterType mMonsterType = eMonsterType::Diablo;
		eMonsterClass mClass = eMonsterClass::Boss;

		enum class eAnimationType
		{
			Attack1,
			Attack2,
			Block,
			Hit,
			Natural,
			Run,
			Walk,
			SpecialCast,
			Special1,
			Special2,
			Special3,
			Special4,
			Dead,
			End,
		};
		std::wstring textureString[(UINT)eAnimationType::End] = {
			L"diabloAttack1",
			L"diabloAttack2",
			L"diabloBlock",
			L"diabloHit",
			L"diabloNatural",
			L"diabloRun",
			L"diabloWalk",
			L"diabloSpecial_cast",
			L"diabloSpecial1",
			L"diabloSpecial2",
			L"diabloSpecial3",
			L"diabloSpecial4",
			L"diabloDead",
		};
		std::wstring animationString[(UINT)eAnimationType::End] = {
			L"diabloAttack1_anim@",
			L"diabloAttack2_anim@",
			L"diabloBlock_anim@",
			L"diabloHit_anim@",
			L"diabloNatural_anim@",
			L"diabloRun_anim@",
			L"diabloWalk_anim@",
			L"diabloSpecialCast_anim@",
			L"diabloSpecial1_anim@",
			L"diabloSpecial2_anim@",
			L"diabloSpecial3_anim@",
			L"diabloSpecial4_anim@",
			L"diabloDead@",
		};
		math::Vector2 animationOffset[(UINT)eAnimationType::End] = {
			math::Vector2(0.f, 0.f), // Attack1
			math::Vector2(0.f, 0.f),	// Attack2
			math::Vector2(0.f, 0.f),	// Block
			math::Vector2(0.f, 0.f),	// Hit
			math::Vector2(0.f, 0.f),	// Natural
			math::Vector2(0.f, 15.f),	// Run
			math::Vector2(0.f, 0.f),	// Walk
			math::Vector2(0.f, 0.f),	// SpecialCast
			math::Vector2(0.f, 0.f),	// Special1
			math::Vector2(0.f, 0.f),	// Special2
			math::Vector2(0.f, 0.f),	// Special3
			math::Vector2(0.f, 0.f),	// Special4
			math::Vector2(0.f, 0.f),	// Dead
		};
		math::Vector2 animationSizes[(UINT)eAnimationType::End] = {
			math::Vector2(4960.f / 16.f, 1791.f / 8.f),	// Attack1
			math::Vector2(5760.f / 20.f, 2295.f / 8.f),	// Attack2
			math::Vector2(2655.f / 9.f, 1551.f / 8.f),	// Block
			math::Vector2(1853.f / 6.f, 1767.f / 8.f),	// Hit
			math::Vector2(3156.f / 12.f, 1695.f / 8.f),	// Natural
			math::Vector2(6798.f / 22.f, 1991.f / 8.f),	// Run
			math::Vector2(3516.f / 14.f, 1503.f / 8.f),	// Walk
			math::Vector2(4522.f / 17.f , 2055.f / 8.f),	// SpecialCast
			math::Vector2(4986.f / 18.f , 1631.f / 8.f),	// Special1
			math::Vector2(4608.f / 16.f , 1895.f / 8.f),	// Special2
			math::Vector2(4979.f / 16.f , 2183.f / 8.f),	// Special3
			math::Vector2(4605.f / 16.f , 1615.f / 8.f),	// Special4
			math::Vector2(169.f, 147.f),					// Dead
		};
		float animationDuration[(UINT)eAnimationType::End] = {
			0.05f,   // Attack1
			0.05f,	// Attack2
			0.05f,	// Block
			0.05f,	// Hit
			0.05f,	// Natural
			0.05f,	// Run
			0.05f,	// Walk
			0.05f,	// SpecialCast
			0.05f,	// Special1
			0.05f,	// Special2
			0.05f,	// Special3
			0.05f,	// Special4
			0.05f,	// Dead
		};
		int animationLength[(UINT)eAnimationType::End] = {
			16,// Attack1
			16,// Attack2
			9, // Block
			6, // Hit
			12,// Natural
			13, // Run
			12, // Walk
			17,// SpecialCast
			18,// Special1
			16, // Special2
			16, // Special3
			16	, // Special4
			1, // Dead
		};
		int animStartIndex[(UINT)eAnimationType::End] = {
			0,// Attack1
			0,// Attack2
			0, // Block
			0, // Hit
			0,// Natural
			6, // Run
			0, // Walk
			11,// SpecialCast
			0,// Special1
			0, // Special2
			0, // Special3
			0, // Special4
			0, // Dead
		};
		int animEndIndex[(UINT)eAnimationType::End] = {
			0,// Attack1
			0,// Attack2
			0, // Block
			0, // Hit
			0,// Natural
			0, // Run
			0, // Walk
			13,// SpecialCast
			0,// Special1
			0, // Special2
			0, // Special3
			0, // Special4
			0, // Dead
		};
		int animProgressStartIndex[(UINT)eAnimationType::End] = {
			10,// Attack1
			0, // Attack2
			0, // Block
			0, // Hit
			0, // Natural
			0, // Run
			0, // Walk
			11, // SpecialCast
			0, // Special1
			0, // Special2
			0, // Special3
			0, // Special4
			0, // Dead
		};
	};
}
