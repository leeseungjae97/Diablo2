#pragma once
#include "mMath.h"

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
	L"sorceressTownNatural_anim",
	L"sorceressNatural_anim",
	L"sorceressRun_anim",
	L"sorceressWalk_anim",
	L"sorceressSpecialCast_anim",
	L"sorceressGetHit_anim",
	L"sorceressDead",
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
enum class eMonsterDirection
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
m::math::Vector2 sorceressAnimationSizes[(UINT)eSorceressAnimationType::End] = {
	m::math::Vector2(2500.f / 20.f, 1263.f / 16.f),		// Attack1
	m::math::Vector2(2400.f / 20.f, 1471.f / 16.f),		// Attack2
	m::math::Vector2(329.f / 5.f, 1167.f / 16.f),		// Block
	m::math::Vector2(528.f / 8.f, 1167.f / 16.f),		// GetHit
	m::math::Vector2(1248.f / 12.f, 1247.f / 16.f),		// Kick
	m::math::Vector2(528.f / 8.f, 1151.f / 16.f),		// Natural
	m::math::Vector2(488.f / 8.f, 1215.f / 16.f),		// Run
	m::math::Vector2(1246.f / 14.f, 1467.f / 16.f),		// Special1
	m::math::Vector2(1358.f / 14.f , 1471.f / 16.f),	// SpecialCast
	m::math::Vector2(669.f / 8.f, 1165.f / 16.f),		// TownNatural
	m::math::Vector2(384.f / 8.f, 1199.f / 16.f),		// TownWalk
	m::math::Vector2(480.f / 8.f, 1215.f / 16.f),		// Walk
	m::math::Vector2(192.f, 1664.f / 16.f),				// Dead
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
struct Monster {
	enum class eAnimationType {};
	std::wstring animationString[5] = {};
	m::math::Vector2 animationSizes[5] = {};
	std::wstring textureString[5] = {};
	int animationLength[5] = {};
};
struct DiabloSt : public Monster
{
	enum class eAnimationType
	{
		Attack1,
		Attack2,
		Block,
		Hit,
		Natural,
		Run,
		Walk,
		Special_cast,
		Special1,
		Special2,
		Special3,
		Special4,
		Dead,
		End,
	};
	std::wstring textureString[(UINT)eAnimationType::End] = {
		L"diabloNatural",
		L"diabloWalk",
		L"diabloAttack1",
		L"diabloAttack2",
		L"diabloBlock",
		L"diabloHit",
		L"diabloRun",
		L"diabloSpecial_cast",
		L"diabloSpecial1",
		L"diabloSpecial2",
		L"diabloSpecial3",
		L"diabloSpecial4",
		L"diabloDead",
	};
	std::wstring animationString[(UINT)eAnimationType::End] = {
		L"diabloAttack1_anim",
		L"diabloAttack2_anim",
		L"diabloBlock_anim",
		L"diabloHit_anim",
		L"diabloNatural_anim",
		L"diabloRun_anim",
		L"diabloWalk_anim",
		L"diabloSpecialCast_anim",
		L"diabloSpecial1_anim",
		L"diabloSpecial2_anim",
		L"diabloSpecial3_anim",
		L"diabloSpecial4_anim",
		L"diabloDead",
	};
	m::math::Vector2 animationSizes[(UINT)eAnimationType::End] = {
		m::math::Vector2(4960.f / 20.f, 1791.f / 8.f),		// Attack1
		m::math::Vector2(5760.f / 20.f, 2295.f / 8.f),		// Attack2
		m::math::Vector2(2655.f / 9.f, 1551.f / 8.f),		// Block
		m::math::Vector2(1853.f / 6.f, 1767.f / 8.f),		// Hit
		m::math::Vector2(3156.f / 12.f, 1695.f / 8.f),		// Natural
		m::math::Vector2(6798.f / 22.f, 1991.f / 8.f),		// Run
		m::math::Vector2(3516.f / 14.f, 1503.f / 8.f),		// Walk
		m::math::Vector2(4522.f / 17.f , 2055.f / 8.f),	// SpecialCast
		m::math::Vector2(4986.f / 18.f , 1631.f / 8.f),	// Special1
		m::math::Vector2(4608.f / 16.f , 1895.f / 8.f),	// Special2
		m::math::Vector2(4979.f / 16.f , 2183.f / 8.f),	// Special3
		m::math::Vector2(4605.f / 16.f , 1615.f / 8.f),	// Special4
		m::math::Vector2(169.f, 147.f),				// Dead
	};
	int animationLength[(UINT)eAnimationType::End] = {
		16,// Attack1
		16,// Attack2
		9, // Block
		6, // Hit
		12,// Natural
		22, // Run
		12, // Walk
		17,// SpecialCast
		18,// Special1
		16, // Special2
		16, // Special3
		16	, // Special4
		1, // Dead
	};
};
enum class eMonsterType {
	Diablo,
	End,
};
