#pragma once
#include "_Engine.h"

namespace m
{
	class Camera;
	class Item;
	class StashManager
	{
	public:
		enum class eStashType {
			Invetory,
			PocketInven,
			Shop,
			End
		};
		struct Stash
		{
			Vector2 pos;
			Vector2 size;
			eStashType type;
		};
		static eStashType GetHoverStashType();
		static void AddStash(Vector2 pos, Vector2 size, eStashType type);
		static bool StashItem(Item* item);
		static void SetCamera(Camera* camera) { mCurCamera = camera; }


	private:
		static Camera* mCurCamera;
		static std::vector<Stash> stashPositions;
		
	};
}


