#pragma once
#include "_Engine.h"

#include "../Engine/mEmptyRect.h"

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

		template <typename T>
		void AddItem(T* item);

		template <typename T>
		void EraseItem(T* item);

	private:
		static Camera* mCurCamera;
		static std::vector<Stash> stashPositions;
		static EmptyRect* invensCollider;
		static std::vector<EmptyRect*> invens;
		static std::vector<EmptyRect*> equiments;
		static std::vector<InvenItem*> invenItems;

		//std::vector<PocketItem*>
		
	};
}


