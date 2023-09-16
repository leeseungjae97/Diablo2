#include "mCollider2D.h"
#include "mGameObject.h"
#include "mRenderer.h"
#include "mGraphics.h"
#include "mMeshRenderer.h"

namespace m
{
	UINT Collider2D::mColliderNumber = 0;
	Collider2D::Collider2D()
		: Component(eComponentType::Collider2D)
		, mTransform(nullptr)
		, mSize(Vector3::One)
		, mCenter(Vector2::Zero)
		, mScale(Vector3::One)
		, mType(eColliderType::Rect)
		, mColor(eColor::Green)
		, bOnEnter(false)
		, bOnStay(false)
		, bOnExit(false)
		, bVisible(true)
		, bResize(false)
	    , bCustomSize(false)
	{
		mColliderNumber++;
		mColliderID = mColliderNumber;
	}
	Collider2D::~Collider2D()
	{
	}
	void Collider2D::Initialize()
	{
	}
	void Collider2D::Update()
	{
		if (collidereds.empty())
		{
			SetColor(eColor::Green);
			SetExit();
		}
		else
		{
			SetColor(eColor::Red);
			SetStay();
		}
	}
	void Collider2D::LateUpdate()
	{
		Component::LateUpdate();

		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 scale = tr->GetScale();
		if (bResize)
		{
			Vector3 scale = tr->GetScale();
			mScale = scale;
			bResize = false;
		}
		if (mScale == Vector3::One)
		{
			if (mType == eColliderType::Circle)
			{
				scale.y = scale.x / 2.f;
			}
			if (mType == eColliderType::Dot)
			{
				scale.x = 1.f;
				scale.y = 1.f;
			}
			scale.x *= mSize.x;
			scale.y *= mSize.y;
			if(!bCustomSize)
			    mScale = scale;
		}

		if (bCustomSize)
		{
			mScale *= mSize.x;
			mScale *= mSize.y;
		}
			

		mRotation = tr->GetRotation();
		
		Vector3 pos = tr->GetPosition();
		pos.x += mCenter.x;
		pos.y += mCenter.y;

		mPosition = pos;

		Camera* camera = GetOwner()->GetCamera();

		DebugMesh debugMesh = {};
		debugMesh.position = pos;
		debugMesh.scale = mScale;
		debugMesh.rotation = mRotation;
		debugMesh.type = mType;
		debugMesh.view = camera->GetPrivateViewMatrix();
		debugMesh.projection = camera->GetPrivateProjectionMatrix();
		debugMesh.color = mColor;
		debugMesh.visible = bVisible;
		if(bVisible)
			GetOwner()->GetState() != GameObject::RenderUpdate ? debugMesh.visible = false : debugMesh.visible = true;

		renderer::PushDebugMeshAttribute(debugMesh);
	}

	void Collider2D::Render()
	{}
	void Collider2D::Release()
	{
		if (!collidereds.empty())
		{
			for (Collider2D* col : collidereds)
			{
				if (nullptr == col) continue;
				if (col->GetCollidereds().empty()) continue;

				//std::erase(col->GetCollidereds(), this);
				auto iter = col->GetCollidereds().begin();
				while (iter != col->GetCollidereds().end())
				{
					if ((*iter) == this)
					{
						iter = col->GetCollidereds().erase(iter);
						break;
					}
					else ++iter;
				}
			}
			collidereds.clear();
		}
	}
	void Collider2D::OnCollisionEnter(Collider2D* other)
	{
		if (std::find(exceptTypes.begin(), exceptTypes.end(), other->GetOwner()->GetLayerType()) != exceptTypes.end()) 
			return;
	
		collidereds.push_back(other);

		SetEnter();
		const std::vector<Script*>& scripts
			= GetOwner()->GetScripts();

		for (Script* script : scripts)
		{
			script->OnCollisionEnter(other);
		}
	}
	void Collider2D::OnCollisionStay(Collider2D* other)
	{
		if (std::find(exceptTypes.begin(), exceptTypes.end(), other->GetOwner()->GetLayerType()) != exceptTypes.end())
			return;

		SetStay();
		const std::vector<Script*>& scripts
			= GetOwner()->GetScripts();

		for (Script* script : scripts)
		{
			script->OnCollisionStay(other);
		}
	}
	void Collider2D::OnCollisionExit(Collider2D* other)
	{
		if (std::find(exceptTypes.begin(), exceptTypes.end(), other->GetOwner()->GetLayerType()) != exceptTypes.end())
			return;

		std::erase(collidereds, other);

		SetExit();
		const std::vector<Script*>& scripts
			= GetOwner()->GetScripts();

		for (Script* script : scripts)
		{
			script->OnCollisionExit(other);
		}
	}

    void Collider2D::SetScale(Vector3 scale)
    {
		mScale = scale;
		bCustomSize = true;
    }

    bool Collider2D::SearchObjectGameObjectId(UINT gameObjectId)
	{
		for (Collider2D* col : collidereds)
		{
			if (nullptr == col) continue;
			if (col->GetOwner()->GetGameObjectId() == gameObjectId) return true;
		}
			

		return false;
	}
}