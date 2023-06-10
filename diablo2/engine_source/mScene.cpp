#include "mScene.h"
namespace m
{
	Scene::Scene()
	{
		mGameObjects.push_back(new GameObject(Vector4(0.0f, 0.0f, 0.0f, 0.0f)
			, Vector4(1.0f, 1.0f, 1.0f, 1.0f)
			, enums::eGameObjectType::Player
			, 0.1
			, this));
		srand((unsigned int)time(NULL));
		for (int i = 0; i < 30; i++)
		{
			int randX = rand() % 50;
			int randY = rand() % 50;

			int randXSign = rand() % 2;
			int randYSign = rand() % 2;

			if (randXSign) randX *= -1;
			if (randYSign) randY *= -1;

			int randR = rand() % 2;
			int randG = rand() % 2;
			int randB = rand() % 2;
			mGameObjects.push_back(new GameObject(
				Vector4((float)randX / 50.f, (float)randY / 50.f, 0.0f, 0.0f)
				, Vector4(randR, randG, randB, 1.0f)
				, enums::eGameObjectType::Food
				, 0.05
				, this));
		}
	}
	Scene::~Scene()
	{
		//for (GameObject* gameObj : mGameObjects) delete gameObj;
	}

	void Scene::Initialize()
	{
		// 여기서 초기 게임 맵데이터를 세팅해줘야 한다.
	}
	void Scene::Update()
	{
		std::vector<GameObject*> deleteObjects;
		vector<GameObject*>::iterator iter = mGameObjects.begin();
		for (GameObject* gameObj : mGameObjects)
		{
			if (gameObj->GetState() == GameObject::eState::Active)
			{
				gameObj->Update();
				iter++;
			}
			else
			{
				deleteObjects.push_back(gameObj);
				iter = mGameObjects.erase(iter);
			}
		}


		for (GameObject* gameObj : deleteObjects) delete gameObj;
		deleteObjects.clear();
	}

	void Scene::LateUpdate()
	{
	}
	void Scene::Render()
	{
		for (GameObject* gameObj : mGameObjects)
		{
			if (gameObj->GetState() == GameObject::eState::Active)
				gameObj->Render();
		}
	}
}