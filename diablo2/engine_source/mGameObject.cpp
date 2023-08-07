#include "mGameObject.h"
#include "mRenderer.h"
#include "mGraphicDevice_DX11.h"
#include "mTransform.h"
#include "mScript.h"
namespace m
{
	int GameObject::GameObjectIdDispender = 0;
	GameObject::GameObject()
		: mState(eState::RenderUpdate)
		, mBattleState(eBattleState::Idle)
		, mCamera(nullptr)
		, bHover(false)
		, bCulled(false)
		, bRhombus(false)
		, iGameObjectId(0)
	{
		iGameObjectId = GameObjectIdDispender;
		GameObjectIdDispender++;
		AddComponent<Transform>();
	}

	GameObject::~GameObject()
	{
		for (Component* comp : mComponents)
		{
			if (comp == nullptr)
				continue;

			delete comp;
			comp = nullptr;
		}
		for (Script* script : mScripts)
		{
			if (script == nullptr)
				continue;

			delete script;
			script = nullptr;
		}
	}

	void GameObject::Initialize()
	{
		for (Component* comp : mComponents)
		{
			comp->Initialize();
		}
	}

	void GameObject::Update()
	{
		MousePosHoverGameObject();

		for (Component* comp : mComponents)
		{
			comp->Update();
		}
		for (Script* script : mScripts)
		{
			script->Update();
		}
	}

	void GameObject::LateUpdate()
	{
		for (Component* comp : mComponents)
		{
			comp->LateUpdate();
		}
		for (Script* script : mScripts)
		{
			script->LateUpdate();
		}
	}

	void GameObject::Render()
	{
		for (Component* comp : mComponents)
		{
			comp->Render();
		}
		for (Script* script : mScripts)
		{
			script->Render();
		}

	}
	void GameObject::MousePosHoverGameObject()
	{
		if (GetState() != eState::RenderUpdate)
		{
			bHover = false;
			return;
		}
		Transform* tr = GetComponent<Transform>();
		Vector3 mPos = tr->GetPosition();
		Vector3 mScale = tr->GetScale();
		MAKE_VEC2_F_VEC3(mPosV2, mPos);
		MAKE_VEC2_F_VEC3(mScaleV2, mScale);
		Matrix proj = Matrix::Identity;
		Matrix view = Matrix::Identity;

		if (nullptr == GetCamera())
		{
			proj = Camera::GetProjectionMatrix();
			view = Camera::GetViewMatrix();
		}
		else
		{
			proj = GetCamera()->GetPrivateProjectionMatrix();
			view = GetCamera()->GetPrivateViewMatrix();
		}

		Vector3 unprojMousePos = Input::GetUnprojectionMousePos(mPos.z, proj, view);
		MAKE_VEC2_F_VEC3(unpMPosV2, unprojMousePos);
		if (bRhombus)
		{
			if (Vector2::PointIntersectRhombus(mPosV2
											, mScaleV2
											, unpMPosV2))
			{
				bHover = true;
			}
			else bHover = false;
		}
		else
		{
			if (Vector2::PointIntersectRect(mPosV2
											, mScaleV2
											, unpMPosV2))
			{
				bHover = true;
			}
			else bHover = false;
		}
		
	}
}