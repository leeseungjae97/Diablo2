#include "mScene.h"
namespace m
{
	Scene::Scene()
	{
		mGameObjects.push_back(new GameObject(Vector4(0.0f, 0.0f, 0.0f, 0.0f), Vector4(1.0f, 1.0f, 1.0f, 1.0f), true));
		for (int i = 0; i < 10; i++)
		{
			srand((unsigned int)time(NULL));
			int randX = rand() % 100;
			int randY = rand() % 100;

			int randR = rand() % 2;
			int randG = rand() % 2;
			int randB = rand() % 2;
			mGameObjects.push_back(new GameObject(
				Vector4((float)randX / 100.f, (float)randY / 100.f, 0.0f, 0.0f)
				, Vector4(randR, randG, randB, 1.0f)
				, false));
		}
	}
	Scene::~Scene()
	{

	}

	void Scene::Initialize()
	{
		// 여기서 초기 게임 맵데이터를 세팅해줘야 한다.
	}

	void Scene::Update()
	{
		for (GameObject* gameObj : mGameObjects)
		{
			gameObj->Update();
		}
	}

	void Scene::LateUpdate()
	{
	}
	void Scene::Render()
	{
		for (GameObject* gameObj : mGameObjects)
		{
			gameObj->Render();
		}
	}
}