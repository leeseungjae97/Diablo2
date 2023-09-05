#include "mInvenItem.h"

#include "../engine_source/mInput.h"
#include "../engine_source/mApplication.h"
#include "../engine_source/mTransform.h"
#include "../engine_source/mMeshRenderer.h"
#include "../engine_source/mCollider2D.h"
#include "../engine_source/mStashManager.h"

#include "mEmptyRect.h"
#include "mMouseManager.h"
#include "mPosionScript.h"


namespace m
{
	InvenItem::InvenItem(eItem item)
		: Item(item)
	    , bDoItemFunction(false)
	{
		eItemType type = itemTypeTable[(UINT)item];

		if(type == eItemType::Posion)
		{
			PosionScript* pis = ADD_COMP(this, PosionScript);
			pis->SetOwnerItem(item);
		}

		ADD_COMP(this, Collider2D);
		ADD_COMP(this, MeshRenderer);

		SET_MESH(this, L"RectMesh");
		SET_MATERIAL(this, itemNameTable[(UINT)item]);

		SET_POS_XYZ(this, -10.f, -10.f,-1.f);
		SET_SCALE_XYZ(this, 27.f * itemInvenDisplayScale[(UINT)item][0] * Texture::GetWidRatio()
			, 27.f * itemInvenDisplayScale[(UINT)item][1] * Texture::GetHeiRatio(), 0.f);

		prevPosition = GET_POS(this);
	}
	InvenItem::~InvenItem()
	{
	}
	void InvenItem::Initialize()
	{
		Item::Initialize();
	}
	void InvenItem::Update()
	{
		Item::Update();
		if (GetHover())
		{
			if (Input::GetKeyDownOne(eKeyCode::LBUTTON))
			{
				SetMouseFollow(GetMouseFollow() ? false : true);
			}
		}
		if (GetMouseFollow())
		{
			MouseManager::SetMouseFollow(this);
		}
		else
		{
			if (this == MouseManager::GetMouseFollow())
				MouseManager::FreeMouseFollow();
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
