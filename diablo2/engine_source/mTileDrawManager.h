#pragma once
#include "_Engine.h"

namespace m
{
	class TileDrawSystem;
	class TileDrawManager
	{
	public:
		static void Update();
		static void Add(TileDrawSystem* tds);
		static void EraseAll();
		static void Erase(TileDrawSystem* tds);

		static std::vector<TileDrawSystem*> mtiledrawsystems;

		static bool bDrawTile;
	};
}


