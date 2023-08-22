#include "mLayer.h"

namespace m
{
	Layer::Layer()
	{
	}
	Layer::~Layer()
	{
		for (GameObject* gameObj : mGameObjects)
		{
			if (gameObj == nullptr)
				continue;
			if (gameObj->GetState() == GameObject::eState::Delete) 
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
			if (gameObj->GetCulled()) continue;
			if (gameObj->GetState() == GameObject::eState::NoRenderNoUpdate
				|| gameObj->GetState() == GameObject::eState::Delete
				|| gameObj->GetState() == GameObject::eState::RenderNoUpdate)
				continue;

			gameObj->Update();
		}
	}
	void Layer::LateUpdate()
	{
		for (GameObject* gameObj : mGameObjects)
		{
			if (gameObj->GetCulled()) continue;
			if (gameObj->GetState() == GameObject::eState::NoRenderNoUpdate
				|| gameObj->GetState() == GameObject::eState::Delete
				|| gameObj->GetState() == GameObject::eState::RenderNoUpdate)
				continue;

			gameObj->LateUpdate();
		}
	}
	void Layer::Render()
	{
		//for (GameObject* gameObj : mGameObjects)
		//{
		//	if (gameObj->GetCulled()) continue;
		//	if (gameObj->GetState() == GameObject::eState::NoRenderNoUpdate
		//		|| gameObj->GetState() == GameObject::eState::NoRenderUpdate
		//		|| gameObj->GetState() == GameObject::eState::Delete)
		//		continue;

		//	gameObj->Render();

		//}
	}
	void Layer::Destroy()
	{
		// dead 오브젝트 모아두기
		std::set<GameObject*> deleteGameObj = {};
		for (GameObject* gameObj : mGameObjects)
		{
			if (gameObj->GetState()
				== GameObject::eState::Delete)
				deleteGameObj.insert(gameObj);
		}

		// daed 오브젝트 제외시키기 layer에서
		typedef std::vector<GameObject*>::iterator GameObjectIter;
		for (GameObjectIter iter = mGameObjects.begin()
			 ; iter != mGameObjects.end(); )
		{
			std::set<GameObject*>::iterator deleteIter
				= deleteGameObj.find(*(iter));

			if (deleteIter != deleteGameObj.end())
			{
				iter = mGameObjects.erase(iter);
				continue;
			}

			iter++;
		}

		//메모리 해제
		for (GameObject* gameObj : deleteGameObj)
		{
			delete gameObj;
			gameObj = nullptr;
		}
	}
	void Layer::AddGameObject(GameObject* gameObj)
	{
		mGameObjects.push_back(gameObj);
	}
	void Layer::FrontGameObject(GameObject* gameObj)
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

	void Layer::ChangeLayerIndexGameObject(GameObject* gameObj, GameObject* targetObj)
	{
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
		iter = mGameObjects.begin();
		while (iter != mGameObjects.end())
		{
			if ((*iter) == targetObj)
			{
				break;
			}
			else iter++;
		}
		mGameObjects.insert(iter, gameObj);
	}
}
