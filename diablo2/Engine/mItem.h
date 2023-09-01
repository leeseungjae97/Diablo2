#pragma once
#include "mStashManager.h"
#include "../engine_source/mGameObject.h"
#include "../engine_source/mMaterial.h"
#include "../engine_source/ItemLookUpTables.h"
#include "../engine_source/mStashManager.h"

namespace m
{
    class Item :
        public GameObject
    {
    public:

        Item(eItem type);
        virtual ~Item();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;

        void SetItemType(eItemType type) { mType = type; }
        eItemType GetItemType() { return mType; }

        void SetStashType(StashManager::eStashType type) { mStashType = type; }
        StashManager::eStashType GetStashType() { return mStashType; }

        bool GetMouseFollow() { return bSetMouseFollow; }
        void SetMouseFollow(bool _b) { bSetMouseFollow = _b; }

        eItem GetEItem() { return mItem; }
        void SetEItem(eItem item) { mItem = item; }

    private:
        StashManager::eStashType mStashType;
        
        bool bSetMouseFollow;

        eItemType mType;
        eItem mItem;

        float fFieldXSpace;
        float fFieldYSpace;

        std::shared_ptr<Material> mInvenMaterial;
        std::shared_ptr<Material> mFieldMaterial;
    };
}


