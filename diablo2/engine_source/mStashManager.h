#pragma once
#include "_Engine.h"

#include "../Engine/mItem.h"

namespace m
{
	class StashManager
	{
	public:
		enum class eStashType {
			Invetory,
			PocketInven,
			Shop,
			End
		};
		void StashHover();
		static std::vector<Vector2, eStashType> stashPositions;

	private:
		
	};
}


