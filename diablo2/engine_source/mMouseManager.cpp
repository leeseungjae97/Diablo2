#include "mMouseManager.h"
#include "mSceneManager.h"
#include "mInput.h"
#include "mScene.h"
#include "mLayer.h"
#include "mApplication.h"
#include "mUI.h"

#include "../Engine/mInvenItem.h"

extern m::Application application;
namespace m
{
	bool MouseManager::mMouseOnUI = false;
	bool MouseManager::mMouseOnMonster = false;
	bool MouseManager::bFreeMouse = false;

	Vector2 MouseManager::hoverMonsterTileCoord = Vector2(-1.f, -1.f);
	int MouseManager::hoverMonsterId = -1;
	InvenItem* MouseManager::mMouseFollowItem = nullptr;

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

    void MouseManager::SetMouseFollow(InvenItem* item)
    {
		if(mMouseFollowItem != item)
		    mMouseFollowItem = item;
    }

    void MouseManager::Initialize()
	{
	}
    void MouseManager::Update()
	{
		if (bFreeMouse) FreeMouseFollow();
		UpdateMouseHoverUI();
		UpdateMouseFollow();
	}
	void MouseManager::MouseOut()
	{
	    
	}
	void MouseManager::UpdateMouseFollow()
	{
		if (nullptr == mMouseFollowItem) return;
		MAKE_POS(pos, mMouseFollowItem);
		Vector3 unprojMousePos = UnprojectionMousePos(pos.z, mMouseFollowItem->GetCamera());
		unprojMousePos.z = pos.z;
		SET_POS_VEC(mMouseFollowItem, unprojMousePos);
	}

	void MouseManager::UpdateMouseHoverUI()
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

    void MouseManager::FreeMouseFollow()
    {
		if (mMouseFollowItem) mMouseFollowItem = nullptr;
		bFreeMouse = false;
    }

    void MouseManager::FreeMouseFollowNextUpdate()
    {
		bFreeMouse = true;
    }

    void MouseManager::LateUpdate()
	{}

	void MouseManager::Render()
	{}

}