#include "mInvenItem.h"

#include "../engine_source/mInput.h"
#include "../engine_source/mApplication.h"
#include "../engine_source/mTransform.h"
#include "../engine_source/mMeshRenderer.h"
#include "../engine_source/mCollider2D.h"
#include "../engine_source/mStashManager.h"
#include "../engine_source/mFontWrapper.h"
#include "../engine_source/mMouseManager.h"
#include "../engine_source/ItemLookUpTables.h"

#include "mEmptyRect.h"
#include "mInteractUI.h"
#include "mInteractUIManager.h"
#include "mPosionScript.h"


namespace m
{
	InvenItem::InvenItem(eItem item)
		: Item(item)
		, bDoItemFunction(false)
		, bMakeUI(false)
	{
		eItemType type = itemTypeTable[(UINT)item];

		if (type == eItemType::Posion)
		{
			PosionScript* pis = ADD_COMP(this, PosionScript);
			pis->SetOwnerItem(item);
		}

		ADD_COMP(this, Collider2D);
		ADD_COMP(this, MeshRenderer);

		SET_MESH(this, L"RectMesh");
		SET_MATERIAL(this, itemNameTable[(UINT)item]);

		SET_POS_XYZ(this, -10.f, -10.f, -1.f);
		SET_SCALE_XYZ(this, 25.f * itemInvenDisplayScale[(UINT)item][0] * Texture::GetWidRatio()
			, 25.f * itemInvenDisplayScale[(UINT)item][1] * Texture::GetHeiRatio(), 0.f);

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
			if (bShopItem)
			{
				if(InteractUIManager::mCurUIType != InteractUIManager::eInteractUIType::BuyItem
					&& InteractUIManager::mCurUIType != InteractUIManager::eInteractUIType::BuyFail)
				{
					InteractUIManager::SetItemUI((int)mItem
						, InteractUIManager::eInteractUIType::ExItem
						, GET_POS(this)
						, true
						, GetCamera()
						, 15.f
					);
				}

				InteractUIManager::bItemHover = true;
			}else
			{
				if(StashManager::GetShopInventoryState() == RenderUpdate)
				{
					if (!GetMouseFollow() && nullptr == MouseManager::GetMouseFollow())
					{
						InteractUIManager::SetItemUI((int)mItem
							, InteractUIManager::eInteractUIType::InvenSellEx
							, GET_POS(this)
							, true
							, GetCamera()
							, 15.f
						);
					}
					
				}else
				{
					if (!GetMouseFollow() && nullptr == MouseManager::GetMouseFollow())
					{
						InteractUIManager::SetItemUI((int)mItem
							, InteractUIManager::eInteractUIType::InvenEx
							, GET_POS(this)
							, true
							, GetCamera()
							, 15.f
						);
					}
				}
				
				InteractUIManager::bItemHover = true;
			}

			if (Input::GetKeyDownOne(eKeyCode::LBUTTON))
			{
				if (!bShopItem)
					SetMouseFollow(GetMouseFollow() ? false : true);
				else
				{
					if(mPrevStashType != StashManager::eStashType::Inventory)
					{
						InteractUIManager::SetItemUI((int)mItem
							, InteractUIManager::eInteractUIType::BuyItem
							, GET_POS(this)
							, false
							, GetCamera()
							, 15.f
						);
					}
					else { mPrevStashType = mStashType; }
				}
			}
		}
		if (!bShopItem)
		{
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
