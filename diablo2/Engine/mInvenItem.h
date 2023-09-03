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
        InvenItem(eItem item);
        virtual ~InvenItem();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;

        void SetClickFunction() { SceneManager::GetActiveScene()->GetLayer(eLayerType::Item)->FrontGameObject(this); }

        Vector3 GetPrevPosition() { return prevPosition; }
        void SetPrevPosition(Vector3 prevPos) { prevPosition = prevPos; }

        void ItemFunction() { bDoItemFunction = true; }
        void ItemFunctionStop() { bDoItemFunction = false; }

        bool GetDoItemFunction() { return bDoItemFunction; }
    private:
        Vector3 prevPosition;
        bool bDoItemFunction;
    };
}

