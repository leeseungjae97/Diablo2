#include "mLayer.h"

namespace m
{
	Layer::Layer()
	{}
	Layer::~Layer()
	{
		for (GameObject* gameObj : mGameObjects)
		{
			if (gameObj == nullptr)
				continue;

			delete gameObj;
			gameObj = nullptr;
		}
	}
	void Layer::Initialize()
	{

	}
	void Layer::Update()
	{
		for (GameObject* gameObj : mGameObjects)
		{
			if (gameObj->GetState() == GameObject::eState::Dead)
				continue;

			gameObj->Update();
		}
	}
	void Layer::LateUpdate()
	{
		for (GameObject* gameObj : mGameObjects)
		{
			if (gameObj->GetState() == GameObject::eState::Dead)
				continue;

			gameObj->LateUpdate();
		}
	}
	void Layer::Render()
	{
		for (GameObject* gameObj : mGameObjects)
		{
			if (gameObj->GetState() != GameObject::eState::Active
				|| gameObj->GetState() != GameObject::eState::Invisible)
				continue;

			gameObj->Render();

		}
	}
	void Layer::AddGameObject(GameObject* gameObj)
	{
		mGameObjects.push_back(gameObj);
	}
	void Layer::ChangeOrderGameObject(GameObject* gameObj)
	{
		//if (gameObj == nullptr) return;
		//std::vector<GameObject*>::iterator iter = mGameObjects.begin();
		//int index = 0;
		//while (iter != mGameObjects.end())
		//{
		//	if ((*iter) == gameObj)
		//	{
		//		//iter = mGameObjects.erase(iter);
		//		GameObject* tmp = mGameObjects[mGameObjects.size() - 1];
		//		mGameObjects[mGameObjects.size() - 1] = (*iter);
		//		mGameObjects[index] = tmp;

		//		break;
		//	}
		//	else
		//	{
		//		iter++;
		//		index++;
		//	}
		//}
		if (gameObj == nullptr) return;
		std::vector<GameObject*>::iterator iter = mGameObjects.begin();
		while (iter != mGameObjects.end())
		{
			if ((*iter) == gameObj)
			{
				iter = mGameObjects.erase(iter);
				break;
			}
			else iter++;
		}
		mGameObjects.push_back(gameObj);
	}
}