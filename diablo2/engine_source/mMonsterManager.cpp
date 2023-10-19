#include "mMonsterManager.h"

#include "../Engine/mMonster.h"

namespace m
{
	std::vector<Monster*> MonsterManager::monsters = {};
	std::vector<Monster*> MonsterManager::deadMonsters = {};

    void MonsterManager::AddMonster(Monster* monster)
    {
		monsters.push_back(monster);
		monster->SetMonsterId(monsters.size() - 1);
    }
	void MonsterManager::AddDeadMonster(Monster* monster)
    {
		EraseMonster(monster);
		deadMonsters.push_back(monster);
    }
	void MonsterManager::EraseDeadMonster()
    {
		if (!deadMonsters.empty())
		{
			for (Monster* monster : deadMonsters)
			{
				monster->SetState(GameObject::eState::NoRenderNoUpdate);
			}
		}

		deadMonsters.clear();
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

    void MonsterManager::EraseAll()
    {
		if (!monsters.empty())
		{
			for (Monster* monster : monsters)
			{
				monster->SetState(GameObject::eState::NoRenderNoUpdate);
			}
		}
		EraseDeadMonster();
		ClearMonster();
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