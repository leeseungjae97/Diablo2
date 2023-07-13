#include "mCollider2D.h"
#include "mGameObject.h"
#include "mRenderer.h"
#include "mGraphics.h"

namespace m
{
	Collider2D::Collider2D()
		: Component(eComponentType::Collider2D)
		, mTransform(nullptr)
		, mSize(Vector2::One)
		, mCenter(Vector2::Zero)
	{
	}
	Collider2D::~Collider2D()
	{}
	void Collider2D::Initialize()
	{
	}
	void Collider2D::Update()
	{}
	void Collider2D::LateUpdate()
	{
		Component::LateUpdate();
		Transform* tr = GetOwner()->GetComponent<Transform>();

		Vector3 scale = tr->GetScale();
		scale.x *= mSize.x;
		scale.y *= mSize.y;

		Vector3 pos = tr->GetPosition();
		//pos.x += mCenter.x;
		//pos.y += mCenter.y;

		mPosition = pos;

		DebugMesh debugMesh = {};

		debugMesh.position = pos;
		debugMesh.scale = scale;
		debugMesh.rotation = tr->GetRotation();
		debugMesh.type = eColliderType::Rect;

		renderer::PushDebugMeshAttribute(debugMesh);
	}
	void Collider2D::Render()
	{}
}