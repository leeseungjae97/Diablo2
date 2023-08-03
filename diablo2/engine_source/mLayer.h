#pragma once
#include "mGameObject.h"
namespace m
{
	class Layer
	{
	public:
		Layer();
		~Layer();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		void AddGameObject(GameObject* gameObj);
		void ChangeOrderGameObject(GameObject* gameObj);
		const std::vector<GameObject*> GetGameObjects() { return mGameObjects; }

	private:
		std::vector<GameObject*> mGameObjects;
	};

}

