#include "mMouseManager.h"
#include "mSceneManager.h"
#include "mInput.h"
#include "mScene.h"
#include "mLayer.h"
#include "mApplication.h"
#include "mUI.h"

extern m::Application application;
namespace m
{
	bool MouseManager::mMouseOnUI = false;
	bool MouseManager::mMouseOnMonster = false;
	Vector2 MouseManager::hoverMonsterTileCoord = Vector2(-1.f, -1.f);
	int MouseManager::hoverMonsterId = -1;
	Item* MouseManager::mMouseFollowItem = nullptr;
	Vector3 MouseManager::UnprojectionMousePos(float z, Camera* camera)
	{
		Matrix proj = Matrix::Identity;
		Matrix view = Matrix::Identity;

		if (nullptr == camera)
		{
			proj = Camera::GetProjectionMatrix();
			view = Camera::GetViewMatrix();
		}
		else
		{
			proj = camera->GetPrivateProjectionMatrix();
			view = camera->GetPrivateViewMatrix();
		}

		Vector3 unprojMousePos = Input::GetUnprojectionMousePos(z, proj, view);
		return Vector3(unprojMousePos.x , unprojMousePos.y, z);
	}

	void MouseManager::Initialize()
	{

	}

	void MouseManager::Update()
	{
		Scene* scene = SceneManager::GetActiveScene();
		Layer* layer = scene->GetLayer(eLayerType::UI);
		auto gameObjs = layer->GetGameObjects();

		for (auto gameObj : gameObjs)
		{
			auto gameUI = dynamic_cast<UI*>(gameObj);
			if (nullptr == gameUI ||
				gameUI->GetState() != GameObject::eState::RenderUpdate) continue;
			 
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