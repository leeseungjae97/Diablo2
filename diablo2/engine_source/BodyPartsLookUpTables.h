#pragma once


enum class eBodyPartsType
{
    Head,
	LeftArm,
	RightArm,
	Body,
	Leg,
	RightHand,
	End
};
static m::math::Vector2 bodyPartsOffset[(int)eBodyPartsType::End][13] = {
	// head
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
	// left arm
		{
			m::math::Vector2(0.f, 0.f), //
			m::math::Vector2(0.f, 0.f), //
			m::math::Vector2(0.f, 0.f), //
			m::math::Vector2(0.f, 27.f), // gethit
			m::math::Vector2(0.f, 0.f), //
			m::math::Vector2(0.f, 27.f), // natural
			m::math::Vector2(0.f, 27.f), // run
			m::math::Vector2(0.f, 0.f), //
			m::math::Vector2(0.f, 40.f), // special cast
			m::math::Vector2(0.f, 0.f), //
			m::math::Vector2(0.f, 0.f), //
			m::math::Vector2(0.f, 0.f), //
			m::math::Vector2(0.f, 0.f), //
	},
	// right arm
		{
			m::math::Vector2(0.f, 0.f), //
			m::math::Vector2(0.f, 0.f), //
			m::math::Vector2(0.f, 0.f), //
			m::math::Vector2(0.f, 27.f), // gethit
			m::math::Vector2(0.f, 0.f), //
			m::math::Vector2(0.f, 27.f), // natural
			m::math::Vector2(0.f, 27.f), // run
			m::math::Vector2(0.f, 0.f), //
			m::math::Vector2(0.f, 40.f), // special cast
			m::math::Vector2(0.f, 0.f), //
			m::math::Vector2(0.f, 0.f), //
			m::math::Vector2(0.f, 0.f), //
			m::math::Vector2(0.f, 0.f), //
	}, // upper body
		{
			m::math::Vector2(0.f, 0.f), //
			m::math::Vector2(0.f, 0.f), //
			m::math::Vector2(0.f, 0.f), //
			m::math::Vector2(0.f, 35.f), // gethit
			m::math::Vector2(0.f, 0.f), //
			m::math::Vector2(0.f, 35.f), // natural
			m::math::Vector2(0.f, 35.f), // run
			m::math::Vector2(0.f, 0.f), //
			m::math::Vector2(0.f, 35.f), // special cast
			m::math::Vector2(0.f, 0.f), //
			m::math::Vector2(0.f, 0.f), //
			m::math::Vector2(0.f, 0.f), //
			m::math::Vector2(0.f, 0.f), //
	}, //leg
		{
			m::math::Vector2(0.f, 0.f), //
			m::math::Vector2(0.f, 0.f), //
			m::math::Vector2(0.f, 0.f), //
			m::math::Vector2(0.f, 5.f), // gethit
			m::math::Vector2(0.f, 0.f), //
			m::math::Vector2(0.f, 5.f), // natural
			m::math::Vector2(0.f, 5.f), // run
			m::math::Vector2(0.f, 0.f), //
			m::math::Vector2(0.f, 5.f), // special cast
			m::math::Vector2(0.f, 0.f), //
			m::math::Vector2(0.f, 0.f), //
			m::math::Vector2(0.f, 0.f), //
			m::math::Vector2(0.f, 0.f), //
	},// orb right arm
		{
			m::math::Vector2(0.f, 0.f), //
			m::math::Vector2(0.f, 0.f), //
			m::math::Vector2(0.f, 0.f), //
			m::math::Vector2(0.f, 0.f), // gethit
			m::math::Vector2(0.f, 0.f), //
			m::math::Vector2(0.f, 0.f), // natural
			m::math::Vector2(0.f, 0.f), // run
			m::math::Vector2(0.f, 0.f), //
			m::math::Vector2(0.f, 0.f), // special cast
			m::math::Vector2(0.f, 0.f), //
			m::math::Vector2(0.f, 0.f), //
			m::math::Vector2(0.f, 0.f), //
			m::math::Vector2(0.f, 0.f), //
	},
};
static m::math::Vector2 bodyPartsShadowOffset[(int)eBodyPartsType::End][13] = {
	// head
	{
	m::math::Vector2(0.f, 0.f), //
	m::math::Vector2(0.f, 0.f), //
	m::math::Vector2(0.f, 0.f), //
	m::math::Vector2(-10.f, -15.5f), // gethit
	m::math::Vector2(0.f, 0.f), //
	m::math::Vector2(-10.f, -15.5f), // natural
	m::math::Vector2(-25.f, -18.f), // run
	m::math::Vector2(0.f, 0.f), //
	m::math::Vector2(-10.f, -15.5f), // special cast
	m::math::Vector2(0.f, 0.f), //
	m::math::Vector2(0.f, 0.f), //
	m::math::Vector2(0.f, 0.f), //
	m::math::Vector2(0.f, 0.f), //
	},
	// left arm
		{
			m::math::Vector2(0.f, 0.f), //
			m::math::Vector2(0.f, 0.f), //
			m::math::Vector2(0.f, 0.f), //
			m::math::Vector2(-7.f, -10.f), // gethit
			m::math::Vector2(0.f, 0.f), //
			m::math::Vector2(-7.f, -10.f), // natural
			m::math::Vector2(-13.f, -10.f), // run
			m::math::Vector2(0.f, 0.f), //
			m::math::Vector2(-5.f, -8.f), // special cast
			m::math::Vector2(0.f, 0.f), //
			m::math::Vector2(0.f, 0.f), //
			m::math::Vector2(0.f, 0.f), //
			m::math::Vector2(0.f, 0.f), //
	},
	// right arm
		{
			m::math::Vector2(0.f, 0.f), //
			m::math::Vector2(0.f, 0.f), //
			m::math::Vector2(0.f, 0.f), //
			m::math::Vector2(-5.f, -10.f), // gethit
			m::math::Vector2(0.f, 0.f), //
			m::math::Vector2(-5.f, -10.f), // natural
			m::math::Vector2(-12.f, -10.f), // run
			m::math::Vector2(0.f, 0.f), //
			m::math::Vector2(-5.f, -8.f), // special cast
			m::math::Vector2(0.f, 0.f), //
			m::math::Vector2(0.f, 0.f), //
			m::math::Vector2(0.f, 0.f), //
			m::math::Vector2(0.f, 0.f), //
	}, // upper body
			{
	m::math::Vector2(0.f, 0.f), //
	m::math::Vector2(0.f, 0.f), //
	m::math::Vector2(0.f, 0.f), //
	m::math::Vector2(-14.f, -15.5f), // gethit
	m::math::Vector2(0.f, 0.f), //
	m::math::Vector2(-14.f, -15.5f), // natural
	m::math::Vector2(-27.f, -16.5f), // run
	m::math::Vector2(0.f, 0.f), //
	m::math::Vector2(-15.f, -15.5f), // special cast
	m::math::Vector2(0.f, 0.f), //
	m::math::Vector2(0.f, 0.f), //
	m::math::Vector2(0.f, 0.f), //
	m::math::Vector2(0.f, 0.f), //
	},//leg
		{
			m::math::Vector2(0.f, 0.f), //
			m::math::Vector2(0.f, 0.f), //
			m::math::Vector2(0.f, 0.f), //
			m::math::Vector2(0.f, 5.f), // gethit
			m::math::Vector2(0.f, 0.f), //
			m::math::Vector2(0.f, 5.f), // natural
			m::math::Vector2(0.f, 5.f), // run
			m::math::Vector2(0.f, 0.f), //
			m::math::Vector2(0.f, 5.f), // special cast
			m::math::Vector2(0.f, 0.f), //
			m::math::Vector2(0.f, 0.f), //
			m::math::Vector2(0.f, 0.f), //
			m::math::Vector2(0.f, 0.f), //
	},// orb right arm
		{
			m::math::Vector2(0.f, 0.f), //
			m::math::Vector2(0.f, 0.f), //
			m::math::Vector2(0.f, 0.f), //
			m::math::Vector2(0.f, 0.f), // gethit
			m::math::Vector2(0.f, 0.f), //
			m::math::Vector2(0.f, 0.f), // natural
			m::math::Vector2(0.f, 0.f), // run
			m::math::Vector2(0.f, 0.f), //
			m::math::Vector2(0.f, 0.f), // special cast
			m::math::Vector2(0.f, 0.f), //
			m::math::Vector2(0.f, 0.f), //
			m::math::Vector2(0.f, 0.f), //
			m::math::Vector2(0.f, 0.f), //
	},
};
//// orb right arm
//{
//	L"",// Attack1 
//		L"",// Attack2 
//		L"",// Block 
//		L"ob_ra_gh",// GetHit 
//		L"",// Kick 
//		L"ob_ra_nu",// Natural 
//		L"ob_ra_r",// Run 
//		L"",// Special1 
//		L"ob_ra_sc",// SpecialCast 
//		L"",// TownNatural 
//		L"",// TownWalk 
//		L"",// Walk 
//		L"",// Dead 
//},
//// weapon orb
//	{
//			L"",// Attack1 
//	L"",// Attack2 
//	L"",// Block 
//	L"ob_gh",// GetHit 
//	L"",// Kick 
//	L"ob_nu",// Natural 
//	L"ob_r",// Run 
//	L"",// Special1 
//	L"ob_sc",// SpecialCast 
//	L"",// TownNatural 
//	L"",// TownWalk 
//	L"",// Walk 
//	L"",// Dead 
//	}
static std::wstring partsMaterialNames[(int)eBodyPartsType::End][13] = {
	// head
	{
		L"",// Attack1 
		L"",// Attack2 
		L"",// Block 
		L"hdGH",// GetHit 
		L"",// Kick 
		L"hdNU",// Natural 
		L"hdR",// Run 
		L"",// Special1 
		L"hdSC",// SpecialCast 
		L"",// TownNatural 
		L"",// TownWalk 
		L"",// Walk 
		L"",// Dead 
	},
	// left arm
{
	L"",// Attack1 
	L"",// Attack2 
	L"",// Block 
	L"laGH",// GetHit 
	L"",// Kick 
	L"laNU",// Natural 
	L"laR",// Run 
	L"",// Special1 
	L"laSC",// SpecialCast 
	L"",// TownNatural 
	L"",// TownWalk 
	L"",// Walk 
	L"",// Dead 
},
// right arm
{
	L"",// Attack1 
	L"",// Attack2 
	L"",// Block 
	L"raGH",// GetHit 
	L"",// Kick 
	L"raNU",// Natural 
	L"raR",// Run 
	L"",// Special1 
	L"raSC",// SpecialCast 
	L"",// TownNatural 
	L"",// TownWalk 
	L"",// Walk 
	L"",// Dead 
},
// upper body
{
	L"", // Attack1 
	L"", // Attack2 
	L"", // Block 
	L"trGH", // GetHit 
	L"", // Kick 
	L"trNU", // Natural 
	L"trR", // Run 
	L"", // Special1 
	L"trSC", // SpecialCast 
	L"", // TownNatural 
	L"", // TownWalk 
	L"", // Walk 
	L"", // Dead 
},
// leg
{
	L"",// Attack1 
	L"",// Attack2 
	L"",// Block 
	L"lgGH",// GetHit 
	L"",// Kick 
	L"lgNU",// Natural 
	L"lgR",// Run 
	L"",// Special1 
	L"lgSC",// SpecialCast 
	L"",// TownNatural 
	L"",// TownWalk 
	L"",// Walk 
	L"",// Dead 
},
};

static m::math::Vector2 partsSizes[(int)eBodyPartsType::End][13] = {
	{
		m::math::Vector2(0.f,0.f), // Attack1 
		m::math::Vector2(0.f,0.f), // Attack2 
		m::math::Vector2(0.f,0.f), // Block 
		m::math::Vector2(44.f,34.f), // GetHit 
		m::math::Vector2(0.f,0.f), // Kick 
		m::math::Vector2(35.f,30.f), // Natural 
		m::math::Vector2(32.f,30.f), // Run 
		m::math::Vector2(0.f,0.f), // Special1 
		m::math::Vector2(43.f,35.f), // SpecialCast 
		m::math::Vector2(0.f,0.f), // TownNatural 
		m::math::Vector2(0.f, 0.f), // TownWalk 
		m::math::Vector2(0.f, 0.f), // Walk 
		m::math::Vector2(0.f, 0.f), // Dead 
	},
		{
		m::math::Vector2(0.f,0.f), // Attack1 
		m::math::Vector2(0.f,0.f), // Attack2 
		m::math::Vector2(0.f,0.f), // Block 
		m::math::Vector2(34.f,35.f), // GetHit 
		m::math::Vector2(0.f,0.f), // Kick 
		m::math::Vector2(30.f,32.f), // Natural 
		m::math::Vector2(54.f,35.f), // Run 
		m::math::Vector2(0.f,0.f), // Special1 
		m::math::Vector2(85.f,62.f), // SpecialCast 
		m::math::Vector2(0.f,0.f), // TownNatural 
		m::math::Vector2(0.f, 0.f), // TownWalk 
		m::math::Vector2(0.f, 0.f), // Walk 
		m::math::Vector2(0.f, 0.f), // Dead 
	},
		{
		m::math::Vector2(0.f,0.f), // Attack1 
		m::math::Vector2(0.f,0.f), // Attack2 
		m::math::Vector2(0.f,0.f), // Block 
		m::math::Vector2(34.f,35.f), // GetHit 
		m::math::Vector2(0.f,0.f), // Kick 
		m::math::Vector2(30.f,34.f), // Natural 
		m::math::Vector2(50.f,33.f), // Run 
		m::math::Vector2(0.f,0.f), // Special1 
		m::math::Vector2(84.f,64.f), // SpecialCast 
		m::math::Vector2(0.f,0.f), // TownNatural 
		m::math::Vector2(0.f, 0.f), // TownWalk 
		m::math::Vector2(0.f, 0.f), // Walk 
		m::math::Vector2(0.f, 0.f), // Dead 
	},
		{
		m::math::Vector2(0.f,0.f), // Attack1 
		m::math::Vector2(0.f,0.f), // Attack2 
		m::math::Vector2(0.f,0.f), // Block 
		m::math::Vector2(24.f,26.f), // GetHit 
		m::math::Vector2(0.f,0.f), // Kick 
		m::math::Vector2(16.f,24.f), // Natural 
		m::math::Vector2(20.f,28.f), // Run 
		m::math::Vector2(0.f,0.f), // Special1 
		m::math::Vector2(30.f,29.f), // SpecialCast 
		m::math::Vector2(0.f,0.f), // TownNatural 
		m::math::Vector2(0.f, 0.f), // TownWalk 
		m::math::Vector2(0.f, 0.f), // Walk 
		m::math::Vector2(0.f, 0.f), // Dead 
	},
		{
			m::math::Vector2(0.f, 0.f), //
			m::math::Vector2(0.f, 0.f), //
			m::math::Vector2(0.f, 0.f), //
			m::math::Vector2(38.f, 50.f), // gethit
			m::math::Vector2(0.f, 0.f), //
			m::math::Vector2(30.f, 50.f), // natural
			m::math::Vector2(61.f, 52.f), // run
			m::math::Vector2(0.f, 0.f), //
			m::math::Vector2(30.f, 51.f), // special cast
			m::math::Vector2(0.f, 0.f), //
			m::math::Vector2(0.f, 0.f), //
			m::math::Vector2(0.f, 0.f), //
			m::math::Vector2(0.f, 0.f), //
	},
		{
		m::math::Vector2(0.f,0.f), // Attack1 
		m::math::Vector2(0.f,0.f), // Attack2 
		m::math::Vector2(0.f,0.f), // Block 
		m::math::Vector2(0.f,0.f), // GetHit 
		m::math::Vector2(0.f,0.f), // Kick 
		m::math::Vector2(0.f,0.f), // Natural 
		m::math::Vector2(0.f,0.f), // Run 
		m::math::Vector2(0.f,0.f), // Special1 
		m::math::Vector2(0.f,0.f), // SpecialCast 
		m::math::Vector2(0.f,0.f), // TownNatural 
		m::math::Vector2(0.f, 0.f), // TownWalk 
		m::math::Vector2(0.f, 0.f), // Walk 
		m::math::Vector2(0.f, 0.f), // Dead 
	},

};

static m::math::Vector2 partsCenterPos[(int)eBodyPartsType::End][13] = {
};

static int partsLength[13] = {
	0,// Attack1 
    0,// Attack2 
    0,// Block 
    8,// GetHit 
    0,// Kick 
    8,// Natural 
    8,// Run 
    0,// Special1 
    14,// SpecialCast 
    0,// TownNatural 
    0,// TownWalk 
    0,// Walk 
    0,// Dead
};


static float partsDuration[13] = {
	0.05f, // Attack1 
	0.03f, // Attack2 
	0.03f, // Block 
	0.05f, // GetHit 
	0.03f, // Kick 
	0.1f, // Natural 
	0.1f, // Run 
	0.03f, // Special1 
	0.03f, // SpecialCast 
	0.03f, // TownNatural 
	0.03f, // TownWalk 
	0.03f, // Walk 
	0.03f, // Dead
};

static std::wstring partsShadowNames[(int)eBodyPartsType::End][13] = {
	{
		L"",// Attack1 
		L"",// Attack2 
		L"",// Block 
		L"hdGHS",// GetHit 
		L"",// Kick 
		L"hdNUS",// Natural 
		L"hdRS",// Run 
		L"",// Special1 
		L"hdSCS",// SpecialCast 
		L"",// TownNatural 
		L"",// TownWalk 
		L"",// Walk 
		L"",// Dead 
	},
	{
	L"",// Attack1 
	L"",// Attack2 
	L"",// Block 
	L"laGHS",// GetHit 
	L"",// Kick 
	L"laNUS",// Natural 
	L"laRS",// Run 
	L"",// Special1 
	L"laSCS",// SpecialCast 
	L"",// TownNatural 
	L"",// TownWalk 
	L"",// Walk 
	L"",// Dead 
},
// right arm
{
	L"",// Attack1 
	L"",// Attack2 
	L"",// Block 
	L"raGHS",// GetHit 
	L"",// Kick 
	L"raNUS",// Natural 
	L"raRS",// Run 
	L"",// Special1 
	L"raSCS",// SpecialCast 
	L"",// TownNatural 
	L"",// TownWalk 
	L"",// Walk 
	L"",// Dead 
},
// upper body
{
	L"", // Attack1 
	L"", // Attack2 
	L"", // Block 
	L"trGHS", // GetHit 
	L"", // Kick 
	L"trNUS", // Natural 
	L"trRS", // Run 
	L"", // Special1 
	L"trSCS", // SpecialCast 
	L"", // TownNatural 
	L"", // TownWalk 
	L"", // Walk 
	L"", // Dead 
},
// leg
{
	L"",// Attack1 
	L"",// Attack2 
	L"",// Block 
	L"lgGHS",// GetHit 
	L"",// Kick 
	L"lgNUS",// Natural 
	L"lgRS",// Run 
	L"",// Special1 
	L"lgSCS",// SpecialCast 
	L"",// TownNatural 
	L"",// TownWalk 
	L"",// Walk 
	L"",// Dead 
},
};