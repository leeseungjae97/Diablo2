#pragma once
#include "_Engine.h"

namespace m
{
	class Monster;
	class MonsterManager
	{
	public:
		static void AddMonster(Monster* monster) { monsters.push_back(monster); }
		static Monster* GetMonster(float monsterId);
		static void ClearMonster();
		static float DispendMonsterId();
		static std::vector<Monster*> monsters;
		static float dispendMonsterId;
	private:
	};
}


