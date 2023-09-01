#pragma once
#include "mGameObject.h"
#include "_Engine.h"

namespace m
{
	class InvenItem;
	class PocketItem;
	class ShopItem;
	class EmptyRect;
	class Camera;
	class Item;
	class StashManager
	{
	public:
		enum class eStashType
		{
			Field,
			Inventory,
			Equiment,
			PocketInven,
			ExPocketInven,
			Shop,
			End
		};
		struct Stash
		{
			Vector2 pos;
			Vector2 size;
			eStashType type;
		};

		static eStashType GetHoverStashType();
		static void InitStash();
		static void InitStashPos(Vector2 pos, Vector2 size, eStashType type);
		static void Release();
		static void Update();

		static void ItemHoverStashPos();

		static void MoveOtherStash(InvenItem* item, eStashType stashTypeMove, Vector3 stashPos);

		static bool AvailableDeployItem(Item* item);
		static void SetCamera(Camera* camera) { mCurCamera = camera; }

		static void AddItem(InvenItem* item, eStashType stashType);

		static void EraseItem(InvenItem* item);

		static std::vector<EmptyRect*>& GetInvens() { return invens; }
		static std::vector<EmptyRect*>& GetEquiments() { return equiments; }
		static std::vector<EmptyRect*>& GetShopInvens() { return shopInvens; }
		static std::vector<EmptyRect*>& GetPockets() { return pockets; }
		static std::vector<EmptyRect*>& GetExPockets() { return exPockets; }

		static EmptyRect* GetInvenWeapon1Left() { return invenWeapon1Left; }
		static EmptyRect* GetInvenWeapon1Right() { return invenWeapon1Right; }
		static EmptyRect* GetInvenRingLeft() { return invenRingLeft; }
		static EmptyRect* GetInvenRingRight() { return invenRingRight; }
		static EmptyRect* GetInvenAmulet() { return invenAmulet; }
		static EmptyRect* GetInvenBelt() { return invenBelt; }
		static EmptyRect* GetInvenHelmet() { return invenHelmet; }
		static EmptyRect* GetInvenShoes() { return invenShoes; }
		static EmptyRect* GetInvenGlove() { return invenGlove; }
		static EmptyRect* GetInvenArmor() { return invenArmor; }

		static EmptyRect* GetInvensCollider() { return invensCollider; }
		static EmptyRect* GetShopInvensCollider() { return shopInvensCollider; }
		static EmptyRect* GetPocketCollider() { return pocketCollider; }
		static EmptyRect* GetExPocketCollider() { return exPocketCollider; }

		static std::vector<InvenItem*>& GetInvenItems() { return invenItems; }
		static std::vector<InvenItem*>& GetPocketItems() { return pocketItems; }
		static std::vector<InvenItem*> GetShopItems() { return shopItems; }

		static void SetInventoryVisible(GameObject::eState state) { eInventoryState = state; }

		static void SetFollowItem(InvenItem* item) { mFollowItem = item; }
		static InvenItem* GetFollowItem() { return mFollowItem; }

	private:
		static void inventoryUpdate();
		static void shopInventoryUpdate();
		static void pocketInventoryUpdate();

		static Camera* mCurCamera;
		static std::vector<Stash> stashPositions;

		static EmptyRect* invensCollider;
		static EmptyRect* shopInvensCollider;
		static EmptyRect* pocketCollider;
		static EmptyRect* exPocketCollider;

		static std::vector<EmptyRect*> invens;
		static std::vector<EmptyRect*> equiments;
		static std::vector<EmptyRect*> shopInvens;
		static std::vector<EmptyRect*> pockets;
		static std::vector<EmptyRect*> exPockets;

		static EmptyRect* invenWeapon1Left;   // x 60 y 117
		static EmptyRect* invenWeapon1Right;  // x 60 y 117
		static EmptyRect* invenRingLeft;      // x 30 y 31
		static EmptyRect* invenRingRight;     // x 30 y 31
		static EmptyRect* invenAmulet;        // x 30 y 31
		static EmptyRect* invenBelt;          // x 60 y 31
		static EmptyRect* invenHelmet;        // x 60 y 60
		static EmptyRect* invenShoes;         // x 60 y 61
		static EmptyRect* invenGlove;         // x 60 y 61
		static EmptyRect* invenArmor;         // x 62 y 89

		static std::vector<InvenItem*> invenItems;
		static std::vector<InvenItem*> pocketItems;
		static std::vector<InvenItem*> shopItems;

		static GameObject::eState eInventoryState;
		static GameObject::eState eShopInventoryState;

		static InvenItem* mFollowItem;
	};
}


