#include "mSceneManager.h"
#include "mPlayScene.h"
#include "mSelectCharacterScene.h"
#include "mMainMenuScene.h"

namespace m
{
	Scene* SceneManager::mActiveScene = nullptr;
	std::map<std::wstring, Scene*> SceneManager::mScenes;
	void SceneManager::Initialize()
	{
		SceneManager::CreateScene<PlayScene>(wsScenes[(UINT)eSceneType::PlayScene]);
		SceneManager::CreateScene<SelectCharacterScene>(wsScenes[(UINT)eSceneType::SelectCharacterScene]);
		SceneManager::CreateScene<MainMenuScene>(wsScenes[(UINT)eSceneType::MainMenuScene]);

		std::map<std::wstring, Scene*>::iterator iter = mScenes.begin();
		while (iter != mScenes.end())
		{
			if (nullptr != iter->second)
			{
				iter->second->Initialize();
				iter++;
			}
		}

		mActiveScene = LoadScene(wsScenes[(UINT)eSceneType::MainMenuScene]);
	}
	void SceneManager::Update()
	{
		if(mActiveScene)
			mActiveScene->Update();
	}
	void SceneManager::LateUpdate()
	{
		if (mActiveScene)
			mActiveScene->LateUpdate();
	}
	void SceneManager::Release()
	{
		for (auto iter : mScenes)
		{
			delete iter.second;
			iter.second = nullptr;
		}
	}

	void SceneManager::Render()
	{	
		if (mActiveScene)
			mActiveScene->Render();
	}
	Scene* SceneManager::LoadScene(std::wstring name)
	{
		std::map<std::wstring, Scene*>::iterator iter
			= mScenes.find(name);

		if (iter == mScenes.end())
			return nullptr;

		if (nullptr != mActiveScene)
		{
			mActiveScene->OnExit();
			mActiveScene = iter->second;
			mActiveScene->OnEnter();
		}

		return iter->second;
	}
}