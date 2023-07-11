#include "mCollider2D.h"
#include "mGameObject.h"

namespace m
{
	Collider2D::Collider2D()
		: Component(eComponentType::Collider2D)
		, mTransform(nullptr)
		, mSize(Vector2::One)
		, mCenter(Vector2::Zero)
	{}
	Collider2D::~Collider2D()
	{}
	void Collider2D::Initialize()
	{
		mTransform = GetOwner()->GetComponent<Transform>();
	}
	void Collider2D::Update()
	{}
	void Collider2D::LateUpdate()
	{}
	void Collider2D::Render()
	{}
}