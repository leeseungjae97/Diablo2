#pragma once
#include "mMath.h"
//#include "MonsterHandLookUpTables.h"
#include "SkillLookUpTables.h"
#include "SkillAnimLookUpTables.h"

namespace m
{
	enum class ePlayerAnimationType
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
	std::wstring sorceressAnimationString[(UINT)ePlayerAnimationType::End] = {
		L"sorceressAttack1_anim@",
		L"sorceressAttack2_anim@",
		L"sorceressBlock_anim@",
		L"sorceressGetHit_anim@",
		L"sorceressKick_anim@",
		L"sorceressNatural_anim@",
		L"sorceressRun_anim@",
		L"sorceressSpecial1_anim@",
		L"sorceressSpecialCast_anim@",
		L"sorceressTownNatural_anim@",
		L"sorceressTownWalk_anim@",
		L"sorceressWalk_anim@",
		L"sorceressDead_anim@",
	};
	enum class eSixteenDirection
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
	int eEightDirection[8] = {
		(int)eSixteenDirection::Down,
		(int)eSixteenDirection::LeftDown1,
		(int)eSixteenDirection::Left,
		(int)eSixteenDirection::LeftUp1,
		(int)eSixteenDirection::Up,
		(int)eSixteenDirection::RightUp1,
		(int)eSixteenDirection::Right,
		(int)eSixteenDirection::RightDown1,
	};
	std::wstring sixteenDirectionString[(UINT)eSixteenDirection::End] = {
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
	math::Vector2 sorceressAnimationSizes[(UINT)ePlayerAnimationType::End] = {
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
	int sorceressAnimationLength[(UINT)ePlayerAnimationType::End] = {
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
	int plusSixteenDirections[((int)eSixteenDirection::End / 2) + 1] = {
		(int)eSixteenDirection::Up,
		(int)eSixteenDirection::RightUp1,
		(int)eSixteenDirection::RightUp2,
		(int)eSixteenDirection::RightUp3,
		(int)eSixteenDirection::Right,
		(int)eSixteenDirection::RightDown1,
		(int)eSixteenDirection::RightDown2,
		(int)eSixteenDirection::RightDown3,
		(int)eSixteenDirection::Down
	};
	int minusSixteenDirections[((int)eSixteenDirection::End / 2) + 1] = {
		(int)eSixteenDirection::Up,
		(int)eSixteenDirection::LeftUp3,
		(int)eSixteenDirection::LeftUp2,
		(int)eSixteenDirection::LeftUp1,
		(int)eSixteenDirection::Left,
		(int)eSixteenDirection::LeftDown3,
		(int)eSixteenDirection::LeftDown2,
		(int)eSixteenDirection::LeftDown1,
		(int)eSixteenDirection::Down,
	};
	int plusEightDirections[5] = {
		(int)eSixteenDirection::Up,
		(int)eSixteenDirection::RightUp1,
		(int)eSixteenDirection::Right,
		(int)eSixteenDirection::RightDown1,
		(int)eSixteenDirection::Down,
	};
	int minusEightDirections[5] = {
		(int)eSixteenDirection::Up,
		(int)eSixteenDirection::LeftUp1,
		(int)eSixteenDirection::Left,
		(int)eSixteenDirection::LeftDown1,
		(int)eSixteenDirection::Down,
	};

	enum class eMonsterType
	{
		Diablo,
		Andariel,
		Duriel,
		Mephisto,
		Balrog,
		End,
	};
	enum class eMonsterClass
	{
		Boss,
		Normal,
		End,
	};
	eMonsterClass monsterClasses[(int)eMonsterType::End] = {
		eMonsterClass::Boss,
		eMonsterClass::Normal,

	};
	struct MonsterData
	{
		MonsterData() {}
		~MonsterData() {}
		std::wstring textureString[5] = {};
		std::wstring animationString[5] = {};
		math::Vector2 animationOffset[5] = {};
		m::math::Vector2 animationSizes[5] = {};
		m::math::Vector2 animationCenterPos[5] = {};
		float animationDuration[5] = {};
		int animationLength[5] = {};
		int animStartIndex[5] = {};
		int animEndIndex[5] = {};
		int animProgressStartIndex[5] = {};
		int iBehavior = 0;
		float animYOffset = 0.f;

		float fSpeed = 100.f;
		float fAttackDelay = 1.5f;
		float hp = 100;
		float hpCapacity = hp;
		eSkillType mSpecialSkills[5] = {
			eSkillType::END
			,eSkillType::END
			,eSkillType::END
			,eSkillType::END
		};
		const std::wstring wsMonsterName = L"";

		eAuraType passiveAura = eAuraType::End;
		m::math::Vector2 auraOffSet = m::math::Vector2(0.f, 0.f);

		m::enums::eColliderFunctionType mSkillActiveColliderType[5] = {
		m::enums::eColliderFunctionType::End
		, m::enums::eColliderFunctionType::End
		, m::enums::eColliderFunctionType::End
		, m::enums::eColliderFunctionType::End
		, m::enums::eColliderFunctionType::End
		};
		bool bSpecialSkillLoop[5] = { false,false, false, false, false };
		bool bSpecialSkillStopInProgress[5] = { false, false, false, false, false };
		int mSpecialSkillAddFunction[5] = { 0,0,0,0 };
		int mSpecialSkillCount[5] = { 0, 0, 0, 0 };

		eMonsterType mMonsterType = eMonsterType::End;
		eMonsterClass mClass = eMonsterClass::Normal;

		bool bPathImage = false;
		bool bHandAnim = false;

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
			ToDead,
			End,
		};
	};
	struct MDBalrog : public MonsterData
	{
		MDBalrog() {}
		~MDBalrog() {}

		float fSpeed = 200.f;
		float fAttackDelay = 2.5f;
		float hp = 100;
		float hpCapacity = hp;
		bool bSpecialSkillLoop[5] = { false,false, false, false, false };
		bool bSpecialSkillStopInProgress[5] = { false, false, false, false, false };
		eSkillType mSpecialSkills[5] = {
			eSkillType::END
			,eSkillType::END
			,eSkillType::END
			,eSkillType::END
			,eSkillType::END
		};
		m::enums::eColliderFunctionType mSkillActiveColliderType[5] = {
		m::enums::eColliderFunctionType::End
		,m::enums::eColliderFunctionType::End
		,m::enums::eColliderFunctionType::End
		,m::enums::eColliderFunctionType::End
		,m::enums::eColliderFunctionType::End
		};
		eAuraType passiveAura = eAuraType::End;
		m::math::Vector2 auraOffSet = m::math::Vector2(0.f, 0.f);

		const std::wstring wsMonsterName = L"발록";

		int mSpecialSkillAddFunction[5] = { 0,0,0,0 };

		int mSpecialSkillCount[5] = { 0, 0, 0, 0 };
		int iBehavior = 4;
		eMonsterType mMonsterType = eMonsterType::Balrog;
		eMonsterClass mClass = eMonsterClass::Normal;

		bool bPathImage = true;
		bool bHandAnim = true;

		std::wstring textureString[(UINT)eAnimationType::End] = {
			L"balrogAttack",
			L"",
			L"",
			L"balrogHit",
			L"balrogNatural",
			L"balrogRun",
			L"",
			L"",
			L"",
			L"",
			L"",
			L"",
			L"",
			L"balrogToDead",
		};
		std::wstring animationString[(UINT)eAnimationType::End] = {
			L"balrogAttack_anim@",
			L"",
			L"",
			L"balrogHit_anim@",
			L"balrogNatural_anim@",
			L"balrogRun_anim@",
			L"",
			L"",
			L"",
			L"",
			L"",
			L"",
			L"",
			L"balrogToDead_anim@",
		};
		math::Vector2 animationOffset[(UINT)eAnimationType::End] = {
			math::Vector2(0.f, 0.f), // Attack
			math::Vector2(0.f, 0.f),
			math::Vector2(0.f, 0.f),
			math::Vector2(0.f, 0.f),	// Hit
			math::Vector2(0.f, 0.f),	// Natural
			math::Vector2(0.f, 0.f),	// Run
			math::Vector2(0.f, 0.f),
			math::Vector2(0.f, 0.f),
			math::Vector2(0.f, 0.f),
			math::Vector2(0.f, 0.f),
			math::Vector2(0.f, 0.f),
			math::Vector2(0.f, 0.f),
			math::Vector2(0.f, 0.f),
			math::Vector2(0.f, 0.f),	// Dead
		};
		math::Vector2 animationCenterPos[(UINT)eAnimationType::End] = {
	math::Vector2(0.f, 0.f), // Attack
	math::Vector2(0.f, 0.f),
	math::Vector2(0.f, 0.f),
	math::Vector2(0.f, 0.f),	// Hit
	math::Vector2(0.f, 0.f),	// Natural
	math::Vector2(0.f, 0.f),	// Run
	math::Vector2(0.f, 0.f),
	math::Vector2(0.f, 0.f),
	math::Vector2(0.f, 0.f),
	math::Vector2(0.f, 0.f),
	math::Vector2(0.f, 0.f),
	math::Vector2(0.f, 0.f),
	math::Vector2(0.f, 0.f),
	math::Vector2(0.f, 0.f),	// Dead
		};
		math::Vector2 animationSizes[(UINT)eAnimationType::End] = {
			math::Vector2(222.f, 157.f),	// Attack
			math::Vector2(0.f, 0.f),
			math::Vector2(0.f, 0.f),
			math::Vector2(197.f, 145.f),	// Hit
			math::Vector2(191.f, 148.f),	// Natural
			math::Vector2(171.f, 153.f),	// Run
			math::Vector2(0.f, 0.f),
			math::Vector2(0.f, 0.f),
			math::Vector2(0.f, 0.f),
			math::Vector2(0.f, 0.f),
			math::Vector2(0.f, 0.f),
			math::Vector2(0.f, 0.f),
			math::Vector2(0.f, 0.f),
			math::Vector2(210.f, 179.f),  // Dead
		};
		float animationDuration[(UINT)eAnimationType::End] = {
			0.05f,   // Attack
			0.f,	// Attack2
			0.f,	// block
			0.05f,	// Hit
			0.05f,	// Natural
			0.05f,	// Run
			0.f,
			0.f,
			0.f,
			0.f,
			0.f,
			0.f,
			0.f,
			0.05f,	// Dead
		};
		int animationLength[(UINT)eAnimationType::End] = {
			16,// Attack
			0,
			0,
			6, //Hit
			8,// Natural
			8, // Run
			0,
			0,
			0,
			0,
			0,
			0,
			1,
			20, // Dead
		};
		int animStartIndex[(UINT)eAnimationType::End] = {
			0,// Attack1
			0,
			0,
			0, // Hit
			0,// Natural
			0, // Run
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0, // Dead
		};
		int animEndIndex[(UINT)eAnimationType::End] = {
			0,// Attack
			0,
			0,
			0, // Hit
			0,// Natural
			0, // Run
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0, // Dead
		};
		int animProgressStartIndex[(UINT)eAnimationType::End] = {
			12,// Attack
			0,
			0,
			0, // Hit
			0, // Natural
			0, // Run
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0, // Dead
		};
	};
	struct MDDiablo : public MonsterData
	{
		MDDiablo() {}
		~MDDiablo() {}

		float fSpeed = 200.f;
		float fAttackDelay = 2.5f;
		float hp = 1;
		float hpCapacity = hp;

		eSkillType mSpecialSkills[5] = {
			eSkillType::DiabloLightning
			,eSkillType::DiabloFireNova
			,eSkillType::DiabloFireStorm
			,eSkillType::END
			,eSkillType::END
		};
		m::enums::eColliderFunctionType mSkillActiveColliderType[5] = {
			m::enums::eColliderFunctionType::Sight
			, m::enums::eColliderFunctionType::Sight
			, m::enums::eColliderFunctionType::Sight
			, m::enums::eColliderFunctionType::End
			, m::enums::eColliderFunctionType::End
		};
		const std::wstring wsMonsterName = L"디아블로";

		eAuraType passiveAura = eAuraType::End;
		m::math::Vector2 auraOffSet = m::math::Vector2(0.f, 0.f);
		bool bSpecialSkillLoop[5] = { true,false, false, false, false };
		bool bSpecialSkillStopInProgress[5] = { true, false, false, false, false };
		int mSpecialSkillAddFunction[5] = {
			0/*eFireType::Linear*/
			,0
			,2
			,0
			,0
		};

		int mSpecialSkillCount[5] = { 20, 40, 3, 0, 0 };
		int iBehavior = 12;

		eMonsterType mMonsterType = eMonsterType::Diablo;
		eMonsterClass mClass = eMonsterClass::Boss;


		bool bPathImage = false;
		bool bHandAnim = false;

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
			L"diabloToDead1",
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
			L"diabloDead_anim@",
			L"diabloToDead1_anim@",
		};
		math::Vector2 animationOffset[(UINT)eAnimationType::End] = {
			math::Vector2(0.f, 0.f), // Attack1
			math::Vector2(0.f, 0.f),	// Attack2
			math::Vector2(0.f, 0.f),	// Block
			math::Vector2(0.f, 0.f),	// Hit
			math::Vector2(0.f, 0.f),	// Natural
			math::Vector2(0.f, 15.f),	// Run
			math::Vector2(0.f, 0.f),	// Walk
			math::Vector2(0.f, -15.f),// SpecialCast
			math::Vector2(0.f, -15.f),	// Special1
			math::Vector2(0.f, -15.f),	// Special2
			math::Vector2(0.f, 0.f),	// Special3
			math::Vector2(0.f, 0.f),	// Special4
			math::Vector2(0.f, 0.f),	// Dead
			math::Vector2(0.f, 0.f),	// Dead
		};
		math::Vector2 animationCenterPos[(UINT)eAnimationType::End] = {
            math::Vector2(0.f, 0.f), // Attack
            math::Vector2(0.f, 0.f),
            math::Vector2(0.f, 0.f),
            math::Vector2(0.f, 0.f),	// Hit
            math::Vector2(0.f, 0.f),	// Natural
            math::Vector2(0.f, 0.f),	// Run
            math::Vector2(0.f, 0.f),
            math::Vector2(0.f, 0.f),
            math::Vector2(0.f, 0.f),
            math::Vector2(0.f, 0.f),
            math::Vector2(0.f, 0.f),
            math::Vector2(0.f, 0.f),
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
			math::Vector2(266.f, 306.f),					// Dead
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
			60,
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
			8, // Special1
			5, // Special2
			8, // Special3
			8, // Special4
			0, // Dead
			0, // Dead
		};
	};
	struct MDAndariel : public MonsterData
	{
		MDAndariel() {}
		~MDAndariel() {}

		float fSpeed = 200.f;
		float fAttackDelay = 2.5f;
		float hp = 1;
		float hpCapacity = hp;

		eSkillType mSpecialSkills[5] = {
		eSkillType::AndarielPoisonAttack
			,eSkillType::END
			,eSkillType::END
			,eSkillType::END
		};
		eAuraType passiveAura = eAuraType::End;
		m::math::Vector2 auraOffSet = m::math::Vector2(0.f, 0.f);

		const std::wstring wsMonsterName = L"안다리엘";

		m::enums::eColliderFunctionType mSkillActiveColliderType[5] = { m::enums::eColliderFunctionType::Sight
			, m::enums::eColliderFunctionType::End
			, m::enums::eColliderFunctionType::End
			, m::enums::eColliderFunctionType::End
			, m::enums::eColliderFunctionType::End
		};
		bool bSpecialSkillLoop[5] = { false,false, false, false, false };
		bool bSpecialSkillStopInProgress[5] = { false, false, false, false };
		int mSpecialSkillAddFunction[5] = {
		    5/*eFireType::Radial*/
			,0
			,0
			,0 };

		int mSpecialSkillCount[5] = { 10, 0, 0, 0 };

		eMonsterType mMonsterType = eMonsterType::Andariel;
		eMonsterClass mClass = eMonsterClass::Boss;

		bool bPathImage = true;
		bool bHandAnim = false;

		std::wstring textureString[(UINT)eAnimationType::End] = {
			L"andarielAttack",// Attack1
			L"",			  // Attack2
			L"",			  // Block
			L"andarielHit",	  // Hit
			L"andarielNatural",// Natural,
			L"andarielWalk",  // Run
			L"",			  // Walk
			L"andarielSpecial",// SpecialCast,
			L"",			  // Special1
			L"",			  // Special2
			L"",			 // Special3
			L"",			 // Special4
			L"andarielDead", // Dead
			L"andarielToDead",
		};
		std::wstring animationString[(UINT)eAnimationType::End] = {
			L"andarielAttack_anim@",// Attack1
			L"",					// Attack2
			L"",					// Block
			L"andarielHit_anim@",	// Hit
			L"andarielNatural_anim@",// Natural,
			L"andarielWalk_anim@",	// Run
			L"",					// Walk
			L"andarielSpecial_anim@",// SpecialCast,
			L"",					// Special1
			L"",					// Special2
			L"",				   // Special3
			L"",				   // Special4
			L"andarielDead_anim@", // Dead
			L"andarielToDead_anim@",
		};
		math::Vector2 animationOffset[(UINT)eAnimationType::End] = {
			math::Vector2(0.f, 12.f), // Attack1
			math::Vector2(0.f, 0.f),	// Attack2
			math::Vector2(0.f, 0.f),	// Block
			math::Vector2(0.f, 0.f),	// Hit
			math::Vector2(0.f, 0.f),	// Natural
			math::Vector2(0.f, 0.f),	// Run
			math::Vector2(0.f, 0.f),	// Walk
			math::Vector2(0.f, 0.f),	// SpecialCast
			math::Vector2(0.f, 0.f),	// Special1
			math::Vector2(0.f, 0.f),	// Special2
			math::Vector2(0.f, 0.f),	// Special3
			math::Vector2(0.f, 0.f),	// Special4
			math::Vector2(0.f, 0.f),	// Dead
			math::Vector2(0.f, 0.f),	// Dead
		};
		math::Vector2 animationCenterPos[(UINT)eAnimationType::End] = {
            math::Vector2(0.f, 0.f), // Attack
            math::Vector2(0.f, 0.f),
            math::Vector2(0.f, 0.f),
            math::Vector2(0.f, 0.f),	// Hit
            math::Vector2(0.f, 0.f),	// Natural
            math::Vector2(0.f, 0.f),	// Run
            math::Vector2(0.f, 0.f),
            math::Vector2(0.f, 0.f),
            math::Vector2(0.f, 0.f),
            math::Vector2(0.f, 0.f),
            math::Vector2(0.f, 0.f),
            math::Vector2(0.f, 0.f),
            math::Vector2(0.f, 0.f),	// Dead
            math::Vector2(0.f, 0.f),	// Dead
		};
		math::Vector2 animationSizes[(UINT)eAnimationType::End] = {
			math::Vector2(247.f, 248.f),	// Attack1
			math::Vector2(),	// Attack2
			math::Vector2(),	// Block
			math::Vector2(173.f, 180.f),	// Hit
			math::Vector2(178.f, 179.f),	// Natural
			math::Vector2(148.f, 184.f),	// Run
			math::Vector2(),	// Walk
			math::Vector2(212.f, 182.f),	// SpecialCast
			math::Vector2(),	// Special1
			math::Vector2(),	// Special2
			math::Vector2(),	// Special3
			math::Vector2(),	// Special4
			math::Vector2(177.f, 116.f),					// Dead
			math::Vector2(203.f, 232.f),					// ToDead

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
			0.05f,	// Dead
		};
		int animationLength[(UINT)eAnimationType::End] = {
			16,// Attack1
			0,// Attack2
			0, // Block
			6, // Hit
			16,// Natural
			12, // Run
			0, // Walk
			18,// SpecialCast
			0,// Special1
			0, // Special2
			0, // Special3
			0	, // Special4
			1, // Dead
			23, // ToDead
		};
		int animStartIndex[(UINT)eAnimationType::End] = {
			0,// Attack1
			0,// Attack2
			0, // Block
			0, // Hit
			0,// Natural
			0, // Run
			0, // Walk
			0,// SpecialCast
			0,// Special1
			0, // Special2
			0, // Special3
			0, // Special4
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
			0,// SpecialCast
			0,// Special1
			0, // Special2
			0, // Special3
			0, // Special4
			0, // Special4
			0, // Dead
		};
		int animProgressStartIndex[(UINT)eAnimationType::End] = {
			0,// Attack1
			0, // Attack2
			0, // Block
			0, // Hit
			0, // Natural
			0, // Run
			0, // Walk
			17, // SpecialCast
			0, // Special1
			0, // Special2
			0, // Special3
			0, // Special4
			0, // Special4
			0, // Dead
		};
	};
	struct MDDuriel : public MonsterData
	{
		MDDuriel() {}
		~MDDuriel() {}

		float fSpeed = 200.f;
		float fAttackDelay = 2.5f;
		float hp = 1;
		float hpCapacity = hp;

		eSkillType mSpecialSkills[5] = {
			eSkillType::END
			,eSkillType::END
			,eSkillType::END
			,eSkillType::END
			,eSkillType::END
		};
		eAuraType passiveAura = eAuraType::HolyFreeze;
		m::math::Vector2 auraOffSet = m::math::Vector2(0.f, -30.f);
		const std::wstring wsMonsterName = L"두리엘";
		m::enums::eColliderFunctionType mSkillActiveColliderType[5] = {
			m::enums::eColliderFunctionType::Range
			, m::enums::eColliderFunctionType::End
			, m::enums::eColliderFunctionType::End
			, m::enums::eColliderFunctionType::End
			, m::enums::eColliderFunctionType::End
		};
		bool bSpecialSkillLoop[5] = { false,false, false, false, false };
		bool bSpecialSkillStopInProgress[5] = { false, false, false, false };
		int mSpecialSkillAddFunction[5] = { 0,0,0,0 };

		int mSpecialSkillCount[5] = { 0, 0, 0, 0 };


		eMonsterType mMonsterType = eMonsterType::Duriel;
		eMonsterClass mClass = eMonsterClass::Boss;

		bool bPathImage = false;
		bool bHandAnim = false;

		// Duriel have stun effect attack2
		// categorization special

		std::wstring textureString[(UINT)eAnimationType::End] = {
			L"durielAttack1",
			L"",
			L"",
			L"durielHit",
			L"durielNatural",
			L"durielWalk",
			L"",
			L"durielAttack2",
			L"",
			L"",
			L"",
			L"",
			L"durielDead",
			L"durielToDead",
		};
		std::wstring animationString[(UINT)eAnimationType::End] = {
			L"durielAttack1_anim@",
			L"",
			L"",
			L"durielHit_anim@",
			L"durielNatural_anim@",
			L"durielWalk_anim@",
			L"",
			L"durielAttack2_anim@",
			L"",
			L"",
			L"",
			L"",
			L"durielDead_anim@",
			L"durielToDead_anim@",
		};
		math::Vector2 animationOffset[(UINT)eAnimationType::End] = {
			math::Vector2(10.f, 0.f), // Attack1
			math::Vector2(0.f, 0.f),	// Attack2
			math::Vector2(0.f, 0.f),	// Block
			math::Vector2(0.f, 0.f),	// Hit
			math::Vector2(0.f, 0.f),	// Natural
			math::Vector2(0.f, 0.f),	// Run
			math::Vector2(0.f, 0.f),	// Walk
			math::Vector2(-10.f, 0.f),	// SpecialCast
			math::Vector2(0.f, 0.f),	// Special1
			math::Vector2(0.f, 0.f),	// Special2
			math::Vector2(0.f, 0.f),	// Special3
			math::Vector2(0.f, 0.f),	// Special4
			math::Vector2(0.f, 0.f),	// Dead
		};
		math::Vector2 animationCenterPos[(UINT)eAnimationType::End] = {
            math::Vector2(0.f, 0.f), // Attack
            math::Vector2(0.f, 0.f),
            math::Vector2(0.f, 0.f),
            math::Vector2(0.f, 0.f),	// Hit
            math::Vector2(0.f, 0.f),	// Natural
            math::Vector2(0.f, 0.f),	// Run
            math::Vector2(0.f, 0.f),
            math::Vector2(0.f, 0.f),
            math::Vector2(0.f, 0.f),
            math::Vector2(0.f, 0.f),
            math::Vector2(0.f, 0.f),
            math::Vector2(0.f, 0.f),
            math::Vector2(0.f, 0.f),	// Dead
		};
		math::Vector2 animationSizes[(UINT)eAnimationType::End] = {
			math::Vector2(301.f, 201.f),	// Attack1
			math::Vector2(),	// Attack2
			math::Vector2(),	// Block
			math::Vector2(207.f, 188.f),	// Hit
			math::Vector2(172.f, 186.f),	// Natural
			math::Vector2(253.f, 225.f),	// Run
			math::Vector2(),	// Walk
			math::Vector2(287.f, 188.f),	// SpecialCast
			math::Vector2(),	// Special1
			math::Vector2(),	// Special2
			math::Vector2(),	// Special3
			math::Vector2(),	// Special4
			math::Vector2(263.f, 160.f),					// Dead
			math::Vector2(266.f, 232.f),					// ToDead

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
			0.05f,	// Dead
		};
		int animationLength[(UINT)eAnimationType::End] = {
			10,// Attack1
			0,// Attack2
			0, // Block
			6, // Hit
			12,// Natural
			16, // Run
			0, // Walk
			15,// SpecialCast
			0,// Special1
			0, // Special2
			0, // Special3
			0	, // Special4
			1, // Dead
			25, // ToDead
		};
		int animStartIndex[(UINT)eAnimationType::End] = {
			0,// Attack1
			0,// Attack2
			0, // Block
			0, // Hit
			0,// Natural
			0, // Run
			0, // Walk
			0,// SpecialCast
			0,// Special1
			0, // Special2
			0, // Special3
			0, // Special4
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
			0,// SpecialCast
			0,// SpecialCast
			0,// Special1
			0, // Special2
			0, // Special3
			0, // Special4
			0, // Dead
		};
		int animProgressStartIndex[(UINT)eAnimationType::End] = {
			5,// Attack1
			0, // Attack2
			0, // Block
			0, // Hit
			0, // Natural
			0, // Run
			0, // Walk
			8, // SpecialCast
			0, // Special1
			0, // Special2
			0, // Special3
			0, // Special3
			0, // Special4
			0, // Dead
		};
	};
	struct MDMephisto : public MonsterData
	{
		MDMephisto() {}
		~MDMephisto() {}

		float fSpeed = 200.f;
		float fAttackDelay = 2.5f;
		float hp = 1;
		float hpCapacity = hp;

		bool bSpecialSkillLoop[5] = { false,false, false, false, false };
		bool bSpecialSkillStopInProgress[5] = { false, false, false, false, false };

		const std::wstring wsMonsterName = L"메피스토";
		eSkillType mSpecialSkills[5] = {
			eSkillType::lightning
			,eSkillType::chargedBolt
			,eSkillType::mephistoMissile
			,eSkillType::END
			,eSkillType::END
		};
		m::enums::eColliderFunctionType mSkillActiveColliderType[5] = {
			m::enums::eColliderFunctionType::Sight
			, m::enums::eColliderFunctionType::Sight
			, m::enums::eColliderFunctionType::Sight
			, m::enums::eColliderFunctionType::End
			, m::enums::eColliderFunctionType::End
		};
		eAuraType passiveAura = eAuraType::MephistoOverlay;

		m::math::Vector2 auraOffSet = m::math::Vector2(0.f, 0.f);

		int mSpecialSkillAddFunction[5] = { 0,3,0,0, 0 };

		int mSpecialSkillCount[5] = { 20, 6, 0, 0, 0 };

		eMonsterType mMonsterType = eMonsterType::Mephisto;
		eMonsterClass mClass = eMonsterClass::Boss;

		bool bPathImage = false;
		bool bHandAnim = false;


		std::wstring textureString[(UINT)eAnimationType::End] = {
			L"mephistoAttack1",					
			L"mephistoAttack21",					
			L"",					
			L"mephistoGetHit",					
			L"mephistoNatural",					
			L"mephistoWalk",					
			L"",					
			L"mephistoAttack2",					
			L"mephistoAttack2",					
			L"mephistoAttack2",
			L"",					
			L"",					
			L"mephistoDead",					
			L"mephistoToDead",					
		};
		std::wstring animationString[(UINT)eAnimationType::End] = {
			L"mephistoAttack1_anim@",
			L"mephistoAttack21_anim@",
			L"",
			L"mephistoGetHit_anim@",
			L"mephistoNatural_anim@",
			L"mephistoWalk_anim@",
			L"",
			L"mephistoAttack2_anim@",
			L"mephistoAttack3_anim@",
			L"mephistoAttack4_anim@",
			L"",
			L"",
			L"mephistoDead_anim@",
			L"mephistoToDead_anim@",
		};
		math::Vector2 animationOffset[(UINT)eAnimationType::End] = {
			math::Vector2(0.f, 0.f), // Attack1
			math::Vector2(0.f, 0.f),	// Attack2
			math::Vector2(0.f, 0.f),	// Block
			math::Vector2(0.f, 0.f),	// Hit
			math::Vector2(0.f, 0.f),	// Natural
			math::Vector2(0.f, 0.f),	// Run
			math::Vector2(0.f, 0.f),	// Walk
			math::Vector2(0.f, 0.f),	// SpecialCast
			math::Vector2(0.f, 0.f),	// Special1
			math::Vector2(0.f, 0.f),	// Special2
			math::Vector2(0.f, 0.f),	// Special3
			math::Vector2(0.f, 0.f),	// Special4
			math::Vector2(0.f, 0.f),	// Dead
			math::Vector2(0.f, 0.f),	// Dead
		};
		math::Vector2 animationCenterPos[(UINT)eAnimationType::End] = {
            math::Vector2(0.f, 0.f), // Attack
            math::Vector2(0.f, 0.f),
            math::Vector2(0.f, 0.f),
            math::Vector2(0.f, 0.f),	// Hit
            math::Vector2(0.f, 0.f),	// Natural
            math::Vector2(0.f, 0.f),	// Run
            math::Vector2(0.f, 0.f),
            math::Vector2(0.f, 0.f),
            math::Vector2(0.f, 0.f),
            math::Vector2(0.f, 0.f),
            math::Vector2(0.f, 0.f),
            math::Vector2(0.f, 0.f),
            math::Vector2(0.f, 0.f),	// Dead
            math::Vector2(0.f, 0.f),	// Dead
		};
		math::Vector2 animationSizes[(UINT)eAnimationType::End] = {
			math::Vector2(5526.f / 18.f, 2471.f / 8.f),	// Attack1
			math::Vector2(5219.f / 17.f, 2471.f / 8.f),	// attack2
			math::Vector2(),	// Block
			math::Vector2(1842.f / 6.f, 2471.f / 8.f),	// Hit
			math::Vector2(3991.f / 13.f, 2471.f / 8.f),	// Natural
			math::Vector2(3991.f / 13.f, 2471.f / 8.f),	// Run
			math::Vector2(),	// Walk
			math::Vector2(5219.f / 17.f, 2471.f / 8.f),	// specialcast
			math::Vector2(5219.f / 17.f, 2471.f / 8.f),	// specialcast
			math::Vector2(5219.f / 17.f, 2471.f / 8.f),	// specialcast
			math::Vector2(),	// Special3
			math::Vector2(),	// Special4
			math::Vector2(308.f, 2471.f / 8.f),					// Dead
			math::Vector2(7675.f / 25.f, 2471.f / 8.f),// ToDead

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
			0.05f,	// Dead
		};
		int animationLength[(UINT)eAnimationType::End] = {
			18,// Attack1
			17,// Attack2
			0, // Block
			6, // Hit
			13,// Natural
			13, // Run
			0, // Walk
			17,// SpecialCast
			17,// SpecialCast
			17,// SpecialCast
			0, // Special3
			0	, // Special4
			1, // Dead
			25, // ToDead
		};
		int animStartIndex[(UINT)eAnimationType::End] = {
			0,// Attack1
			0,// Attack2
			0, // Block
			0, // Hit
			0,// Natural
			0, // Run
			0, // Walk
			0,// SpecialCast
			0,// Special1
			0, // Special2
			0, // Special3
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
			0,// SpecialCast
			0,// Special1
			0, // Special2
			0, // Special2
			0, // Special3
			0, // Special4
			0, // Dead
		};
		int animProgressStartIndex[(UINT)eAnimationType::End] = {
			6,// Attack1
			7, // Attack2
			0, // Block
			0, // Hit
			0, // Natural
			0, // Run
			0, // Walk
			7, // SpecialCast
			7, // Special1
			7, // Special2
			0, // Special3
			0, // Special4
			0, // Special4
			0, // Dead
		};
	};
}
