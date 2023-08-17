#include "mSceneManager.h"
#include "mMonsterManager.h"
namespace m
{
	Scene* SceneManager::mActiveScene = nullptr;
	std::map<std::wstring, Scene*> SceneManager::mScenes;
	void SceneManager::Initialize()
	{
		mActiveScene = LoadScene(L"PlayScene");
		srand((unsigned int)time(NULL));
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
	void SceneManager::Destroy()
	{
		mActiveScene->Destroy();
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
			MonsterManager::ClearMonster();
			mActiveScene = iter->second;
			mActiveScene->OnEnter();
		}

		return iter->second;
	}
}