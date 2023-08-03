#include "mMonsterManager.h"

#include "../Engine/mMonster.h"

namespace m
{
	std::vector<Monster*> MonsterManager::monsters = {};
	float MonsterManager::dispendMonsterId = 0.f;
	Monster* MonsterManager::GetMonster(float monsterId)
	{
		auto iter = monsters.begin();
		while (iter != monsters.end())
		{
			if ((*iter)->GetMonsterId() == monsterId)
				return (*iter);
			else
				iter++;
		}
		return nullptr;
	}
	void MonsterManager::ClearMonster()
	{
		if (!monsters.empty()) monsters.clear();
	}
	float MonsterManager::DispendMonsterId()
	{
		float dispendId = dispendMonsterId;
		dispendMonsterId += 0.00001f;
		return dispendId;
	}
}