#pragma once

#include "MoveAbleObjectAnimLookUpTables.h"

namespace m
{

	math::Vector2 playerHandSizes[(int)ePlayerAnimationType::End] = {
		math::Vector2(0.f, 0.f),
		math::Vector2(0.f, 0.f),
		math::Vector2(0.f, 0.f),
		math::Vector2(0.f, 0.f),
		math::Vector2(0.f, 0.f),
		math::Vector2(0.f, 0.f),
		math::Vector2(0.f, 0.f),
		math::Vector2(0.f, 0.f),
		math::Vector2(0.f, 0.f),
		math::Vector2(0.f, 0.f),
		math::Vector2(0.f, 0.f),
		math::Vector2(0.f, 0.f),
		math::Vector2(0.f, 0.f),
	};
	int playerHandLength[(int)ePlayerAnimationType::End] = {
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
	};

}