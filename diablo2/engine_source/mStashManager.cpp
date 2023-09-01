#include "mStashManager.h"

//#include "mMouseManager.h"

#include "../Engine/mItem.h"
#include "../Engine/mEmptyRect.h"
#include "../Engine/mInvenItem.h"
#include "../Engine/mPocketItem.h"
#include "../Engine/mShopItem.h"

namespace m
{
	std::vector<StashManager::Stash> StashManager::stashPositions;

	std::vector<EmptyRect*> StashManager::invens = {};
	std::vector<EmptyRect*> StashManager::equiments = {};
	std::vector<EmptyRect*> StashManager::shopInvens = {};
	std::vector<EmptyRect*> StashManager::pockets = {};
	std::vector<EmptyRect*> StashManager::exPockets = {};

	std::vector<InvenItem*> StashManager::invenItems = {};
	std::vector<InvenItem*> StashManager::pocketItems = {};
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

	StashManager::eStashType StashManager::GetHoverStashType()
	{
		Vector3 mousePosV3 = MouseManager::UnprojectionMousePos(-1.f, mCurCamera);
		Vector2 mousePosV2 = Vector2(mousePosV3.x, mousePosV3.y);

		for (Stash stash : stashPositions)
		{
			Vector2 sPos = stash.pos;
			Vector2 sSize = stash.size;
			if (Vector2::PointIntersectRect(sPos, sSize, mousePosV2))
			{
				return stash.type;
			}
		}
		return eStashType::End;
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

		for (int i = 0; i < pockets.size(); ++i)
			InitStashPos(pockets[i]->GetSize(), pockets[i]->GetSize(), eStashType::PocketInven);

		for (int i = 0; i < exPockets.size(); ++i)
			InitStashPos(exPockets[i]->GetSize(), exPockets[i]->GetSize(), eStashType::ExPocketInven);

		for (int i = 0; i < invens.size(); ++i)
			InitStashPos(invens[i]->GetSize(), invens[i]->GetSize(), eStashType::Inventory);

		for (int i = 0; i < equiments.size(); ++i)
			InitStashPos(equiments[i]->GetSize(), equiments[i]->GetSize(), eStashType::Equiment);

		for (int i = 0; i < shopInvens.size(); ++i)
			InitStashPos(shopInvens[i]->GetSize(), shopInvens[i]->GetSize(), eStashType::Shop);
#pragma endregion
#pragma region Collider
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
#pragma region initStashPos
		for (EmptyRect* er : invens)
			InitStashPos(er->GetPos(), er->GetSize(), eStashType::Inventory);

		for (EmptyRect* er : equiments)
			InitStashPos(er->GetPos(), er->GetSize(), eStashType::Equiment);

		for (EmptyRect* er : exPockets)
			InitStashPos(er->GetPos(), er->GetSize(), eStashType::ExPocketInven);

		for (EmptyRect* er : pockets)
			InitStashPos(er->GetPos(), er->GetSize(), eStashType::PocketInven);

		for (EmptyRect* er : shopInvens)
			InitStashPos(er->GetPos(), er->GetSize(), eStashType::Shop);
#pragma endregion
	}

    void StashManager::InitStashPos(Vector2 pos, Vector2 size, eStashType type)
    {
		stashPositions.push_back({ pos, size, type });
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
		ItemHoverStashPos();
    }

    void StashManager::ItemHoverStashPos()
    {
		InvenItem* item = mFollowItem;

		if (nullptr == item) return;

		for(Stash stash : stashPositions)
		{
			Vector2 stashPos = stash.pos;
			Vector2 stashSize = stash.size;
			eStashType stashType = stash.type;

			if (item->GetStashType() == stash.type) continue;

			Vector3 itemPos = GET_POS(item);
			Vector3 itemScale = GET_SCALE(item);
			MAKE_VEC2_F_VEC3(itemPosV2, itemPos);
			MAKE_VEC2_F_VEC3(itemScaleV2, itemScale);
			
			if(Vector2::RectIntersectRect(stashPos, stashSize, itemPosV2, itemScaleV2))
			{
				if(Input::GetKeyDownOne(eKeyCode::LBUTTON))
				{
				    MoveOtherStash(item, stashType, Vector3(stashPos.x, stashPos.y, itemPos.z));
				}
			}
		}
		
    }

    void StashManager::MoveOtherStash(InvenItem* item, eStashType stashTypeMove, Vector3 stashPos)
    {
		eStashType stashType = item->GetStashType();
		Scene* curScene = SceneManager::GetActiveScene();
		if (stashType == eStashType::Inventory)
			std::erase(invenItems, item);

		if (stashType == eStashType::ExPocketInven)
			std::erase(pocketItems, item);

		if (stashType == eStashType::PocketInven)
			std::erase(pocketItems, item);

		if (stashType == eStashType::Shop)
			std::erase(shopItems, item);


		if (stashTypeMove == eStashType::Inventory)
		{
			//InvenItem* newItem = new InvenItem(item->GetEItem());

			//newItem->SetCamera(mCurCamera);
			//newItem->SetState(eInventoryState);
			//curScene->AddGameObject(eLayerType::UI, newItem);

			SET_POS_VEC(item, stashPos);

			invenItems.push_back(item);
		}

		if (stashTypeMove == eStashType::ExPocketInven ||
			stashTypeMove == eStashType::PocketInven)
		{
			//PocketItem* pocItem = new PocketItem(item->GetEItem());

			//pocItem->SetCamera(mCurCamera);
			//pocItem->SetState(eInventoryState);

			SET_POS_VEC(item, stashPos);

			//curScene->AddGameObject(eLayerType::UI, pocItem);

			
			pocketItems.push_back(item);
		}

		if (stashTypeMove == eStashType::Shop)
		{
			//ShopItem* shopItem = new ShopItem(item->GetEItem());

			//shopItem->SetCamera(mCurCamera);
			//shopItem->SetState(eInventoryState);
			//curScene->AddGameObject(eLayerType::UI, shopItem);
			
			SET_POS_VEC(item, stashPos);

			
			shopItems.push_back(item);
		}
		
		//EraseItem(item);
		MouseManager::SetMouseFollow(nullptr);
		//item->SetState(GameObject::Delete);
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
	}

	void StashManager::AddItem(InvenItem* item, eStashType stashType)
	{
		if(stashType == eStashType::Inventory)
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
	}
	bool StashManager::AvailableDeployItem(Item* item)
	{
		eStashType prevStashType = item->GetStashType();

		eStashType type = GetHoverStashType();
		if (type == eStashType::End) return false;

		eItemType type2 = item->GetItemType();
		if (type2 == eItemType::END) return false;

		switch (type)
		{
		case eStashType::Field:
		{

		}
		break;
		case eStashType::Inventory:
		{
		}
		break;
		case eStashType::PocketInven:
		{
			if (type2 != eItemType::Posion) return false;
		}
		break;
		case eStashType::Shop:
		{

		}
		break;
		default:
		{

		}
		break;
		}

		return true;
	}
}
