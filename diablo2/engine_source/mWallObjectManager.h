#pragma once
#include "mGameObject.h"

namespace m
{
	class WallObjectManager
	{
	public:
		static void EraseAll();
		static void Add(GameObject* obj);

		static std::vector<GameObject*> objs;
	};
}

