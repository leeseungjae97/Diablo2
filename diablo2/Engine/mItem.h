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

        Item(eItemType type);
        virtual ~Item();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;

        void SetItemType(eItemType type) { mType = type; }
        eItemType GetItemType() { return mType; }

        void SetInvenXSpace(int spaceX) { iInvenXSpace = spaceX; }
        void SetInvenYSpace(int spaceY) { iInvenYSpace = spaceY; }

        int GetInvenXSpace() { return iInvenXSpace; }
        int GetInvenYSpace() { return iInvenYSpace; }

        void SetStashType(StashManager::eStashType type) { mStashType = type; }
        StashManager::eStashType GetStashType() { return mStashType; }

        bool GetMouseFollow() { return bSetMouseFollow; }
        void SetMouseFollow(bool _b) { bSetMouseFollow = _b; }

        eItem GetEItem() { return mItem; }
        void SetEItem(eItem item) { mItem = item; }

        void SetStash(GameObject* stash) { mStash = stash; }
        GameObject* GetStash() { return mStash; }

    private:
        StashManager::eStashType mStashType;
        GameObject* mStash;
        bool bSetMouseFollow;

        eItemType mType;
        eItem mItem;

        int iInvenXSpace;
        int iInvenYSpace;

        float fFieldXSpace;
        float fFieldYSpace;

        std::shared_ptr<Material> mInvenMaterial;
        std::shared_ptr<Material> mFieldMaterial;
    };
}


