#include "mSceneManager.h"
#include "mPlayScene.h"
#include "mSelectCharacterScene.h"
#include "mMainMenuScene.h"
#include "mScene.h"

namespace m
{
	Scene* SceneManager::mActiveScene = nullptr;
	std::map<std::wstring, Scene*> SceneManager::mScenes;
	void SceneManager::Initialize()
	{
		mScenes.insert(std::make_pair(wsScenes[(UINT)eSceneType::MainMenuScene], new MainMenuScene()));
		mScenes.insert(std::make_pair(wsScenes[(UINT)eSceneType::SelectCharacterScene], new SelectCharacterScene()));
		mScenes.insert(std::make_pair(wsScenes[(UINT)eSceneType::PlayScene], new PlayScene()));

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
		mActiveScene->Update();
	}
	void SceneManager::LateUpdate()
	{
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