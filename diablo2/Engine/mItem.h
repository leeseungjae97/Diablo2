#pragma once
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

    private:
        StashManager::eStashType mStashType;

        eItemType mType;
        int iInvenXSpace;
        int iInvenYSpace;

        float fFieldXSpace;
        float fFieldYSpace;

        std::shared_ptr<Material> mInvenMaterial;
        std::shared_ptr<Material> mFieldMaterial;
    };
}


