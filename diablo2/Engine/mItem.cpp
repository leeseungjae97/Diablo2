#include "mItem.h"

#include "..\engine_source\mTransform.h"
#include "..\engine_source\mApplication.h"

extern m::Application application;
namespace m
{
	Item::Item(eItemType type)
		: mType(type)
		, bHover(false)
		, mInvenMaterial()
		, mFieldMaterial()
		, iSpaceInvenX(0)
		, iSpaceInvenY(0)
	{}
	Item::~Item()
	{}
	void Item::Initialize()
	{}
	void Item::Update()
	{
		Transform* tr = GetComponent<Transform>();
		Vector3 mScale = tr->GetScale();

		Viewport viewport = application.GetViewport();

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

		Vector3 unprojMousePos = Input::GetUnprojectionMousePos(mScale.z, viewport, proj, view);

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
	void Item::LateUpdate()
	{}
	void Item::Render()
	{}
}