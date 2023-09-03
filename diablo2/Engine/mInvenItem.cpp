#include "mInvenItem.h"

#include "../engine_source/mInput.h"
#include "../engine_source/mApplication.h"
#include "../engine_source/mTransform.h"
#include "../engine_source/mMeshRenderer.h"
#include "../engine_source/mCollider2D.h"
#include "../engine_source/mStashManager.h"

#include "mEmptyRect.h"
#include "mMouseManager.h"


namespace m
{
	InvenItem::InvenItem(eItem item)
		: Item(item)
	{
		ADD_COMP(this, Collider2D);
		ADD_COMP(this, MeshRenderer);

		SET_MESH(this, L"RectMesh");
		SET_MATERIAL(this, itemNameTable[(UINT)item]);

		SET_POS_XYZ(this, -10.f, -10.f,-1.f);
		SET_SCALE_XYZ(this, 27.f * itemInvenDisplayScale[(UINT)item][0] * Texture::GetWidRatio()
			, 27.f * itemInvenDisplayScale[(UINT)item][1] * Texture::GetHeiRatio(), 0.f);

		prevPosition = GET_POS(this);

		//InvenItemInit();
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
	void InvenItem::InvenItemInit()
	{
		std::vector<EmptyRect*> invens = StashManager::GetInvens();
		MAKE_VEC2_F_VEC3(thisPosV2, GET_POS(this));
		MAKE_VEC2_F_VEC3(thisScaleV2, GET_SCALE(this));
		Vector2 subScale = thisScaleV2 / 2.0f;

		for (int i = 0; i < invens.size(); ++i)
		{
			Vector2 invenPos= invens[i]->GetPos();
			Vector2 invenSize= invens[i]->GetSize();
			eItem mItem = GetEItem();
			if (itemInvenDisplayScale[(UINT)mItem][0] > 1.f
				|| itemInvenDisplayScale[(UINT)mItem][1] > 1.f)
			{
				Vector2 sub1 = invenPos + (invenSize / 2.f);
				Vector2 subPos = Vector2(sub1.x + subScale.x, sub1.y - subScale.y);

				if (CheckItemSizeIntersectItem(subPos)) continue;

				prevPosition = Vector3(subPos.x , subPos.y, prevPosition.z);
				SET_POS_VEC(this, prevPosition);
				ChangeFillIntersectArea(subPos, true);
				break;
			}
			if (itemInvenDisplayScale[(UINT)mItem][0] == 1.f
				&& itemInvenDisplayScale[(UINT)mItem][1] == 1.f)
			{
				if (invens[i]->GetFill()) continue;


				if (!CheckItemSizeIntersectInventory(invens[i]->GetPos())) continue;
				if (CheckItemSizeIntersectItem(invens[i]->GetPos())) continue;

				prevPosition = Vector3(invenPos.x, invenPos.y, prevPosition.z);
				SET_POS_VEC(this, prevPosition);
				ChangeFillIntersectArea(invenPos, true);
				break;
			}
		}
	}

	void InvenItem::ChangeFillIntersectArea(Vector2 areaPos, bool _bV)
	{
		std::vector<EmptyRect*> invens = StashManager::GetInvens();
		for (int y = 0; y < 4; ++y)
		{
			for (int x = 0; x < 10; ++x)
			{
				Vector2 invenPos = invens[y * 10 + x]->GetPos();
				Vector2 invenSize = invens[y * 10 + x]->GetSize();
				MAKE_VEC2_F_VEC3(thisScale, GET_SCALE(this));

				if (Vector2::RectIntersectRect(invenPos, invenSize, areaPos, thisScale))
				{
					invens[y * 10 + x]->SetFill(_bV);
				}
			}
		}
	}

	bool InvenItem::CheckLimitIntersectItems(int limit)
	{
		std::vector<InvenItem*> invenItems = StashManager::GetInvenItems();
		int intersectItemCnt = 0;
		for (InvenItem* item : invenItems)
		{
			if (item->GetComponent<Collider2D>()->GetOnStay()
				|| item->GetComponent<Collider2D>()->GetOnEnter())
			{
				intersectItemCnt++;
			}
			if (intersectItemCnt > limit)
			{
				return false;
			}
		}
		return true;
	}

	void InvenItem::DeployItem()
	{
		std::vector<EmptyRect*> invens = StashManager::GetInvens();
		MAKE_VEC2_F_VEC3(thisPosV2, GET_POS(this));
		MAKE_VEC2_F_VEC3(thisScaleV2, GET_SCALE(this));

		for (int i = 0; i < invens.size(); ++i)
		{
			Vector2 invenPos = invens[i]->GetPos();
			Vector2 invenSize = invens[i]->GetSize();
			eItem mItem = GetEItem();
			if (itemInvenDisplayScale[(UINT)mItem][0] > 1.f
				|| itemInvenDisplayScale[(UINT)mItem][1] > 1.f)
			{
				Vector2 subScale = thisScaleV2 / 2.0f;
				Vector2 leftTop = Vector2(thisPosV2.x - subScale.x, thisPosV2.y + subScale.y);


				if (Vector2::PointIntersectRect(invenPos
												, invenSize
												, leftTop))
				{
					
					invenPos.x -= invens[i]->GetSize().x / 2.f;
					invenPos.y += invens[i]->GetSize().y / 2.f;

					Vector2 finalPos = Vector2(invenPos.x + thisScaleV2.x / 2.f, invenPos.y - thisScaleV2.y / 2.f);

					if (!CheckLimitIntersectItems(2)) continue;

					ChangeFillIntersectArea(GET_VEC2_F_VEC3_D(prevPosition), false);
					SET_POS_VEC(this, Vector3(finalPos.x, finalPos.y, prevPosition.z));
					prevPosition = Vector3(finalPos.x, finalPos.y, prevPosition.z);
					ChangeFillIntersectArea(finalPos, true);

					if (GetMouseFollow())
					{
						std::vector<InvenItem*> invenItems = StashManager::GetInvenItems();
						for (int i = 0; i < invenItems.size(); ++i)
						{
							if (this != invenItems[i])
							{
								if (invenItems[i]->GetComponent<Collider2D>()->GetOnEnter() ||
									invenItems[i]->GetComponent<Collider2D>()->GetOnStay())
								{
									invenItems[i]->SetMouseFollow(true);
									SET_POS_VEC(invenItems[i], GET_POS(this));
								}
							}
						}
					}
					return;
				}
			}
			else
			{
				if(invens[i]->MouseHover(prevPosition.z, GetCamera()))
				{
					if (!CheckLimitIntersectItems(2)) continue;
					if (!CheckItemSizeIntersectInventory(invens[i]->GetPos())) continue;

					ChangeFillIntersectArea(GET_VEC2_F_VEC3_D(prevPosition), false);
					Vector3 invenPosV3 = Vector3(invenPos.x, invenPos.y, prevPosition.z);
					SET_POS_VEC(this, invenPosV3);
					prevPosition = invenPosV3;
					ChangeFillIntersectArea(GET_VEC2_F_VEC3_D(GET_POS(this)), true);

					if (GetMouseFollow())
					{
						std::vector<InvenItem*> invenItems = StashManager::GetInvenItems();
						for (int i = 0; i < invenItems.size(); ++i)
						{
							if (this != invenItems[i])
							{
								if (invenItems[i]->GetComponent<Collider2D>()->GetOnEnter() ||
									invenItems[i]->GetComponent<Collider2D>()->GetOnStay())
								{
									invenItems[i]->SetMouseFollow(true);
									SET_POS_VEC(invenItems[i], GET_POS(this));
								}
							}
						}
					}
					return;
				}
			}
		}

		for (EmptyRect* eq : StashManager::GetEquiments())
		{
			Vector2 eqPos = eq->GetPos();
			Vector2 eqScale = eq->GetSize();
			if (Vector2::PointIntersectRect(eqPos, eqScale, thisPosV2))
			{
				SET_POS_VEC(this, Vector3(eqPos.x, eqPos.y, prevPosition.z));
				return;
			}
		}

		for(EmptyRect* pocket : StashManager::GetPockets())
		{
			Vector2 pocketPos = pocket->GetPos();
			Vector2 pocketScale = pocket->GetSize();
			if (Vector2::PointIntersectRect(pocketPos, pocketScale, thisPosV2))
			{
				SET_POS_VEC(this, Vector3(pocketPos.x, pocketPos.y, prevPosition.z));
				return;
			}
		}

		for (EmptyRect* pocket : StashManager::GetExPockets())
		{
			Vector2 pocketPos = pocket->GetPos();
			Vector2 pocketScale = pocket->GetSize();
			if (Vector2::PointIntersectRect(pocketPos, pocketScale, thisPosV2))
			{
				SET_POS_VEC(this, Vector3(pocketPos.x, pocketPos.y, prevPosition.z));
				return;
			}
		}

		for (EmptyRect* pocket : StashManager::GetShopInvens())
		{
			Vector2 pocketPos = pocket->GetPos();
			Vector2 pocketScale = pocket->GetSize();
			if (Vector2::PointIntersectRect(pocketPos, pocketScale, thisPosV2))
			{
				SET_POS_VEC(this, Vector3(pocketPos.x, pocketPos.y, prevPosition.z));
				return;
			}
		}
		SET_POS_VEC(this, prevPosition);
	}

	bool InvenItem::CheckItemSizeIntersectInventory(Vector2 comparePos)
	{
		MAKE_VEC2_F_VEC3(thisPosV2, comparePos);
		MAKE_VEC2_F_VEC3(thisScaleV2, GET_SCALE(this));

		EmptyRect* inC = StashManager::GetInvensCollider();
		Vector2 inventoryOutLinePos = inC->GetPos();
		Vector2 inventoryOutLineScale = inC->GetSize();
		eItem mItem = GetEItem();
		if (itemInvenDisplayScale[(UINT)mItem][0] > 1.f
			|| itemInvenDisplayScale[(UINT)mItem][1] > 1.f)
		{
			if (Vector2::RectIndexesIntersectRectIndexes(inventoryOutLinePos, inventoryOutLineScale, thisPosV2, thisScaleV2))
			{
				return false;
			}
		}
		return true;
	}

	bool InvenItem::CheckItemSizeIntersectItem(Vector2 comparePos)
	{
		std::vector<InvenItem*> invenItems = StashManager::GetInvenItems();

		MAKE_VEC2_F_VEC3(thisPosV2, comparePos);
		MAKE_VEC2_F_VEC3(thisScaleV2, GET_SCALE(this));
		eItem mItem = GetEItem();
		if (itemInvenDisplayScale[(UINT)mItem][0] > 1.f
			|| itemInvenDisplayScale[(UINT)mItem][1] > 1.f)
		{
			for (InvenItem* item : invenItems)
			{
				MAKE_VEC2_F_VEC3(itemPosV2, GET_POS(item));
				MAKE_VEC2_F_VEC3(itemScaleV2, GET_SCALE(item));

				if (Vector2::RectIntersectRect(itemPosV2, itemScaleV2, thisPosV2, thisScaleV2))
					return true;
			}
		}
		return false;
	}
}
