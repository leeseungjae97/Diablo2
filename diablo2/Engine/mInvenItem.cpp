#include "mInvenItem.h"

#include "../engine_source/mInput.h"
#include "../engine_source/mApplication.h"
#include "../engine_source/mTransform.h"
#include "../engine_source/mMeshRenderer.h"
#include "../engine_source/mCollider2D.h"

#include "mInven.h"
#include "mInventory.h"
#include "mMouseManager.h"


namespace m
{
	InvenItem::InvenItem(eItem item, Inventory* inventory)
		: Item(itemTypeTable[(UINT)item])
		, mInventory(inventory)
		, bSetMouseFollow(false)
		, mItem(item)
	{
		ADD_COMP(this, Collider2D);
		ADD_COMP(this, MeshRenderer);

		SET_MESH(this, L"RectMesh");
		SET_MATERIAL(this, itemNameTable[(UINT)mItem]);

		SET_SCALE_XYZ(this, 27.f * itemInvenDisplayScale[(UINT)mItem][0] * Texture::GetWidRatio(), 27.f * itemInvenDisplayScale[(UINT)mItem][1] * Texture::GetHeiRatio(), 0.f);

		InvenItemInit();
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
				DeployItem();
				bSetMouseFollow = bSetMouseFollow ? false : true;
			}
			if (bSetMouseFollow)
			{
				MAKE_POS(pos, this);
				Vector3 unprojMousePos = Input::GetUnprojectionMousePos(pos.z
																		, GetCamera()->GetPrivateProjectionMatrix(), GetCamera()->GetPrivateViewMatrix());
				unprojMousePos.z = pos.z;
				SET_POS_VEC(this, unprojMousePos);
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
	void InvenItem::InvenItemInit()
	{
		std::vector<Inven*> invens = mInventory->GetInvens();
		MAKE_VEC2_F_VEC3(thisPosV2, GET_POS(this));
		MAKE_VEC2_F_VEC3(thisScaleV2, GET_SCALE(this));
		Vector2 subScale = thisScaleV2 / 2.0f;

		for (int i = 0; i < invens.size(); ++i)
		{
			Vector2 invenPos= invens[i]->GetPos();
			Vector2 invenSize= invens[i]->GetSize();
			if (itemInvenDisplayScale[(UINT)mItem][0] > 1.f
				|| itemInvenDisplayScale[(UINT)mItem][1] > 1.f)
			{
				//Vector2 subScale = thisScaleV2 / 2.0f;
				//Vector2 leftTop = Vector2(thisPosV2.x - subScale.x, thisPosV2.y + subScale.y);
				//if (Vector2::PointIntersectRect(GET_VEC2_F_VEC3_D(GET_POS(invens[i]))
				//								, GET_VEC2_F_VEC3_D(GET_SCALE(invens[i]))
				//								, leftTop))
				//{
				//	
				//}
				Vector2 sub1 = invenPos + (invenSize / 2.f);
				Vector2 subPos = Vector2(sub1.x + subScale.x, sub1.y - subScale.y);
				//Vector3 subPos = Vector3(sub1.x, sub1.y - subScale.y, prevPosition.z);

				if (CheckItemSizeIntersectItem(subPos)) continue;
				//if (!CheckLimitIntersectItems(0)) continue;

				prevPosition = Vector3(subPos.x , subPos.y, prevPosition.z);
				SET_POS_VEC(this, prevPosition);
				ChangeFillIntersectArea(subPos, true);
				break;
			}
			else
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
		std::vector<Inven*> invens = mInventory->GetInvens();
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
		std::vector<InvenItem*> invenItems = mInventory->GetInvenItems();
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
		std::vector<Inven*> invens = mInventory->GetInvens();
		MAKE_VEC2_F_VEC3(thisPosV2, GET_POS(this));
		MAKE_VEC2_F_VEC3(thisScaleV2, GET_SCALE(this));
		
		Vector3 mousePos = MouseManager::UnprojectionMousePos(GET_POS(this).z, GetCamera());
		MAKE_VEC2_F_VEC3(mousePosV2, mousePos);
		for (int i = 0; i < invens.size(); ++i)
		{
			Vector2 invenPos = invens[i]->GetPos();
			Vector2 invenSize = invens[i]->GetSize();

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
					//if (CheckItemSizeIntersectItem(finalPos)) continue;

					ChangeFillIntersectArea(GET_VEC2_F_VEC3_D(prevPosition), false);
					SET_POS_VEC(this, Vector3(finalPos.x, finalPos.y, prevPosition.z));
					prevPosition = Vector3(finalPos.x, finalPos.y, prevPosition.z);
					ChangeFillIntersectArea(finalPos, true);

					if (bSetMouseFollow)
					{
						std::vector<InvenItem*> invenItems = mInventory->GetInvenItems();
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
				if(Vector2::PointIntersectRect(invens[i]->GetPos(), invens[i]->GetSize(), mousePosV2))
				{
					if (!CheckLimitIntersectItems(2)) continue;
					if (!CheckItemSizeIntersectInventory(invens[i]->GetPos())) continue;

					ChangeFillIntersectArea(GET_VEC2_F_VEC3_D(prevPosition), false);
					Vector3 invenPosV3 = Vector3(invenPos.x, invenPos.y, prevPosition.z);
					SET_POS_VEC(this, invenPosV3);
					prevPosition = invenPosV3;
					ChangeFillIntersectArea(GET_VEC2_F_VEC3_D(GET_POS(this)), true);

					if (bSetMouseFollow)
					{
						std::vector<InvenItem*> invenItems = mInventory->GetInvenItems();
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

		for (Inven* eq : mInventory->GetEquiments())
		{
			Vector2 eqPos = eq->GetPos();
			Vector2 eqScale = eq->GetSize();
			if (Vector2::RectIntersectRect(eqPos, eqScale, thisPosV2, thisScaleV2))
			{
				SET_POS_VEC(this, Vector3(eqPos.x, eqPos.y, prevPosition.z));
				return;
			}
		}
		SET_POS_VEC(this, prevPosition);
	}
	bool InvenItem::CheckItemSizeIntersectInventory(Vector2 comparePos)
	{
		MAKE_VEC2_F_VEC3(thisPosV2, comparePos);
		MAKE_VEC2_F_VEC3(thisScaleV2, GET_SCALE(this));

		Inven* inC = mInventory->GetInvensCollider();
		inventoryOutLinePos = inC->GetPos();
		inventoryOutLineScale = inC->GetSize();
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
		std::vector<InvenItem*> invenItems = mInventory->GetInvenItems();

		MAKE_VEC2_F_VEC3(thisPosV2, comparePos);
		MAKE_VEC2_F_VEC3(thisScaleV2, GET_SCALE(this));
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
