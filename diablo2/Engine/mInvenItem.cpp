#include "mInvenItem.h"
#include "..\engine_source\mInput.h"
#include "..\engine_source\mApplication.h"
#include "..\engine_source\mTransform.h"

extern m::Application application;
namespace m
{
	InvenItem::InvenItem(eItemType type)
		: Item(type)
		, bSetMouseFollow(false)
	{
	}
	InvenItem::~InvenItem()
	{}
	void InvenItem::Initialize()
	{
		Item::Initialize();
	}
	void InvenItem::Update()
	{
		Item::Update();
		if (GetHover())
		{
			if (Input::GetKeyDown(eKeyCode::LBUTTON))
			{
				bSetMouseFollow = bSetMouseFollow ? false : true;
			}
		}
		if (bSetMouseFollow)
		{
			Viewport viewport = application.GetViewport();

			Vector3 unprojMousePos = Input::GetUnprojectionMousePos(-1.f
				, viewport, GetCamera()->GetPrivateProjectionMatrix(), GetCamera()->GetPrivateViewMatrix());
			unprojMousePos.x -= GetComponent<Transform>()->GetScale().x / 2.f;
			unprojMousePos.y += GetComponent<Transform>()->GetScale().y / 2.f;
			GetComponent<Transform>()->SetPosition(Vector3(unprojMousePos));
		}
	}
	void InvenItem::LateUpdate()
	{
		Item::LateUpdate();
	}
	void InvenItem::Render()
	{
		Item::Render();
	}
}