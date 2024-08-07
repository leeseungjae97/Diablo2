#pragma once
#include "../engine_source/mSceneManager.h"
#include "mPlayScene.h"
#include "mMainMenuScene.h"
#include "mSelectCharacterScene.h"

namespace m
{
	void InitializeScenes()
	{
		SceneManager::CreateScene<PlayScene>(L"PlayScene");
		SceneManager::CreateScene<SelectCharacterScene>(L"SelectCharacterScene");
		SceneManager::CreateScene<MainMenuScene>(L"MainMenuScene");
	}
}