#include "mMonsterManager.h"

#include "../Engine/mMonster.h"

namespace m
{
	std::vector<Monster*> MonsterManager::monsters = {};
	std::vector<Monster*> MonsterManager::deadMonsters = {};
	std::vector<MoveTileReservation> MonsterManager::moveReservations = {};
	int MonsterManager::reserveSize = 50;
	int MonsterManager::monstersSize = 0;

	void MonsterManager::Init()
	{
		monsters.reserve(reserveSize);
		deadMonsters.reserve(reserveSize);
		moveReservations.reserve(reserveSize);
	}

	
	bool MonsterManager::ReserveMoveTile(Monster* monster, Vector2 coord)
	{
		if (monster == nullptr)
			return false;

		for (MoveTileReservation& reservation : moveReservations)
		{
			if (reservation.owner != monster && reservation.coord == coord)
				return false;
		}

		for (MoveTileReservation& reservation : moveReservations)
		{
			if (reservation.owner == monster)
			{
				reservation.coord = coord;
				return true;
			}
		}

		moveReservations.push_back({ monster, coord });
		return true;
	}

	void MonsterManager::ReleaseMoveTile(Monster* monster)
	{
		if (monster == nullptr)
			return;

		auto iter = moveReservations.begin();
		while (iter != moveReservations.end())
		{
			if (iter->owner == monster)
				iter = moveReservations.erase(iter);
			else
				++iter;
		}
	}

	bool MonsterManager::IsMoveTileReservedByOther(Monster* monster, Vector2 coord)
	{
		for (const MoveTileReservation& reservation : moveReservations)
		{
			if (reservation.owner != monster && reservation.coord == coord)
				return true;
		}
		return false;
	}

	bool MonsterManager::HasMoveTileReservation(Monster* monster)
	{
		for (const MoveTileReservation& reservation : moveReservations)
		{
			if (reservation.owner == monster)
				return true;
		}
		return false;
	}
	Monster& MonsterManager::AddMonster(Vector3 pos)
	{
		int index = monstersSize;
		++monstersSize;
		//monsters[index];
		monsters[index]->SetMonsterId(index);
		return *(monsters[index]);
	}

    void MonsterManager::AddMonster(Monster* monster)
    {
		monsters.push_back(monster);
		monster->SetMonsterId(monsters.size() - 1);
    }
	void MonsterManager::AddDeadMonster(Monster* monster)
    {
		ReleaseMoveTile(monster);
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
		ReleaseMoveTile(monster);
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
		moveReservations.clear();
	}
}