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
	End,
};

enum class eCharacterDirection
{
	Down,
	LeftDown1,
	LeftDown2,
	LeftDown3,
	LeftDown4,
	LeftDown5,
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
	End
};

m::math::Vector2 sorceressAnimationSizes[(UINT)eSorceressAnimationType::End] = {
	Vector2(2500.f / 20.f, 1263.f / 16.f),
	Vector2(2400.f / 20.f, 1471.f / 16.f),
	Vector2(329.f / 5.f, 1167.f / 16.f),
	Vector2(528.f / 8.f, 1167.f / 16.f),
	Vector2(1248.f / 12.f, 1247.f / 16.f),
	Vector2(528.f / 8.f, 1151.f / 16.f),
	Vector2(488.f / 8.f, 1215.f / 16.f),
	Vector2(1246.f / 14.f, 1467.f / 16.f),
	Vector2(1358.f / 14.f , 1471.f / 16.f),
	Vector2(669.f / 8.f, 1165.f / 16.f),
	Vector2(384.f / 8.f, 1199.f / 16.f),
	Vector2(480.f / 8.f, 1215.f / 16.f),
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
};