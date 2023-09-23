#include "mMonsterManager.h"

#include "../Engine/mMonster.h"

namespace m
{
	std::vector<Monster*> MonsterManager::monsters = {};

    void MonsterManager::AddMonster(Monster* monster)
    {
		monsters.push_back(monster);
		monster->SetMonsterId(monsters.size() - 1);
    }

	void MonsterManager::EraseMonster(Monster* monster)
	{
		auto iter = monsters.begin();
		int eraseMonsterId = monster->GetMonsterId();
		while(iter != monsters.end())
		{
			if((*iter) == monster) iter = monsters.erase(iter);
			else ++iter;
		}
		for(int i = eraseMonsterId; i < monsters.size(); ++i)
		{
			monsters[i]->SetMonsterId(eraseMonsterId);
			++eraseMonsterId;
		}
	}

    Monster* MonsterManager::GetMonster(int monsterId)
    {
		if(monsters.size() <= monsterId) return nullptr;

		return monsters[monsterId];
    }

    void MonsterManager::ClearMonster()
	{
		if (!monsters.empty()) monsters.clear();
	}
}