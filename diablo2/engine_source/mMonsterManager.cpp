#include "mMonsterManager.h"

#include "../Engine/mMonster.h"

namespace m
{
	std::vector<Monster*> MonsterManager::monsters = {};

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

	void MonsterManager::ClearMonster()
	{
		if (!monsters.empty()) monsters.clear();
	}
}