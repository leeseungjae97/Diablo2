#include "mInvenItem.h"
#include "..\engine_source\mInput.h"
#include "..\engine_source\mApplication.h"
#include "..\engine_source\mTransform.h"

#include "mInventory.h"

namespace m
{
	InvenItem::InvenItem(eItemType type, Inventory *inventory, Vector3 pos)
		: Item(type)
		, mInventory(inventory)
		, bSetMouseFollow(false)
	{		
		prevPosition = pos;
		GetComponent<Transform>()->SetPosition(prevPosition);
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

				bool deploy = false;
				for (UI* inven : mInventory->GetInvens())
				{
					if (inven->GetHover())
					{
						GetComponent<Transform>()->SetPosition(inven->GetComponent<Transform>()->GetPosition());
						prevPosition = inven->GetComponent<Transform>()->GetPosition();
						deploy = true;
					}
				}
				if (!deploy)
					GetComponent<Transform>()->SetPosition(prevPosition);
			}
			if (bSetMouseFollow)
			{
				Vector3 pos = GetComponent<Transform>()->GetPosition();
				Vector3 unprojMousePos = Input::GetUnprojectionMousePos(pos.z
					, GetCamera()->GetPrivateProjectionMatrix(), GetCamera()->GetPrivateViewMatrix());
				unprojMousePos.z = pos.z;
				GetComponent<Transform>()->SetPosition(Vector3(unprojMousePos));
			}
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