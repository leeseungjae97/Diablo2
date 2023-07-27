#pragma once
#include "mItem.h"

#include "..\engine_source\mSceneManager.h"
#include "..\engine_source\mLayer.h"

namespace m
{
    class BottomUI;
    class Inventory;
    class InvenItem :
        public Item
    {
    public:
        InvenItem(eItem item, Inventory* inventory);
        virtual ~InvenItem();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;
        bool GetMouseFollow() { return bSetMouseFollow; }
        void SetMouseFollow(bool _b) { bSetMouseFollow = _b; }
        void SetClickFunction() { SceneManager::GetActiveScene()->GetLayer(eLayerType::Item).ChangeOrderGameObject(this); }

        void InvenItemInit();
        void ChangeBoolIntersectArea(Vector3 areaPos, bool _bV);
        bool CheckLimitIntersectItems(int limit);
        void DeployItem();
        bool CheckItemSizeIntersectInventory(Vector3 comparePos);
        bool CheckItemSizeIntersectItem(Vector3 comparePos);
    private:
        bool bSetMouseFollow;
        Vector3 prevPosition;

        Vector2 inventoryOutLinePos;
        Vector2 inventoryOutLineScale;
        Inventory* mInventory;
        BottomUI* mBottomUI;
        eItem mItem;
    };
}

