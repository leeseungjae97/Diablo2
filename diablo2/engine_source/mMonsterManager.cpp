#include "mMonsterManager.h"

#include "../Engine/mMonster.h"

namespace m
{
	std::vector<Monster*> MonsterManager::monsters = {};

	void MonsterManager::EraseMonster(Monster* monster)
	{
		auto iter = monsters.begin();
		int index = 0;
		int eraseMonsterId = monster->GetMonsterId();
		while(iter != monsters.end())
		{
			if((*iter) == monster)
			{
				iter = monsters.erase(iter);
				break;
			}
			else
			{
				++iter;
				++index;
			}
		}
		for(int i = index; i < monsters.size(); ++i)
		{
			monsters[i]->SetMonsterId(eraseMonsterId);
			++eraseMonsterId;
		}
	}

	void MonsterManager::ClearMonster()
	{
		if (!monsters.empty()) monsters.clear();
	}
}