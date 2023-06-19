#include "mLayer.h"
#include "mGameObject.h"
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
	{}
	void Layer::Update()
	{
		for (GameObject* gameObj : mGameObjects)
		{
			gameObj->Update();
		}
	}
	void Layer::LateUpdate()
	{
		for (GameObject* gameObj : mGameObjects)
		{
			gameObj->LateUpdate();
		}
	}
	void Layer::Render()
	{
		for (GameObject* gameObj : mGameObjects)
		{
			gameObj->Render();
		}
	}
	void Layer::AddGameObject(GameObject* gameObj)
	{
		mGameObjects.push_back(gameObj);
	}
}