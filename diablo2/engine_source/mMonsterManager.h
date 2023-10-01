#pragma once
#include "_Engine.h"

#include "../Engine/mMonster.h"

namespace m
{
	class Monster;
	class MonsterManager
	{
	public:
		static void AddMonster(Monster* monster);
        static void AddDeadMonster(Monster* monster);
        static void EraseDeadMonster();
        static void EraseMonster(Monster* monster);
		static void EraseAll();
		static Monster* GetMonster(int monsterId);
		static void ClearMonster();
		static std::vector<Monster*> monsters;
		static std::vector<Monster*> deadMonsters;
	private:
	};
}


