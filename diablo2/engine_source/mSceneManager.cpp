#include "mSceneManager.h"

namespace m
{
	Scene* SceneManager::mActiveScene = nullptr;
	void SceneManager::Initialize()
	{}
	void SceneManager::Update()
	{
		mActiveScene->Update();
	}
	void SceneManager::LateUpdate()
	{
		mActiveScene->LateUpdate();
	}
	void SceneManager::Render()
	{
		mActiveScene->Render();
	}
}