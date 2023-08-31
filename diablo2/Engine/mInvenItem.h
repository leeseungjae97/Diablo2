#pragma once
#include "mItem.h"

#include "../engine_source/mSceneManager.h"
#include "../engine_source/mLayer.h"

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

        void SetClickFunction() { SceneManager::GetActiveScene()->GetLayer(eLayerType::Item)->FrontGameObject(this); }

        void InvenItemInit();
        void ChangeFillIntersectArea(Vector2 areaPos, bool _bV);
        bool CheckLimitIntersectItems(int limit);
        void DeployItem();
        bool CheckItemSizeIntersectInventory(Vector2 comparePos);
        bool CheckItemSizeIntersectItem(Vector2 comparePos);
    private:

        Vector3 prevPosition;

        Vector2 inventoryOutLinePos;
        Vector2 inventoryOutLineScale;

        Inventory* mInventory;
        BottomUI* mBottomUI;
        

    };
}

