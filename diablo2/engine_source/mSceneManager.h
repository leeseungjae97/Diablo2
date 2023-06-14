#pragma once
#include "mScene.h"

namespace m
{
	class SceneManager
	{
	public:
		static void Initialize();
		static void Update();
		static void LateUpdate();
		static void Render();


	private:
		static Scene* mActiveScene;
	};

}

