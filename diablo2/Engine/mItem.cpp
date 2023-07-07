#include "mItem.h"

#include "..\engine_source\mTransform.h"

namespace m
{
	Item::Item(eItemType type)
		: mType(type)
		//, bHover(false)
		, mInvenMaterial()
		, mFieldMaterial()
		, iSpaceInvenX(0)
		, iSpaceInvenY(0)
	{}
	Item::Item()
		: mType(eItemType::None)
		//, bHover(false)
		, mInvenMaterial()
		, mFieldMaterial()
		, iSpaceInvenX(0)
		, iSpaceInvenY(0)
	{}
	Item::~Item()
	{}
	void Item::Initialize()
	{
		GameObject::Initialize();
	}
	void Item::Update()
	{
		GameObject::Update();
		//Transform* tr = GetComponent<Transform>();
		//Vector3 mScale = tr->GetScale();

		//Matrix proj = Matrix::Identity;
		//Matrix view = Matrix::Identity;

		//if (nullptr == GetCamera())
		//{
		//	proj = Camera::GetProjectionMatrix();
		//	view = Camera::GetViewMatrix();
		//}
		//else
		//{
		//	proj = GetCamera()->GetPrivateProjectionMatrix();
		//	view = GetCamera()->GetPrivateViewMatrix();
		//}

		//Vector3 unprojMousePos = Input::GetUnprojectionMousePos(mScale.z, proj, view);

		//if (Vector2::OnMouseVector2Rect(Vector2(tr->GetPosition().x, tr->GetPosition().y)
		//	, Vector2(mScale.x, mScale.y)
		//	, Vector2(unprojMousePos.x, unprojMousePos.y)))
		//{
		//	bHover = true;
		//}
		//else
		//{
		//	bHover = false;
		//}
	}
	void Item::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Item::Render()
	{
		GameObject::Render();
	}
}