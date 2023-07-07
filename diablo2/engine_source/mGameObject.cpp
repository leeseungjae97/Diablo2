#include "mGameObject.h"
#include "mRenderer.h"
#include "mGraphicDevice_DX11.h"
#include "mTransform.h"
#include "mScript.h"
namespace m
{
	GameObject::GameObject()
		: mState(eState::Active)
		, mCamera(nullptr)
	{
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
		Transform* tr = GetComponent<Transform>();
		Vector3 mPos = tr->GetPosition();
		Vector3 mScale = tr->GetScale();

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

		if (Vector2::OnMouseVector2Rect(Vector2(tr->GetPosition().x, tr->GetPosition().y)
			, Vector2(mScale.x, mScale.y)
			, Vector2(unprojMousePos.x, unprojMousePos.y)))
		{
			bHover = true;
		}
		else
		{
			bHover = false;
		}
	}
}