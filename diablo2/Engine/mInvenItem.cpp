#include "mInvenItem.h"

#include "../engine_source/mInput.h"
#include "../engine_source/mApplication.h"
#include "../engine_source/mTransform.h"
#include "../engine_source/mMeshRenderer.h"
#include "../engine_source/mCollider2D.h"

#include "mInven.h"
#include "mInventory.h"


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
				MAKE_VEC2_F_VEC3(sub1, GET_POS(invens[i]));
				sub1 += GET_VEC2_F_VEC3_D(GET_SCALE(invens[i])) / 2.f;

				Vector3 subPos = Vector3(sub1.x + subScale.x, sub1.y - subScale.y, prevPosition.z);
				//Vector3 subPos = Vector3(sub1.x, sub1.y - subScale.y, prevPosition.z);

				if (CheckItemSizeIntersectItem(subPos)) continue;
				//if (!CheckLimitIntersectItems(0)) continue;

				prevPosition = subPos;
				SET_POS_VEC(this, prevPosition);
				ChangeBoolIntersectArea(prevPosition, true);
				break;
			}
			else
			{
				if (invens[i]->GetFill()) continue;


				if (!CheckItemSizeIntersectInventory(GET_POS(invens[i]))) continue;
				if (CheckItemSizeIntersectItem(GET_POS(invens[i]))) continue;

				prevPosition = GET_POS(invens[i]);
				SET_POS_VEC(this, prevPosition);
				ChangeBoolIntersectArea(prevPosition, true);
				break;
			}
			
		}
	}
	void InvenItem::ChangeBoolIntersectArea(Vector3 areaPos, bool _bV)
	{
		std::vector<Inven*> invens = mInventory->GetInvens();
		for (int y = 0; y < 4; ++y)
		{
			for (int x = 0; x < 10; ++x)
			{
				MAKE_VEC2_F_VEC3(invenPos, GET_POS(invens[y * 10 + x]));
				MAKE_VEC2_F_VEC3(invenScale, GET_SCALE(invens[y * 10 + x]));
				MAKE_VEC2_F_VEC3(prevPos, areaPos);
				MAKE_VEC2_F_VEC3(thisScale, GET_SCALE(this));

				if (Vector2::RectIntersectRect(invenPos, invenScale, prevPos, thisScale))
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
		

		for (int i = 0; i < invens.size(); ++i)
		{
			if (itemInvenDisplayScale[(UINT)mItem][0] > 1.f
				|| itemInvenDisplayScale[(UINT)mItem][1] > 1.f)
			{
				Vector2 subScale = thisScaleV2 / 2.0f;
				Vector2 leftTop = Vector2(thisPosV2.x - subScale.x, thisPosV2.y + subScale.y);
				if (Vector2::PointIntersectRect(GET_VEC2_F_VEC3_D(GET_POS(invens[i]))
												, GET_VEC2_F_VEC3_D(GET_SCALE(invens[i]))
												, leftTop))
				{
					MAKE_VEC2_F_VEC3(invenPos, GET_POS(invens[i]));
					Vector2 invenScale = GET_VEC2_F_VEC3_D(GET_SCALE(invens[i]));
					invenPos.x -= invenScale.x / 2.f;
					invenPos.y += invenScale.y / 2.f;

					Vector3 finalPos = Vector3(invenPos.x + thisScaleV2.x / 2.f, invenPos.y - thisScaleV2.y / 2.f, prevPosition.z);

					if (!CheckLimitIntersectItems(2)) continue;
					//if (CheckItemSizeIntersectItem(finalPos)) continue;

					ChangeBoolIntersectArea(prevPosition, false);
					SET_POS_VEC(this, finalPos);
					prevPosition = finalPos;
					ChangeBoolIntersectArea(finalPos, true);

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
				if (invens[i]->GetHover())
				{
					if (!CheckLimitIntersectItems(2)) continue;
					if (!CheckItemSizeIntersectInventory(GET_POS(invens[i]))) continue;

					ChangeBoolIntersectArea(prevPosition, false);
					SET_POS_VEC(this, GET_POS(invens[i]));
					prevPosition = GET_POS(invens[i]);
					ChangeBoolIntersectArea(GET_POS(this), true);

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
			MAKE_VEC2_F_VEC3(eqPos, GET_POS(eq));
			MAKE_VEC2_F_VEC3(eqScale, GET_SCALE(eq));
			if (Vector2::RectIntersectRect(eqPos, eqScale, thisPosV2, thisScaleV2))
			{
				SET_POS_VEC(this, GET_POS(eq));
				return;
			}
		}
		SET_POS_VEC(this, prevPosition);
	}
	bool InvenItem::CheckItemSizeIntersectInventory(Vector3 comparePos)
	{
		MAKE_VEC2_F_VEC3(thisPosV2, comparePos);
		MAKE_VEC2_F_VEC3(thisScaleV2, GET_SCALE(this));

		GameObject* inC = mInventory->GetInvensCollider();

		GET_VEC2_F_VEC3(inventoryOutLinePos, GET_POS(inC));
		GET_VEC2_F_VEC3(inventoryOutLineScale, GET_SCALE(inC));
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
	bool InvenItem::CheckItemSizeIntersectItem(Vector3 comparePos)
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