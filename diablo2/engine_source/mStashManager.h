#pragma once
#include "_Engine.h"

#include "mGameObject.h"

namespace m
{
	class InvenItem;
	class FieldItem;
	class EmptyRect;
	class Camera;
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

		static void Initialize();
		static void InitStash();		

		static void InitItems(eStashType type);
		static void InitTetris(eStashType type);
		static void InitException(eStashType type);

		static void Release();
		static void Update();

		static bool ItemDeploy();
		static bool DeployTetris(eStashType type);
		static bool DeployException(eStashType type, std::vector<int> exceptType, std::vector<int> acceptType);
		static void ChangeFieldItemToInvenItem(FieldItem* item);
		static bool ChangeInvenItemToFieldItem(InvenItem* item);
		static void MoveOtherStash(InvenItem* item, eStashType stashTypeMove);

		static void SetCamera(Camera* camera) { mCurCamera = camera; }

		static void AddItem(InvenItem* item, eStashType stashType);
		static void EraseItem(InvenItem* item, bool bgracePeriod = false);

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
		static void SetExPocketVisible(GameObject::eState state) { eExPocketState = state; }

		static bool CheckItemCenterPosIntersectItem(Vector2 centerPosFromInvenLeftTop, InvenItem* item, eStashType type);
		static bool CheckInvensFill(int leftTopInvenIndex, InvenItem* item, eStashType type);
		static void ChangeFillIntersectArea(Vector2 areaPos, bool _bV, InvenItem* item, eStashType type);
		static bool CheckItemSizeIntersectOutline(Vector2 comparePos, InvenItem* item, eStashType type);
		static bool CheckLimitIntersectItems(int limit, eStashType type);

		static bool AddItemTetris(InvenItem* item, eStashType type);
	private:
		static InvenItem* getPocketPosItem(int index);
		static InvenItem* getExPocketPosItem(int index);
		static void reArrangePocket();
		static void reArrangeExPocket();
		static void inventoryUpdate();
		static void shopInventoryUpdate();
		static void pocketInventoryUpdate();
		static void usePocketPosion();

		static Camera* mCurCamera;

		static EmptyRect* invensCollider;
		static EmptyRect* shopInvensCollider;
		static EmptyRect* pocketCollider;
		static EmptyRect* exPocketCollider;
		static EmptyRect* inventoryCollider;

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
		static std::vector<InvenItem*> exPocketItems;
		static std::vector<InvenItem*> shopItems;
		static std::vector<InvenItem*> equimentItems;

		static GameObject::eState eInventoryState;
		static GameObject::eState eShopInventoryState;
		static GameObject::eState eExPocketState;

		static GameObject* m;
	};
}


