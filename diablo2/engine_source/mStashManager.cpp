#include "mStashManager.h"
#include "mMouseManager.h"

#include "../Engine/mItem.h"
#include "../Engine/mEmptyRect.h"
#include "../Engine/mInvenItem.h"

namespace m
{
	//std::vector<StashManager::Stash> StashManager::stashPositions;

	std::vector<EmptyRect*> StashManager::invens = {};
	std::vector<EmptyRect*> StashManager::equiments = {};
	std::vector<EmptyRect*> StashManager::shopInvens = {};
	std::vector<EmptyRect*> StashManager::pockets = {};
	std::vector<EmptyRect*> StashManager::exPockets = {};

	std::vector<InvenItem*> StashManager::invenItems = {};
	std::vector<InvenItem*> StashManager::pocketItems = {};
	std::vector<InvenItem*> StashManager::exPocketItems = {};
	std::vector<InvenItem*> StashManager::shopItems = {};

	EmptyRect* StashManager::invenWeapon1Left = nullptr;
	EmptyRect* StashManager::invenWeapon1Right = nullptr;
	EmptyRect* StashManager::invenRingLeft = nullptr;
	EmptyRect* StashManager::invenRingRight = nullptr;
	EmptyRect* StashManager::invenAmulet = nullptr;
	EmptyRect* StashManager::invenBelt = nullptr;
	EmptyRect* StashManager::invenHelmet = nullptr;
	EmptyRect* StashManager::invenShoes = nullptr;
	EmptyRect* StashManager::invenGlove = nullptr;
	EmptyRect* StashManager::invenArmor = nullptr;

	Camera* StashManager::mCurCamera = nullptr;

	EmptyRect* StashManager::invensCollider = nullptr;
	EmptyRect* StashManager::shopInvensCollider = nullptr;
	EmptyRect* StashManager::pocketCollider = nullptr;
	EmptyRect* StashManager::exPocketCollider = nullptr;

	GameObject::eState StashManager::eInventoryState = GameObject::eState::NoRenderNoUpdate;
	GameObject::eState StashManager::eShopInventoryState = GameObject::eState::NoRenderNoUpdate;
	GameObject::eState StashManager::eExPocketState = GameObject::eState::NoRenderNoUpdate;

	//StashManager::eStashType StashManager::GetHoverStashType()
	//{
	//	Vector3 mousePosV3 = MouseManager::UnprojectionMousePos(-1.f, mCurCamera);
	//	Vector2 mousePosV2 = Vector2(mousePosV3.x, mousePosV3.y);

	//	for (Stash stash : stashPositions)
	//	{
	//		Vector2 sPos = stash.pos;
	//		Vector2 sSize = stash.size;
	//		if (Vector2::PointIntersectRect(sPos, sSize, mousePosV2))
	//		{
	//			return stash.type;
	//		}
	//	}
	//	return eStashType::End;
	//}
	void StashManager::Initialize()
	{
		InitStash();
	}

	void StashManager::InitStash()
	{
#pragma region Inventory
		for (int y = 0; y < 4; y++)
		{
			for (int x = 0; x < 10; x++)
			{
				EmptyRect* invenRect = new EmptyRect();
				invenRect->SetPos(Vector2(65.f + ((288.f / 10.f) * Texture::GetWidRatio() * x)
					, -51.f + (-(114.f / 4.f) * Texture::GetHeiRatio() * y)));
				invenRect->SetSize(Vector2((288.f / 10.f) * Texture::GetWidRatio()
					, (114.f / 4.f) * Texture::GetHeiRatio()));
				invens.push_back(invenRect);
			}
		}

		invenWeapon1Left = new EmptyRect();
		invenWeapon1Left->SetSize(60.f * Texture::GetWidRatio()
			, 115.f * Texture::GetHeiRatio());
		invenWeapon1Right = new EmptyRect();
		invenWeapon1Right->SetSize(60.f * Texture::GetWidRatio()
			, 116.f * Texture::GetHeiRatio());
		invenRingLeft = new EmptyRect();
		invenRingLeft->SetSize(30.f * Texture::GetWidRatio()
			, 31.f * Texture::GetHeiRatio());
		invenRingRight = new EmptyRect();
		invenRingRight->SetSize(30.f * Texture::GetWidRatio()
			, 31.f * Texture::GetHeiRatio());
		invenAmulet = new EmptyRect();
		invenAmulet->SetSize(30.f * Texture::GetWidRatio()
			, 31.f * Texture::GetHeiRatio());
		invenBelt = new EmptyRect();
		invenBelt->SetSize(60.f * Texture::GetWidRatio()
			, 31.f * Texture::GetHeiRatio());
		invenHelmet = new EmptyRect();
		invenHelmet->SetSize(60.f * Texture::GetWidRatio()
			, 60.f * Texture::GetHeiRatio());
		invenShoes = new EmptyRect();
		invenShoes->SetSize(60.f * Texture::GetWidRatio()
			, 61.f * Texture::GetHeiRatio());
		invenGlove = new EmptyRect();
		invenGlove->SetSize(60.f * Texture::GetWidRatio()
			, 61.f * Texture::GetHeiRatio());
		invenArmor = new EmptyRect();
		invenArmor->SetSize(62.f * Texture::GetWidRatio()
			, 89.f * Texture::GetHeiRatio());

		invenWeapon1Left->SetPos((17.f * Texture::GetWidRatio())
			+ invenWeapon1Left->GetSize().x / 2.f, (RESOL_H_HEI - 110.f * Texture::GetHeiRatio()) - invenWeapon1Left->GetSize().y / 2.f);

		invenWeapon1Right->SetPos((248.f * Texture::GetWidRatio())
			+ invenWeapon1Right->GetSize().x / 2.f, (RESOL_H_HEI - 110.f * Texture::GetHeiRatio()) - invenWeapon1Right->GetSize().y / 2.f);

		invenRingLeft->SetPos((91.f * Texture::GetWidRatio())
			+ invenRingLeft->GetSize().x / 2.f, (RESOL_H_HEI - 240.f * Texture::GetHeiRatio()) - invenRingLeft->GetSize().y / 2.f);

		invenRingRight->SetPos((205.f * Texture::GetWidRatio())
			+ invenRingRight->GetSize().x / 2.f, (RESOL_H_HEI - 239.f * Texture::GetHeiRatio()) - invenRingRight->GetSize().y / 2.f);

		invenAmulet->SetPos((205.f * Texture::GetWidRatio())
			+ invenAmulet->GetSize().x / 2.f, (RESOL_H_HEI - 95.f * Texture::GetHeiRatio()) - invenAmulet->GetSize().y / 2.f);

		invenBelt->SetPos((133.f * Texture::GetWidRatio())
			+ invenBelt->GetSize().x / 2.f, (RESOL_H_HEI - 240.f * Texture::GetHeiRatio()) - invenBelt->GetSize().y / 2.f);

		invenHelmet->SetPos((132.f * Texture::GetWidRatio())
			+ invenHelmet->GetSize().x / 2.f, (RESOL_H_HEI - 65.0f * Texture::GetHeiRatio()) - invenHelmet->GetSize().y / 2.f);

		invenShoes->SetPos((248.f * Texture::GetWidRatio())
			+ invenShoes->GetSize().x / 2.f, (RESOL_H_HEI - 240.f * Texture::GetHeiRatio()) - invenShoes->GetSize().y / 2.f);

		invenGlove->SetPos((17.f * Texture::GetWidRatio())
			+ invenGlove->GetSize().x / 2.f, (RESOL_H_HEI - 240.f * Texture::GetHeiRatio()) - invenGlove->GetSize().y / 2.f);

		invenArmor->SetPos((132.f * Texture::GetWidRatio())
			+ invenArmor->GetSize().x / 2.f, (RESOL_H_HEI - 138.f * Texture::GetHeiRatio()) - invenArmor->GetSize().y / 2.f);

		equiments.push_back(invenWeapon1Left);
		equiments.push_back(invenWeapon1Right);
		equiments.push_back(invenRingLeft);
		equiments.push_back(invenRingRight);
		equiments.push_back(invenAmulet);
		equiments.push_back(invenBelt);
		equiments.push_back(invenHelmet);
		equiments.push_back(invenShoes);
		equiments.push_back(invenGlove);
		equiments.push_back(invenArmor);
#pragma endregion
#pragma region Pocket
		Vector2 bottomUIPosV2 = Vector2(0.f, -RESOL_H_HEI + 104.f * Texture::GetHeiRatio() / 2.f);

		for (int i = 0; i < 4; ++i)
		{
			EmptyRect* pocket = new EmptyRect();
			pocket->SetSize(30.f * Texture::GetWidRatio()
				, 31.f * Texture::GetHeiRatio());
			pocket->SetPos(bottomUIPosV2.x + 23.f * Texture::GetWidRatio() + (pocket->GetSize().x / 2.f) + (30.f * i) * Texture::GetWidRatio()
				, bottomUIPosV2.y - pocket->GetSize().y / 2.f - 14.f * Texture::GetHeiRatio());

			pockets.push_back(pocket);
		}

		for (int i = 0; i < 8; ++i)
		{
			EmptyRect* pocket = new EmptyRect();
			pocket->SetSize(30.f * Texture::GetWidRatio()
				, 31.f * Texture::GetHeiRatio());
			pocket->SetPos(bottomUIPosV2.x + 23.f * Texture::GetWidRatio() + (pocket->GetSize().x / 2.f) + (30 * (i % 4)) * Texture::GetWidRatio()
				, bottomUIPosV2.y - pocket->GetSize().y / 2.f - 14.f * Texture::GetHeiRatio() + (pocket->GetSize().y * (i / 4 + 1)));
			exPockets.push_back(pocket);
		}

		//for (int i = 0; i < pockets.size(); ++i)
		//	InitStashPos(pockets[i]->GetSize(), pockets[i]->GetSize(), eStashType::PocketInven);

		//for (int i = 0; i < exPockets.size(); ++i)
		//	InitStashPos(exPockets[i]->GetSize(), exPockets[i]->GetSize(), eStashType::ExPocketInven);

		//for (int i = 0; i < invens.size(); ++i)
		//	InitStashPos(invens[i]->GetSize(), invens[i]->GetSize(), eStashType::Inventory);

		//for (int i = 0; i < equiments.size(); ++i)
		//	InitStashPos(equiments[i]->GetSize(), equiments[i]->GetSize(), eStashType::Equiment);

		//for (int i = 0; i < shopInvens.size(); ++i)
		//	InitStashPos(shopInvens[i]->GetSize(), shopInvens[i]->GetSize(), eStashType::Shop);
#pragma endregion
#pragma region Collider

		shopInvensCollider = new EmptyRect();

		invensCollider = new EmptyRect();
		invensCollider->SetSize(300.f * Texture::GetWidRatio(), 120.f * Texture::GetHeiRatio());
		invensCollider->SetPos((15.f + (300.f / 2.f)) * Texture::GetWidRatio(), (-15.f + (-120.f / 2.f)) * Texture::GetHeiRatio());

		pocketCollider = new EmptyRect();
		pocketCollider->SetPos(pockets[1]->GetPos().x + pockets[1]->GetSize().x / 2.f
			, pockets[0]->GetPos().y + 3.f);
		pocketCollider->SetSize(
			30.f * 4.f * Texture::GetWidRatio()
			, (31.f * Texture::GetHeiRatio()) + 3.f);

		exPocketCollider = new EmptyRect();

		exPocketCollider->SetPos(
			(exPockets[1]->GetPos().x + exPockets[1]->GetSize().x / 2.f) + 1.f
			, (exPockets[0]->GetPos().y + exPockets[0]->GetSize().y / 2.f) + 3.f
		);
		SHARED_MAT exMat = RESOURCE_FIND(Material, L"exPocket");
		UINT hei = exMat->GetTexture()->GetMetaDataHeight();
		UINT wid = exMat->GetTexture()->GetMetaDataWidth();
		exPocketCollider->SetSize(wid, hei);
#pragma endregion
	}

	void StashManager::InitStashPos(Vector2 pos, Vector2 size, eStashType type)
	{
		//stashPositions.push_back({ pos, size, type });
	}

	void StashManager::InitItems(eStashType type)
	{
		std::vector<EmptyRect*>* _invens = nullptr;
		std::vector<InvenItem*>* _invenItems = nullptr;

		if (type == eStashType::Inventory)
		{
			_invens = &invens;
			_invenItems = &invenItems;
		}
		if (type == eStashType::Shop)
		{
			_invens = &shopInvens;
			_invenItems = &shopItems;
		}

		for (int j = 0; j < _invenItems->size(); ++j)
		{
			InvenItem* curItem = (*_invenItems)[j];
			Vector3 curPos = GET_POS(curItem);
			MAKE_VEC2_F_VEC3(thisPosV2, curPos);
			MAKE_VEC2_F_VEC3(thisScaleV2, GET_SCALE(curItem));
			Vector2 subScale = thisScaleV2 / 2.0f;

			for (int i = 0; i < _invens->size(); ++i)
			{
				EmptyRect* curInven = (*_invens)[i];
				Vector2 invenPos = curInven->GetPos();
				Vector2 invenSize = curInven->GetSize();
				eItem mItem = curItem->GetEItem();

				if (itemInvenDisplayScale[(UINT)mItem][0] > 1.f
					|| itemInvenDisplayScale[(UINT)mItem][1] > 1.f)
				{
					Vector2 invenLeftTop = invenPos + (invenSize / 2.f);
					Vector2 centerPosFromInvenLeftTop = Vector2(invenLeftTop.x + subScale.x, invenLeftTop.y - subScale.y);

					if (CheckItemCenterPosIntersectItem(centerPosFromInvenLeftTop, curItem, type)) continue;

					curItem->SetPrevPosition(Vector3(centerPosFromInvenLeftTop.x, centerPosFromInvenLeftTop.y, curPos.z));
					SET_POS_XYZ(curItem, centerPosFromInvenLeftTop.x, centerPosFromInvenLeftTop.y, curPos.z);
					ChangeFillIntersectArea(centerPosFromInvenLeftTop, true, curItem, type);
					break;
				}
				if (itemInvenDisplayScale[(UINT)mItem][0] == 1.f
					&& itemInvenDisplayScale[(UINT)mItem][1] == 1.f)
				{
					if (curInven->GetFill()) continue;

					if (CheckItemSizeIntersectOutline(invenPos, curItem, type)) continue;
					if (CheckItemCenterPosIntersectItem(invenPos, curItem, type)) continue;

					curItem->SetPrevPosition(Vector3(invenPos.x, invenPos.y, curPos.z));
					SET_POS_XYZ(curItem, invenPos.x, invenPos.y, curPos.z);
					ChangeFillIntersectArea(invenPos, true, curItem, type);
					break;
				}
			}
		}

	}

	void StashManager::Release()
	{
		for (EmptyRect* rect : invens)
		{
			if (rect)
			{
				delete rect;
				rect = nullptr;
			}
		}
		for (EmptyRect* rect : equiments)
		{
			if (rect)
			{
				delete rect;
				rect = nullptr;
			}
		}
		for (EmptyRect* rect : shopInvens)
		{
			if (rect)
			{
				delete rect;
				rect = nullptr;
			}
		}
		for (EmptyRect* rect : pockets)
		{
			if (rect)
			{
				delete rect;
				rect = nullptr;
			}
		}
		for (EmptyRect* rect : exPockets)
		{
			if (rect)
			{
				delete rect;
				rect = nullptr;
			}
		}
		invenItems.clear();
		pocketItems.clear();
		shopItems.clear();

		if (invensCollider)
			delete invensCollider;
		if (shopInvensCollider)
			delete shopInvensCollider;
		if (pocketCollider)
			delete pocketCollider;
		if (exPocketCollider)
			delete exPocketCollider;
	}

	void StashManager::Update()
	{
		if (nullptr == mCurCamera) mCurCamera = SceneManager::GetActiveScene()->GetSceneUICamera();

		inventoryUpdate();
		pocketInventoryUpdate();
		shopInventoryUpdate();

		ItemDeploy();
		MouseManager::FreeMouseFollow();
	}

	bool StashManager::ItemDeploy()
	{
		if (nullptr == MouseManager::GetMouseFollow()
			|| !Input::GetKeyDownOne(eKeyCode::LBUTTON)) return false;

		InvenItem* item = MouseManager::GetMouseFollow();
		eStashType type = eStashType::End;

		if(Vector2::PointIntersectRect(invensCollider->GetPos(), 
			invensCollider->GetSize(), GET_VEC2_F_VEC3_D(GET_POS(item))))
		{
			type = eStashType::Inventory;
			
		}
		//if (Vector2::PointIntersectRect(shopInvensCollider->GetPos(),
		//	shopInvensCollider->GetSize(), GET_VEC2_F_VEC3_D(GET_POS(item))))
		//{
		//	type = eStashType::Shop;
		//}

		if(type!= eStashType::End)
		{
			if (DeployTetris(type))
				return true;
		}

		type = eStashType::End;

		if (Vector2::PointIntersectRect(pocketCollider->GetPos(),
			pocketCollider->GetSize(), GET_VEC2_F_VEC3_D(GET_POS(item))))
		{
			type = eStashType::PocketInven;
		}
		if (Vector2::PointIntersectRect(exPocketCollider->GetPos(),
			exPocketCollider->GetSize(), GET_VEC2_F_VEC3_D(GET_POS(item))))
		{
			type = eStashType::ExPocketInven;
		}

		if (type != eStashType::End)
		{
			if (DeployException(type, {}, { (int)eItemType::Posion }))
				return true;
		}

		if (DeployException(eStashType::Equiment, { (int)eItemType::Posion, (int)eItemType::Scroll }, {}))
			return true;

		SET_POS_VEC(item, item->GetPrevPosition());

		return false;
	}
	bool StashManager::DeployException(eStashType type, std::vector<int> exceptType, std::vector<int> acceptType)
	{
		InvenItem* item = MouseManager::GetMouseFollow();

		if(!exceptType.empty())
		{
			for (int except : exceptType)
				if ((eItemType)except == item->GetItemType()) return false;
		}

		if(!acceptType.empty())
		{
			bool matchType = false;
			for (int except : acceptType)
				if ((eItemType)except == item->GetItemType()) matchType = true;

			if (!matchType) return false;
		}
		

		Vector3 prevPosition = item->GetPrevPosition();

		std::vector<EmptyRect*>* _invens = nullptr;

		if (type == eStashType::PocketInven) _invens = &pockets;
		if (type == eStashType::ExPocketInven) _invens = &exPockets;
		if (type == eStashType::Equiment) _invens = &equiments;

		MAKE_VEC2_F_VEC3(thisPosV2, GET_POS(item));

		for (int i = 0; i < _invens->size(); ++i)
		{
			Vector2 itemPos = (*_invens)[i]->GetPos();
			Vector2 itemScale = (*_invens)[i]->GetSize();
			if (Vector2::PointIntersectRect(itemPos, itemScale, thisPosV2))
			{
				ChangeFillIntersectArea(GET_VEC2_F_VEC3_D(prevPosition)
					, false, item, item->GetStashType());

				SET_POS_VEC(item, Vector3(itemPos.x, itemPos.y, prevPosition.z));
				MoveOtherStash(item, type);

				ChangeFillIntersectArea(Vector2(itemPos.x, itemPos.y)
					, true, item, type);

				return true;
			}
		}
		return false;
	}
	bool StashManager::DeployTetris(eStashType type)
	{
		if (nullptr == MouseManager::GetMouseFollow()
			|| !Input::GetKeyDownOne(eKeyCode::LBUTTON)) return false;

		InvenItem* item = MouseManager::GetMouseFollow();
		Vector3 prevPosition = item->GetPrevPosition();
		eItem mItem = item->GetEItem();

		MAKE_VEC2_F_VEC3(thisPosV2, GET_POS(item));
		MAKE_VEC2_F_VEC3(thisScaleV2, GET_SCALE(item));

		std::vector<EmptyRect*>* _invens = nullptr;
		std::vector<InvenItem*>* _invenItems = nullptr;

		if (type == eStashType::Inventory)
		{
			_invens = &invens;
			_invenItems = &invenItems;
		}
		if (type == eStashType::Shop)
		{
			_invens = &shopInvens;
			_invenItems = &shopItems;
		}

		for (int i = 0; i < _invens->size(); ++i)
		{
			Vector2 invenPos = (*_invens)[i]->GetPos();
			Vector2 invenSize = (*_invens)[i]->GetSize();

			if (itemInvenDisplayScale[(UINT)mItem][0] > 1.f
				|| itemInvenDisplayScale[(UINT)mItem][1] > 1.f)
			{
				Vector2 subScale = thisScaleV2 / 2.0f;
				Vector2 leftTop = Vector2(thisPosV2.x - subScale.x, thisPosV2.y + subScale.y);

				if (Vector2::PointIntersectRect(invenPos
					, invenSize
					, leftTop))
				{
					invenPos.x -= (*_invens)[i]->GetSize().x / 2.f;
					invenPos.y += (*_invens)[i]->GetSize().y / 2.f;

					Vector2 centerPosInvenleftTopPlus = Vector2(invenPos.x + thisScaleV2.x / 2.f, invenPos.y - thisScaleV2.y / 2.f);

					// 충돌한 위치에 이미 아이템이 2개 이상있다면 continue
					if (CheckLimitIntersectItems(2, type)) continue;
					if (CheckItemSizeIntersectOutline(centerPosInvenleftTopPlus, item, type)) continue;

					ChangeFillIntersectArea(GET_VEC2_F_VEC3_D(prevPosition), false, item, type);

					SET_POS_VEC(item, Vector3(centerPosInvenleftTopPlus.x, centerPosInvenleftTopPlus.y, prevPosition.z));
					item->SetPrevPosition(Vector3(centerPosInvenleftTopPlus.x, centerPosInvenleftTopPlus.y, prevPosition.z));

					ChangeFillIntersectArea(centerPosInvenleftTopPlus, true, item, type);

					//if(CheckInvensFill(i, item, type))
					//{
					//}
					for (int i = 0; i < _invenItems->size(); ++i)
					{
						if (item != (*_invenItems)[i])
						{
							// 한개만 충돌한 경우
							if ((*_invenItems)[i]->GetComponent<Collider2D>()->GetOnEnter() ||
								(*_invenItems)[i]->GetComponent<Collider2D>()->GetOnStay())
							{
								// 이미 hover인 경우 예외처리.
								if(!(*_invenItems)[i]->GetHover())
								    (*_invenItems)[i]->SetMouseFollow(true);

							    //item->SetMouseFollow(false);
								//SET_POS_VEC((*_invenItems)[i], GET_POS(item));
								break;
							}
						}
					}
					MoveOtherStash(item, type);
					return true;
				}
			}
			if (itemInvenDisplayScale[(UINT)mItem][0] == 1.f
				&& itemInvenDisplayScale[(UINT)mItem][1] == 1.f)
			{
				// 아이템의 크기가 1, 1 이하인 것.
				if ((*_invens)[i]->MouseHover(prevPosition.z, mCurCamera))
				{
					if (CheckLimitIntersectItems(2, type)) continue;
					if (CheckItemSizeIntersectOutline(invenPos, item, type)) continue;

					ChangeFillIntersectArea(GET_VEC2_F_VEC3_D(prevPosition), false, item, type);
					Vector3 invenPosV3 = Vector3(invenPos.x, invenPos.y, prevPosition.z);
					SET_POS_VEC(item, invenPosV3);
					item->SetPrevPosition(invenPosV3);
					ChangeFillIntersectArea(GET_VEC2_F_VEC3_D(GET_POS(item)), true, item, type);

					//for (int i = 0; i < _invenItems->size(); ++i)
					//{
					//	if (item != (*_invenItems)[i])
					//	{
					//		if ((*_invenItems)[i]->GetComponent<Collider2D>()->GetOnEnter() ||
					//			(*_invenItems)[i]->GetComponent<Collider2D>()->GetOnStay())
					//		{
					//			//(*_invenItems)[i]->SetMouseFollow(true);
					//			//item->SetMouseFollow(false);
					//			//SET_POS_VEC((*_invenItems)[i], GET_POS(item));
					//			//SET_POS_VEC((*_invenItems)[i], invenPosV3);
					//			break;
					//		}
					//	}
					//}
					MoveOtherStash(item, type);
					return true;
				}
			}
		}
		return false;
	}
	void StashManager::MoveOtherStash(InvenItem* item, eStashType stashTypeMove)
	{
		eStashType stashType = item->GetStashType();

		if (stashType == eStashType::Inventory)
			std::erase(invenItems, item);

		if (stashType == eStashType::ExPocketInven)
			std::erase(exPocketItems, item);

	    if(stashType == eStashType::PocketInven)
			std::erase(pocketItems, item);

		if (stashType == eStashType::Shop)
			std::erase(shopItems, item);

		item->SetStashType(stashTypeMove);

		if (stashTypeMove == eStashType::Inventory)
			invenItems.push_back(item);
		
		if (stashTypeMove == eStashType::PocketInven)
			pocketItems.push_back(item);

        if(stashTypeMove == eStashType::ExPocketInven)
			exPocketItems.push_back(item);

		if (stashTypeMove == eStashType::Shop)
			shopItems.push_back(item);
	}

	void StashManager::inventoryUpdate()
	{
		if (eInventoryState == GameObject::NoRenderNoUpdate) return;

		if (Input::GetKeyDown(eKeyCode::LBUTTON))
		{
			for (InvenItem* ii : invenItems)
			{
				if (ii->GetHover() && !ii->GetMouseFollow())
					ii->SetClickFunction();
			}
		}
		for (InvenItem* ii : invenItems)
			ii->SetState(eInventoryState);
	}

	void StashManager::shopInventoryUpdate()
	{
		if (eInventoryState == GameObject::NoRenderNoUpdate) return;
		if (eShopInventoryState == GameObject::NoRenderNoUpdate) return;
	}

	void StashManager::pocketInventoryUpdate()
	{
		for(InvenItem* pocketItem : pocketItems)
		{
			if (pocketItem->GetStashType() == eStashType::ExPocketInven)
				pocketItem->SetState(eExPocketState);
		}

		usePocketPosion();
	}

	InvenItem* StashManager::getPocketPosItem(int index)
	{
		Vector2 pocketInvenPos = pockets[index]->GetPos();
		Vector2 pocketInvenSize = pockets[index]->GetSize();

		for(InvenItem* item : pocketItems)
		{
			if (Vector2::PointIntersectRect(pocketInvenPos, pocketInvenSize, GET_VEC2_F_VEC3_D(GET_POS(item))))
			{
				return item;
			}
		}
		return nullptr;
	}

	InvenItem* StashManager::getExPocketPosItem(int index)
	{
		Vector2 pocketInvenPos = exPockets[index]->GetPos();
		Vector2 pocketInvenSize = exPockets[index]->GetSize();

		for (InvenItem* item : exPocketItems)
		{
			if (Vector2::PointIntersectRect(pocketInvenPos, pocketInvenSize, GET_VEC2_F_VEC3_D(GET_POS(item))))
			{
				return item;
			}
		}
		return nullptr;
	}

	void StashManager::usePocketPosion()
	{
		int keyIndex = -1;
		if (Input::GetKeyDownOne(eKeyCode::_1))
		{
			keyIndex = (int)eKeyCode::_1;
		}
		if (Input::GetKeyDownOne(eKeyCode::_2))
		{
			keyIndex = (int)eKeyCode::_2;
		}
		if (Input::GetKeyDownOne(eKeyCode::_3))
		{
			keyIndex = (int)eKeyCode::_3;
		}
		if (Input::GetKeyDownOne(eKeyCode::_4))
		{
			keyIndex = (int)eKeyCode::_4;
		}
		if (keyIndex != -1)
		{
			InvenItem* item = getPocketPosItem(keyIndex);
			if(item) EraseItem(item);
		}
		reArrangePocket();
	}
	void StashManager::reArrangePocket()
	{
		for(int i = 0 ; i < pockets.size(); ++i)
		{
			InvenItem* item = getPocketPosItem(i);
			Vector2 pocketPos = pockets[i]->GetPos();
			if(nullptr == item)
			{
				InvenItem* item1= getExPocketPosItem(i);
				if (nullptr != item1)
				{
				    MoveOtherStash(item1, eStashType::PocketInven);
					SET_POS_XYZ(item1, pocketPos.x, pocketPos.y, -1.f);
				}
			}
		}
		reArrangeExPocket();
	}

	void StashManager::reArrangeExPocket()
	{
		for (int i = 0; i < 4; ++i)
		{
			InvenItem* item = getExPocketPosItem(i);
			if(nullptr == item)
			{
				item = getExPocketPosItem(i + 4);
				if(nullptr != item)
				{
					Vector2 pocketInvenPos = exPockets[i]->GetPos();
					SET_POS_XYZ(item, pocketInvenPos.x, pocketInvenPos.y, -1.f);
				}
			}
		}
	}

	void StashManager::AddItem(InvenItem* item, eStashType stashType)
	{
		item->SetStashType(stashType);

		if (stashType == eStashType::Inventory)
		{
			invenItems.push_back(item);
		}
		if (stashType == eStashType::PocketInven)
		{
			pocketItems.push_back(item);
		}
		if (stashType == eStashType::Shop)
		{
			shopItems.push_back(item);
		}
	}

	void StashManager::EraseItem(InvenItem* item)
	{
		eStashType stashType = item->GetStashType();

		if (stashType == eStashType::Inventory)
		{
			std::erase(invenItems, item);
		}
		if (stashType == eStashType::PocketInven)
		{
			std::erase(pocketItems, item);
		}
		if (stashType == eStashType::Shop)
		{
			std::erase(shopItems, item);
		}

		item->SetState(GameObject::Delete);
	}

	bool StashManager::CheckItemSizeIntersectOutline(Vector2 comparePos, InvenItem* item, eStashType type)
	{
		MAKE_VEC2_F_VEC3(thisPosV2, comparePos);
		MAKE_VEC2_F_VEC3(thisScaleV2, GET_SCALE(item));

		EmptyRect* inC = nullptr;

		if (type == eStashType::Inventory) inC = invensCollider;
		if (type == eStashType::Shop) inC = shopInvensCollider;

		Vector2 outLinePos = inC->GetPos();
		Vector2 outLineScale = inC->GetSize();

		eItem mItem = item->GetEItem();

		if (itemInvenDisplayScale[(UINT)mItem][0] > 1.f
			|| itemInvenDisplayScale[(UINT)mItem][1] > 1.f)
		{
			if (Vector2::RectIndexesIntersectRectIndexes(outLinePos, outLineScale, thisPosV2, thisScaleV2))
			{
				return true;
			}
		}
		return false;
	}
	bool StashManager::CheckItemCenterPosIntersectItem(Vector2 centerPosFromInvenLeftTop, InvenItem* item, eStashType type)
	{
		std::vector<InvenItem*>* items = nullptr;
		if (type == eStashType::Inventory) items = &invenItems;
		if (type == eStashType::Shop) items = &shopItems;
		MAKE_VEC2_F_VEC3(thisScaleV2, GET_SCALE(item));
		//MAKE_VEC2_F_VEC3(thisPosV2, GET_POS(item));
		eItem mItem = item->GetEItem();
		if (itemInvenDisplayScale[(UINT)mItem][0] > 1.f
			|| itemInvenDisplayScale[(UINT)mItem][1] > 1.f)
		{
			for (int i = 0; i < items->size(); ++i)
			{
				InvenItem* item = (*items)[i];
				MAKE_VEC2_F_VEC3(itemPosV2, GET_POS(item));
				MAKE_VEC2_F_VEC3(itemScaleV2, GET_SCALE(item));
				if (Vector2::RectIntersectRect(itemPosV2, itemScaleV2, centerPosFromInvenLeftTop, thisScaleV2))
					return true;
				//InvenItem* item = (*items)[i];
				//if(GET_COMP(item, Collider2D)->GetOnStay()
				//	|| GET_COMP(item, Collider2D)->GetOnEnter())
				//{
				//	return true;
			}
		}
		return false;
	}

	bool StashManager::CheckInvensFill(int leftTopInvenIndex, InvenItem* item, eStashType type)
	{
		std::vector<EmptyRect*>* _invens = nullptr;

		if (type == eStashType::Inventory) _invens = &invens;
		if (type == eStashType::Shop) _invens = &shopInvens;

		eItem mItem = item->GetEItem();

		int dx = (leftTopInvenIndex % 10)+ (int)itemInvenDisplayScale[(UINT)mItem][0];
		int dy = (leftTopInvenIndex / 10) + (int)itemInvenDisplayScale[(UINT)mItem][1];

		for(int y = leftTopInvenIndex; y < dy; ++y)
		{
			for (int x = leftTopInvenIndex; x < dx; ++x)
			{
				if ((y * 10 + x) >= _invens->size()) return false;
				if ((*_invens)[y * 10 + x]->GetFill()) return false;
			}
		}
		return true;
	}
	void StashManager::ChangeFillIntersectArea(Vector2 centerPosFromInvenLeftTop, bool _bV, InvenItem* item, eStashType type)
	{
		std::vector<EmptyRect*>* items = nullptr;

		if (type == eStashType::Inventory) items = &invens;
		if (type == eStashType::Shop) items = &shopInvens;

		if (nullptr == items) return;

		for (int i = 0; i < items->size(); ++i)
		{
			Vector2 invenPos = (*items)[i]->GetPos();
			Vector2 invenSize = (*items)[i]->GetSize();

			MAKE_VEC2_F_VEC3(thisScale, GET_SCALE(item));

			if (Vector2::RectIntersectRect(invenPos, invenSize, centerPosFromInvenLeftTop, thisScale))
			{
				(*items)[i]->SetFill(_bV);
			}
		}
	}
	//bool StashManager::CheckFillSetction(Vector2 centerPosFromInvenLeftTop, InvenItem* item, eStashType type)
	//{
	//	std::vector<EmptyRect*>* items = nullptr;

	//	if (type == eStashType::Inventory) items = &invens;
	//	if (type == eStashType::Shop) items = &shopInvens;

	//	if (nullptr == items) return false;

	//	for (int i = 0; i < items->size(); ++i)
	//	{
	//		Vector2 invenPos = (*items)[i]->GetPos();
	//		Vector2 invenSize = (*items)[i]->GetSize();

	//		MAKE_VEC2_F_VEC3(thisScale, GET_SCALE(item));

	//		if (Vector2::RectIntersectRect(invenPos, invenSize, centerPosFromInvenLeftTop, thisScale))
	//		{
	//			//(*items)[i]->SetFill(_bV);
	//		}
	//	}
	//}
	bool StashManager::CheckLimitIntersectItems(int limit, eStashType type)
	{
		std::vector<InvenItem*>* items = nullptr;

		if (type == eStashType::Inventory) items = &invenItems;
		if (type == eStashType::Shop) items = &shopItems;

		if (nullptr == items) return false;

		int intersectItemCnt = 0;
		for (InvenItem* item : (*items))
		{
			if (item->GetComponent<Collider2D>()->GetOnStay()
				|| item->GetComponent<Collider2D>()->GetOnEnter())
			{
				intersectItemCnt++;
			}
			if (intersectItemCnt > limit)
			{
				return true;
			}
		}
		return false;
	}
}
