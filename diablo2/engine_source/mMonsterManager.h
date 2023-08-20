#pragma once
#include "_Engine.h"

#include "../Engine/mMonster.h"

namespace m
{
	class Monster;
	class MonsterManager
	{
	public:
		static void AddMonster(Monster* monster)
		{
			monsters.push_back(monster);
			monster->SetMonsterId(monsters.size() - 1);
		}
		static void EraseMonster(Monster* monster);
		static Monster* GetMonster(int monsterId) { return monsters[monsterId]; }
		static void ClearMonster();
		static std::vector<Monster*> monsters;
	private:
	};
}


