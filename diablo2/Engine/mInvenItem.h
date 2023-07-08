#pragma once
#include "mItem.h"

#include "..\engine_source\mSceneManager.h"
#include "..\engine_source\mLayer.h"

namespace m
{
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
        bool MouseFollow() { return bSetMouseFollow; }
        void OrderClickItem() { SceneManager::GetActiveScene()->GetLayer(eLayerType::Item).ChangeOrderGameObject(this); }
    private:
        bool bSetMouseFollow;
        Vector3 prevPosition;
        Inventory* mInventory;
        eItem mItem;
    };
}

