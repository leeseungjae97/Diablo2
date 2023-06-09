#pragma once
#include "mEntity.h"
#include "mGameObject.h"
namespace m
{
	class Scene : public Entity
	{
	public:
		Scene();
		virtual ~Scene();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		vector<GameObject*>& GetGameObjects() { return mGameObjects; }
	private:
		std::vector<GameObject*> mGameObjects;
	};
}

