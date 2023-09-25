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
		virtual void Destroy();
		virtual void DelayDestroy();

		void AddGameObject(GameObject* gameObj);
		void FrontGameObject(GameObject* gameObj);
		void ChangeLayerIndexGameObject(GameObject* gameObj, GameObject* targetObj);
		const std::vector<GameObject*>& GetGameObjects() { return mGameObjects; }

	private:
		std::vector<GameObject*> mGameObjects;
		std::vector<GameObject*> mDelayDeleteObjects;
	};

}

