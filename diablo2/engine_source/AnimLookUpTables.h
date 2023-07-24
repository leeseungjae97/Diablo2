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

#define NATURAL sorceressAnimationString[(UINT)eSorceressAnimationType::Natural]