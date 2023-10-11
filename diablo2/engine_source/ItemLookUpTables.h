#pragma once

namespace m
{
	enum class eItemIncreaseType
	{
	    Life,
		Mana,
		Energy,
		Strenght,
		Stanmina,
		Vitality,
		Defense,
		Damage,
		Posion,
	};
	enum class eItemType
	{
		None,
		RightWeapon,
		LeftWeapon,
		RightRing,
		LeftRing,
		Amulet,
		Belt,
		Helmet,
		Shoes,
		Glove,
		Armor,
		Posion,
		Scroll,
		END,
	};

	enum class eItem
	{
		hpPosion1,
		mpPosion1,

		jaredsStone,

		leaderArmor,

		cap,
		END
	};
	//std::wstring 
	std::wstring itemNameTable[(int)eItem::END] = {
		// posions
		L"hpPosion1",
		L"mpPosion1",

		//weapons
		L"jaredsStone",

		//armor
		L"leaderArmor",

		//helmet
		L"cap",
	};
	bool bodyChange[(int)eItem::END] = {
		false,
		false,
		true,
		false,
		true,
	};
	eItemIncreaseType itemIncTable[(int)eItem::END] = {
		eItemIncreaseType::Posion,
		eItemIncreaseType::Posion,

		eItemIncreaseType::Damage,

		eItemIncreaseType::Defense,
		eItemIncreaseType::Defense,
	};
	std::wstring fieldItemTable[(int)eItem::END] = {
		L"hpPosionField",
		L"mpPosionField",
		L"jaredsStoneField",
		L"leaderArmorField",
		L"capField"
	};
	std::wstring fieldItemAnimTable[(int)eItem::END] = {
		L"hpPosionAnim",
		L"mpPosionAnim",
		L"jaredsStoneAnim",
		L"leaderArmorAnim",
		L"capAnim",
	};
	int fieldItemAnimLenght[(int)eItem::END] = {
		17,
		17,
		18,
		17,
		17,
	};
	std::wstring itemBodyPartMaterialNames[(int)eItem::END][6][13] = {
		{},
		{},

		{
			//head
			{
				L"",// Attack1 
				L"",// Attack2 
				L"",// Block 
				L"",// GetHit 
				L"",// Kick 
				L"",// Natural 
				L"",// Run 
				L"",// Special1 
				L"",// SpecialCast 
				L"",// TownNatural 
				L"",// TownWalk 
				L"",// Walk 
				L"",// Dead
			},
			//left arm
			{
				L"",// Attack1 
				L"",// Attack2 
				L"",// Block 
				L"",// GetHit 
				L"",// Kick 
				L"",// Natural 
				L"",// Run 
				L"",// Special1 
				L"",// SpecialCast 
				L"",// TownNatural 
				L"",// TownWalk 
				L"",// Walk 
				L"",// Dead
			},
			//right arm
			{
			L"",// Attack1 
				L"",// Attack2 
				L"",// Block 
				L"obRaGH",// GetHit 
				L"",// Kick 
				L"obRaNU",// Natural 
				L"obRaR",// Run 
				L"",// Special1 
				L"raSC",// SpecialCast 
				L"",// TownNatural 
				L"",// TownWalk 
				L"",// Walk 
				L"",// Dead 
			},
			//body
			{
				L"",// Attack1 
				L"",// Attack2 
				L"",// Block 
				L"",// GetHit 
				L"",// Kick 
				L"",// Natural 
				L"",// Run 
				L"",// Special1 
				L"",// SpecialCast 
				L"",// TownNatural 
				L"",// TownWalk 
				L"",// Walk 
				L"",// Dead
			},
			//leg
			{
				L"",// Attack1 
				L"",// Attack2 
				L"",// Block 
				L"",// GetHit 
				L"",// Kick 
				L"",// Natural 
				L"",// Run 
				L"",// Special1 
				L"",// SpecialCast 
				L"",// TownNatural 
				L"",// TownWalk 
				L"",// Walk 
				L"",// Dead
			},
			//right hand
	        {
			L"",// Attack1 
			L"",// Attack2 
			L"",// Block 
			L"obGH",// GetHit 
			L"",// Kick 
			L"obNU",// Natural 
			L"obR",// Run
			L"",// Special1 
			L"obSC",// SpecialCast 
			L"",// TownNatural 
			L"",// TownWalk 
			L"",// Walk 
			L"",// Dead 
			}
		},
     {},
     {
		 //head
			{
				L"",// Attack1 
				L"",// Attack2 
				L"",// Block 
				L"cpHdGH",// GetHit 
				L"",// Kick 
				L"cpHdNU",// Natural 
				L"cpHdR",// Run 
				L"",// Special1 
				L"cpHdSC",// SpecialCast 
				L"",// TownNatural 
				L"",// TownWalk 
				L"",// Walk 
				L"",// Dead
			},
			//left arm
			{
				L"",// Attack1 
				L"",// Attack2 
				L"",// Block 
				L"",// GetHit 
				L"",// Kick 
				L"",// Natural 
				L"",// Run 
				L"",// Special1 
				L"",// SpecialCast 
				L"",// TownNatural 
				L"",// TownWalk 
				L"",// Walk 
				L"",// Dead
			},
			//right arm
			{
			L"",// Attack1 
				L"",// Attack2 
				L"",// Block 
				L"",// GetHit 
				L"",// Kick 
				L"",// Natural 
				L"",// Run 
				L"",// Special1 
				L"",// SpecialCast 
				L"",// TownNatural 
				L"",// TownWalk 
				L"",// Walk 
				L"",// Dead 
			},
			//body
			{
				L"",// Attack1 
				L"",// Attack2 
				L"",// Block 
				L"",// GetHit 
				L"",// Kick 
				L"",// Natural 
				L"",// Run 
				L"",// Special1 
				L"",// SpecialCast 
				L"",// TownNatural 
				L"",// TownWalk 
				L"",// Walk 
				L"",// Dead
			},
			//leg
			{
				L"",// Attack1 
				L"",// Attack2 
				L"",// Block 
				L"",// GetHit 
				L"",// Kick 
				L"",// Natural 
				L"",// Run 
				L"",// Special1 
				L"",// SpecialCast 
				L"",// TownNatural 
				L"",// TownWalk 
				L"",// Walk 
				L"",// Dead
			},
			//right hand
			{
			L"",// Attack1 
			L"",// Attack2 
			L"",// Block 
			L"",// GetHit 
			L"",// Kick 
			L"",// Natural 
			L"",// Run
			L"",// Special1 
			L"",// SpecialCast 
			L"",// TownNatural 
			L"",// TownWalk 
			L"",// Walk 
			L"",// Dead 
			}
     },
	};
	m::math::Vector2 itemBodyPartSizes[(int)eItem::END][6][13] = {
		{},
		{},
		{
			//head
			{
				m::math::Vector2(0.f, 0.f),// Attack1 
				m::math::Vector2(0.f, 0.f),// Attack2 
				m::math::Vector2(0.f, 0.f),// Block 
				m::math::Vector2(0.f, 0.f),// GetHit 
				m::math::Vector2(0.f, 0.f),// Kick 
				m::math::Vector2(0.f, 0.f),// Natural 
				m::math::Vector2(0.f, 0.f),// Run 
				m::math::Vector2(0.f, 0.f),// Special1 
				m::math::Vector2(0.f, 0.f),// SpecialCast 
				m::math::Vector2(0.f, 0.f),// TownNatural 
				m::math::Vector2(0.f, 0.f),// TownWalk 
				m::math::Vector2(0.f, 0.f),// Walk 
				m::math::Vector2(0.f, 0.f),// Dead
			},
			// left arm
						{
				m::math::Vector2(0.f, 0.f),// Attack1 
				m::math::Vector2(0.f, 0.f),// Attack2 
				m::math::Vector2(0.f, 0.f),// Block 
				m::math::Vector2(0.f, 0.f),// GetHit 
				m::math::Vector2(0.f, 0.f),// Kick 
				m::math::Vector2(0.f, 0.f),// Natural 
				m::math::Vector2(0.f, 0.f),// Run 
				m::math::Vector2(0.f, 0.f),// Special1 
				m::math::Vector2(0.f, 0.f),// SpecialCast 
				m::math::Vector2(0.f, 0.f),// TownNatural 
				m::math::Vector2(0.f, 0.f),// TownWalk 
				m::math::Vector2(0.f, 0.f),// Walk 
				m::math::Vector2(0.f, 0.f),// Dead
			},
			// right arm
						{
				m::math::Vector2(0.f, 0.f),// Attack1 
				m::math::Vector2(0.f, 0.f),// Attack2 
				m::math::Vector2(0.f, 0.f),// Block 
				m::math::Vector2(48.f, 36.f),// GetHit 
				m::math::Vector2(0.f, 0.f),// Kick 
				m::math::Vector2(48.f, 35.f),// Natural 
				m::math::Vector2(42.f, 33.f),// Run 
				m::math::Vector2(0.f, 0.f),// Special1 
				m::math::Vector2(84.f, 64.f),// SpecialCast 
				m::math::Vector2(0.f, 0.f),// TownNatural 
				m::math::Vector2(0.f, 0.f),// TownWalk 
				m::math::Vector2(0.f, 0.f),// Walk 
				m::math::Vector2(0.f, 0.f),// Dead
			},
			// body
						{
				m::math::Vector2(0.f, 0.f),// Attack1 
				m::math::Vector2(0.f, 0.f),// Attack2 
				m::math::Vector2(0.f, 0.f),// Block 
				m::math::Vector2(60.f, 39.f),// GetHit 
				m::math::Vector2(0.f, 0.f),// Kick 
				m::math::Vector2(60.f, 38.f),// Natural 
				m::math::Vector2(46.f, 40.f),// Run 
				m::math::Vector2(0.f, 0.f),// Special1 
				m::math::Vector2(92.f, 66.f),// SpecialCast 
				m::math::Vector2(0.f, 0.f),// TownNatural 
				m::math::Vector2(0.f, 0.f),// TownWalk 
				m::math::Vector2(0.f, 0.f),// Walk 
				m::math::Vector2(0.f, 0.f),// Dead
			},
			// leg
						{
				m::math::Vector2(0.f, 0.f),// Attack1 
				m::math::Vector2(0.f, 0.f),// Attack2 
				m::math::Vector2(0.f, 0.f),// Block 
				m::math::Vector2(0.f, 0.f),// GetHit 
				m::math::Vector2(0.f, 0.f),// Kick 
				m::math::Vector2(0.f, 0.f),// Natural 
				m::math::Vector2(0.f, 0.f),// Run 
				m::math::Vector2(0.f, 0.f),// Special1 
				m::math::Vector2(0.f, 0.f),// SpecialCast 
				m::math::Vector2(0.f, 0.f),// TownNatural 
				m::math::Vector2(0.f, 0.f),// TownWalk 
				m::math::Vector2(0.f, 0.f),// Walk 
				m::math::Vector2(0.f, 0.f),// Dead
			},
			// right hand
						{
				m::math::Vector2(0.f, 0.f),// Attack1 
				m::math::Vector2(0.f, 0.f),// Attack2 
				m::math::Vector2(0.f, 0.f),// Block 
				m::math::Vector2(60.f, 39.f),// GetHit 
				m::math::Vector2(0.f, 0.f),// Kick 
				m::math::Vector2(60.f, 38.f),// Natural 
				m::math::Vector2(46.f, 40.f),// Run 
				m::math::Vector2(0.f, 0.f),// Special1 
				m::math::Vector2(92.f, 66.f),// SpecialCast 
				m::math::Vector2(0.f, 0.f),// TownNatural 
				m::math::Vector2(0.f, 0.f),// TownWalk 
				m::math::Vector2(0.f, 0.f),// Walk 
				m::math::Vector2(0.f, 0.f),// Dead
			},
		},
		{},
		{
			//head
			{
				m::math::Vector2(0.f, 0.f),// Attack1 
				m::math::Vector2(0.f, 0.f),// Attack2 
				m::math::Vector2(0.f, 0.f),// Block 
				m::math::Vector2(43.f, 35.f),// GetHit 
				m::math::Vector2(0.f, 0.f),// Kick 
				m::math::Vector2(35.f, 30.f),// Natural 
				m::math::Vector2(30.f, 31.f),// Run 
				m::math::Vector2(0.f, 0.f),// Special1 
				m::math::Vector2(42.f, 36.f),// SpecialCast 
				m::math::Vector2(0.f, 0.f),// TownNatural 
				m::math::Vector2(0.f, 0.f),// TownWalk 
				m::math::Vector2(0.f, 0.f),// Walk 
				m::math::Vector2(0.f, 0.f),// Dead
			},
			// left arm
						{
				m::math::Vector2(0.f, 0.f),// Attack1 
				m::math::Vector2(0.f, 0.f),// Attack2 
				m::math::Vector2(0.f, 0.f),// Block 
				m::math::Vector2(0.f, 0.f),// GetHit 
				m::math::Vector2(0.f, 0.f),// Kick 
				m::math::Vector2(0.f, 0.f),// Natural 
				m::math::Vector2(0.f, 0.f),// Run 
				m::math::Vector2(0.f, 0.f),// Special1 
				m::math::Vector2(0.f, 0.f),// SpecialCast 
				m::math::Vector2(0.f, 0.f),// TownNatural 
				m::math::Vector2(0.f, 0.f),// TownWalk 
				m::math::Vector2(0.f, 0.f),// Walk 
				m::math::Vector2(0.f, 0.f),// Dead
			},
			// right arm
						{
				m::math::Vector2(0.f, 0.f),// Attack1 
				m::math::Vector2(0.f, 0.f),// Attack2 
				m::math::Vector2(0.f, 0.f),// Block 
				m::math::Vector2(0, 0),// GetHit 
				m::math::Vector2(0.f, 0.f),// Kick 
				m::math::Vector2(0, 0),// Natural 
				m::math::Vector2(0, 0),// Run 
				m::math::Vector2(0.f, 0.f),// Special1 
				m::math::Vector2(0, 0),// SpecialCast 
				m::math::Vector2(0.f, 0.f),// TownNatural 
				m::math::Vector2(0.f, 0.f),// TownWalk 
				m::math::Vector2(0.f, 0.f),// Walk 
				m::math::Vector2(0.f, 0.f),// Dead
			},
			// body
						{
				m::math::Vector2(0.f, 0.f),// Attack1 
				m::math::Vector2(0.f, 0.f),// Attack2 
				m::math::Vector2(0.f, 0.f),// Block 
				m::math::Vector2(0, 0),// GetHit 
				m::math::Vector2(0.f, 0.f),// Kick 
				m::math::Vector2(0, 0),// Natural 
				m::math::Vector2(0, 0),// Run 
				m::math::Vector2(0.f, 0.f),// Special1 
				m::math::Vector2(0, 0),// SpecialCast 
				m::math::Vector2(0.f, 0.f),// TownNatural 
				m::math::Vector2(0.f, 0.f),// TownWalk 
				m::math::Vector2(0.f, 0.f),// Walk 
				m::math::Vector2(0.f, 0.f),// Dead
			},
			// leg
						{
				m::math::Vector2(0.f, 0.f),// Attack1 
				m::math::Vector2(0.f, 0.f),// Attack2 
				m::math::Vector2(0.f, 0.f),// Block 
				m::math::Vector2(0.f, 0.f),// GetHit 
				m::math::Vector2(0.f, 0.f),// Kick 
				m::math::Vector2(0.f, 0.f),// Natural 
				m::math::Vector2(0.f, 0.f),// Run 
				m::math::Vector2(0.f, 0.f),// Special1 
				m::math::Vector2(0.f, 0.f),// SpecialCast 
				m::math::Vector2(0.f, 0.f),// TownNatural 
				m::math::Vector2(0.f, 0.f),// TownWalk 
				m::math::Vector2(0.f, 0.f),// Walk 
				m::math::Vector2(0.f, 0.f),// Dead
			},
			// right hand
						{
				m::math::Vector2(0.f, 0.f),// Attack1 
				m::math::Vector2(0.f, 0.f),// Attack2 
				m::math::Vector2(0.f, 0.f),// Block 
				m::math::Vector2(0, 0),// GetHit 
				m::math::Vector2(0.f, 0.f),// Kick 
				m::math::Vector2(0, 0),// Natural 
				m::math::Vector2(0, 0),// Run 
				m::math::Vector2(0.f, 0.f),// Special1 
				m::math::Vector2(0, 0),// SpecialCast 
				m::math::Vector2(0.f, 0.f),// TownNatural 
				m::math::Vector2(0.f, 0.f),// TownWalk 
				m::math::Vector2(0.f, 0.f),// Walk 
				m::math::Vector2(0.f, 0.f),// Dead
			},
		},

	};
	m::math::Vector2 itemAnimCenterPos[(int)eItem::END][6][13] = {
			{},
		{},
		{
			//head
			{
				m::math::Vector2(0.f, 0.f),// Attack1 
				m::math::Vector2(0.f, 0.f),// Attack2 
				m::math::Vector2(0.f, 0.f),// Block 
				m::math::Vector2(0.f, 0.f),// GetHit 
				m::math::Vector2(0.f, 0.f),// Kick 
				m::math::Vector2(0.f, 0.f),// Natural 
				m::math::Vector2(0.f, 0.f),// Run 
				m::math::Vector2(0.f, 0.f),// Special1 
				m::math::Vector2(0.f, 0.f),// SpecialCast 
				m::math::Vector2(0.f, 0.f),// TownNatural 
				m::math::Vector2(0.f, 0.f),// TownWalk 
				m::math::Vector2(0.f, 0.f),// Walk 
				m::math::Vector2(0.f, 0.f),// Dead
			},
			// left arm
						{
				m::math::Vector2(0.f, 0.f),// Attack1 
				m::math::Vector2(0.f, 0.f),// Attack2 
				m::math::Vector2(0.f, 0.f),// Block 
				m::math::Vector2(0.f, 0.f),// GetHit 
				m::math::Vector2(0.f, 0.f),// Kick 
				m::math::Vector2(0.f, 0.f),// Natural 
				m::math::Vector2(0.f, 0.f),// Run 
				m::math::Vector2(0.f, 0.f),// Special1 
				m::math::Vector2(0.f, 0.f),// SpecialCast 
				m::math::Vector2(0.f, 0.f),// TownNatural 
				m::math::Vector2(0.f, 0.f),// TownWalk 
				m::math::Vector2(0.f, 0.f),// Walk 
				m::math::Vector2(0.f, 0.f),// Dead
			},
			// right arm
						{
				m::math::Vector2(0.f, 0.f),// Attack1 
				m::math::Vector2(0.f, 0.f),// Attack2 
				m::math::Vector2(0.f, 0.f),// Block 
			    m::math::Vector2(0.f, 27.f), // gethit
			    m::math::Vector2(0.f, 0.f), //
			    m::math::Vector2(0.f, 27.f), // natural
			    m::math::Vector2(0.f, 27.f), // run
			    m::math::Vector2(0.f, 0.f), //
			    m::math::Vector2(0.f, 40.f), // special cast
				m::math::Vector2(0.f, 0.f),// TownNatural 
				m::math::Vector2(0.f, 0.f),// TownWalk 
				m::math::Vector2(0.f, 0.f),// Walk 
				m::math::Vector2(0.f, 0.f),// Dead
			},
			// body
						{
				m::math::Vector2(0.f, 0.f),// Attack1 
				m::math::Vector2(0.f, 0.f),// Attack2 
				m::math::Vector2(0.f, 0.f),// Block 
				m::math::Vector2(0.f, 0.f),// GetHit 
				m::math::Vector2(0.f, 0.f),// Kick 
				m::math::Vector2(0.f, 0.f),// Natural 
				m::math::Vector2(0.f, 0.f),// Run 
				m::math::Vector2(0.f, 0.f),// Special1 
				m::math::Vector2(0.f, 0.f),// SpecialCast 
				m::math::Vector2(0.f, 0.f),// TownNatural 
				m::math::Vector2(0.f, 0.f),// TownWalk 
				m::math::Vector2(0.f, 0.f),// Walk 
				m::math::Vector2(0.f, 0.f),// Dead
			},
			// leg
						{
				m::math::Vector2(0.f, 0.f),// Attack1 
				m::math::Vector2(0.f, 0.f),// Attack2 
				m::math::Vector2(0.f, 0.f),// Block 
				m::math::Vector2(0.f, 0.f),// GetHit 
				m::math::Vector2(0.f, 0.f),// Kick 
				m::math::Vector2(0.f, 0.f),// Natural 
				m::math::Vector2(0.f, 0.f),// Run 
				m::math::Vector2(0.f, 0.f),// Special1 
				m::math::Vector2(0.f, 0.f),// SpecialCast 
				m::math::Vector2(0.f, 0.f),// TownNatural 
				m::math::Vector2(0.f, 0.f),// TownWalk 
				m::math::Vector2(0.f, 0.f),// Walk 
				m::math::Vector2(0.f, 0.f),// Dead
			},
			// right hand
						{
				m::math::Vector2(0.f, 0.f),// Attack1 
				m::math::Vector2(0.f, 0.f),// Attack2 
				m::math::Vector2(0.f, 0.f),// Block 
			    m::math::Vector2(0.f, 25.f), // gethit
			    m::math::Vector2(0.f, 0.f), //
			    m::math::Vector2(0.f, 25.f), // natural
			    m::math::Vector2(0.f, 25.f), // run
			    m::math::Vector2(0.f, 0.f), //
			    m::math::Vector2(0.f, 25.f), // special cast
				m::math::Vector2(0.f, 0.f),// TownNatural 
				m::math::Vector2(0.f, 0.f),// TownWalk 
				m::math::Vector2(0.f, 0.f),// Walk 
				m::math::Vector2(0.f, 0.f),// Dead
			},
		},
		{},
		{
			            {
	            m::math::Vector2(0.f, 0.f), //
	            m::math::Vector2(0.f, 0.f), //
	            m::math::Vector2(0.f, 0.f), //
	            m::math::Vector2(0.f, 39.f), // gethit
	            m::math::Vector2(0.f, 0.f), //
	            m::math::Vector2(0.f, 39.f), // natural
	            m::math::Vector2(0.f, 41.f), // run
	            m::math::Vector2(0.f, 0.f), //
	            m::math::Vector2(0.f, 39.f), // special cast
	            m::math::Vector2(0.f, 0.f), //
	            m::math::Vector2(0.f, 0.f), //
	            m::math::Vector2(0.f, 0.f), //
	            m::math::Vector2(0.f, 0.f), //
	            },
									{
				m::math::Vector2(0.f, 0.f),// Attack1 
				m::math::Vector2(0.f, 0.f),// Attack2 
				m::math::Vector2(0.f, 0.f),// Block 
				m::math::Vector2(0.f, 0.f),// GetHit 
				m::math::Vector2(0.f, 0.f),// Kick 
				m::math::Vector2(0.f, 0.f),// Natural 
				m::math::Vector2(0.f, 0.f),// Run 
				m::math::Vector2(0.f, 0.f),// Special1 
				m::math::Vector2(0.f, 0.f),// SpecialCast 
				m::math::Vector2(0.f, 0.f),// TownNatural 
				m::math::Vector2(0.f, 0.f),// TownWalk 
				m::math::Vector2(0.f, 0.f),// Walk 
				m::math::Vector2(0.f, 0.f),// Dead
			    },
									{
				m::math::Vector2(0.f, 0.f),// Attack1 
				m::math::Vector2(0.f, 0.f),// Attack2 
				m::math::Vector2(0.f, 0.f),// Block 
				m::math::Vector2(0.f, 0.f),// GetHit 
				m::math::Vector2(0.f, 0.f),// Kick 
				m::math::Vector2(0.f, 0.f),// Natural 
				m::math::Vector2(0.f, 0.f),// Run 
				m::math::Vector2(0.f, 0.f),// Special1 
				m::math::Vector2(0.f, 0.f),// SpecialCast 
				m::math::Vector2(0.f, 0.f),// TownNatural 
				m::math::Vector2(0.f, 0.f),// TownWalk 
				m::math::Vector2(0.f, 0.f),// Walk 
				m::math::Vector2(0.f, 0.f),// Dead
			    },
									{
				m::math::Vector2(0.f, 0.f),// Attack1 
				m::math::Vector2(0.f, 0.f),// Attack2 
				m::math::Vector2(0.f, 0.f),// Block 
				m::math::Vector2(0.f, 0.f),// GetHit 
				m::math::Vector2(0.f, 0.f),// Kick 
				m::math::Vector2(0.f, 0.f),// Natural 
				m::math::Vector2(0.f, 0.f),// Run 
				m::math::Vector2(0.f, 0.f),// Special1 
				m::math::Vector2(0.f, 0.f),// SpecialCast 
				m::math::Vector2(0.f, 0.f),// TownNatural 
				m::math::Vector2(0.f, 0.f),// TownWalk 
				m::math::Vector2(0.f, 0.f),// Walk 
				m::math::Vector2(0.f, 0.f),// Dead
			    },
									{
				m::math::Vector2(0.f, 0.f),// Attack1 
				m::math::Vector2(0.f, 0.f),// Attack2 
				m::math::Vector2(0.f, 0.f),// Block 
				m::math::Vector2(0.f, 0.f),// GetHit 
				m::math::Vector2(0.f, 0.f),// Kick 
				m::math::Vector2(0.f, 0.f),// Natural 
				m::math::Vector2(0.f, 0.f),// Run 
				m::math::Vector2(0.f, 0.f),// Special1 
				m::math::Vector2(0.f, 0.f),// SpecialCast 
				m::math::Vector2(0.f, 0.f),// TownNatural 
				m::math::Vector2(0.f, 0.f),// TownWalk 
				m::math::Vector2(0.f, 0.f),// Walk 
				m::math::Vector2(0.f, 0.f),// Dead
			    },
									{
				m::math::Vector2(0.f, 0.f),// Attack1 
				m::math::Vector2(0.f, 0.f),// Attack2 
				m::math::Vector2(0.f, 0.f),// Block 
				m::math::Vector2(0.f, 0.f),// GetHit 
				m::math::Vector2(0.f, 0.f),// Kick 
				m::math::Vector2(0.f, 0.f),// Natural 
				m::math::Vector2(0.f, 0.f),// Run 
				m::math::Vector2(0.f, 0.f),// Special1 
				m::math::Vector2(0.f, 0.f),// SpecialCast 
				m::math::Vector2(0.f, 0.f),// TownNatural 
				m::math::Vector2(0.f, 0.f),// TownWalk 
				m::math::Vector2(0.f, 0.f),// Walk 
				m::math::Vector2(0.f, 0.f),// Dead
			},
		},
	};

	eItemType itemTypeTable[(int)eItem::END] = {
		eItemType::Posion,
		eItemType::Posion,

		eItemType::RightWeapon,

		eItemType::Armor,

		eItemType::Helmet,

	};
	m::math::Vector2 itemFieldAnimSpaceTable[(int)eItem::END] = {
		{20.f, 159.f}
		,{20.f, 159.f}
		,{37.f, 153.f}
		,{38.f, 173.f}
		,{21.f, 149.f}
	};
	//float itemFieldSpaceTable[(int)eItem::END][2] = {

	//};
	// 28.f, 28.f = one inven = 1.f, 1.f
	float itemInvenDisplayScale[(int)eItem::END][2] = {
		{1.f, 1.f},
		{1.f, 1.f},

		{1.f, 3.f},
		{2.f, 4.f},

		{2.f, 2.f},
	};
	// posion = 0 ��� 1 ȸ����
	// weapon = 0 ��� 1 ������ 2 ���밡���� ����
	// armor = 0 ��� 1 ��� 2 ���밡���� ����
	int itemFunctionValue[(int)eItem::END][4] = {
		{25,30,0,0},
		{50, 40,0,0},

		{120,50,1,0},

		{200,10,1,0},

		{100,5,1,0},
	};

	std::wstring itemCostFunctionNames[(int)eItem::END][5] = {
		{L"�̷��� ��������", L"���: ",L"ȸ����: ",L"",L""},
		{L"�̷��� ��������", L"���: ",L"ȸ����: ",L"",L""},

		{L"�ڷ��� ����", L"���: ",L"������: ",L"���� ������ ����: ",L""},

		{L"���� �Ƹ�", L"���: ",L"���: ",L"���� ������ ����: ",L""},

		{L"ĸ", L"���: ",L"���: ",L"���� ������ ����: ",L""},
	};


}
