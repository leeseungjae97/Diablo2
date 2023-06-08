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
		for (int i = 0; i < 10; i++)
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

	}

	void Scene::Initialize()
	{
		// 여기서 초기 게임 맵데이터를 세팅해줘야 한다.
	}
	void Scene::Update()
	{
		for (GameObject* gameObj : mGameObjects)
		{
			if(gameObj->GetState() != GameObject::eState::Dead)
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
			if (gameObj->GetState() != GameObject::eState::Dead)
				gameObj->Render();
		}
	}
}