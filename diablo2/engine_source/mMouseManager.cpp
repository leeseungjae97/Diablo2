#include "mMouseManager.h"
#include "mSceneManager.h"
#include "mTransform.h"
#include "mInput.h"
#include "mScene.h"
#include "mLayer.h"
#include "mApplication.h"
#include "mUI.h"

extern m::Application application;
namespace m
{
	bool MouseManager::mMouseOnUI = false;

	void MouseManager::Initialize()
	{

	}

	void MouseManager::Update()
	{
		Scene* scene = SceneManager::GetActiveScene();
		Layer& layer = scene->GetLayer(eLayerType::UI);
		auto gameObjs = layer.GetGameObjects();

		for (auto gameObj : gameObjs)
		{
			auto gameUI = dynamic_cast<UI*>(gameObj);
			if (nullptr == gameUI ||
				gameUI->GetState() != GameObject::eState::Active) continue;

			if (gameUI->GetHover())
			{
				mMouseOnUI = true;
				return;
			}
		}
		mMouseOnUI = false;
	}

	void MouseManager::LateUpdate()
	{}

	void MouseManager::Render()
	{}

}