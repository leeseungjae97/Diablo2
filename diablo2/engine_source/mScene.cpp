#include "mScene.h"
#include "mRenderer.h"

namespace m
{
	Scene::Scene()
	{
		//mLayers.resize((int)eLayerType::End);
		for (int i = 0; i < (int)eLayerType::End; ++i)
			mLayers.push_back(new Layer());
	}
	Scene::~Scene()
	{
		for(Layer* layer : mLayers)
		{
			delete layer;
			layer = nullptr;
		}
	}

	void Scene::Initialize()
	{
		// 여기서 초기 게임 맵데이터를 세팅해줘야 한다.
	}

	void Scene::Update()
	{
		int a = 0; 
		for (Layer* layer : mLayers)
		{
			//if(a == (int)eLayerType::PlayerSkill)
			//{
			//	int b = 0;
			//}
			layer->Update();
			++a;
		}
	}
	void Scene::LateUpdate()
	{
		for (Layer* layer : mLayers)
		{
			layer->LateUpdate();
		}
	}
	void Scene::Render()
	{
		for (Layer* layer : mLayers)
		{
			layer->Render();
		}
	}
	void Scene::Destroy()
	{
		for (Layer* layer : mLayers)
		{
			layer->Destroy();
		}
	}
	
    void Scene::AddGameObject(eLayerType type, GameObject* gameObj)
	{
		gameObj->SetLayerType(type);
		mLayers[(int)type]->AddGameObject(gameObj);
	}
	Layer* Scene::GetGameObjects(eLayerType type)
	{
		return mLayers[(int)type];
	}
	void Scene::OnExit()
	{}
	void Scene::OnEnter()
	{
		renderer::mainCamera = GetSceneMainCamera();
	}
}