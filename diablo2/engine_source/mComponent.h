#pragma once
#include "mEntity.h"
#include "mEnums.h"
//#include "..\Engine\mPlayer.h"

namespace m
{
	using namespace m::enums;
	using namespace m::math;
	class Monster;
	class Player;
	class GameObject;
	class Component : public Entity
	{
	public:
		Component(eComponentType type);
		~Component();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		void SetOwner(GameObject* owner) { mOwner = owner; }
		GameObject* GetOwner() { return mOwner; }
		Player* GetPlayer() { return mPlayer; }
		Monster* GetMonster() { return mMonster; }
		void SetPlayer(Player* player) { mPlayer = player; }
		void SetMonster(Monster* monster) { mMonster = monster; }

	private:
		const eComponentType mType;
		GameObject* mOwner;
		Player* mPlayer;
		Monster* mMonster;
	};

}

