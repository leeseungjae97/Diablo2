#include "mScene.h"
namespace m
{
	Scene::Scene()
	{
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
		for (Layer* layer : mLayers)
		{
			layer->Update();
		}
	}

	void Scene::LateUpdate()
	{
	}
	void Scene::Render()
	{
		for (Layer* layer : mLayers)
		{
			layer->Render();
		}
	}
}