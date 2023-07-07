#pragma once
#include "..\engine_source\mGameObject.h"
#include "..\engine_source\mMaterial.h"

namespace m
{
    class Item :
        public GameObject
    {
    public:
        enum class eItemType
        {
            None,
            Weapon,
            Ring,
            Amulet,
            Belt,
            Helmet,
            Shoes,
            Glove,
            Armor,
            Posion,
            Scroll,
            END,
        };

        Item(eItemType type);
        Item();
        virtual ~Item();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;

        void SetItemType(eItemType type) { mType = type; }
        eItemType GetItemType() { return mType; }

        //bool GetHover() { return bHover; }
        //void SetHover(bool hover) { bHover = hover; }

    private:
        //bool bHover;
        eItemType mType;
        int iSpaceInvenX;
        int iSpaceInvenY;

        std::shared_ptr<Material> mInvenMaterial;
        std::shared_ptr<Material> mFieldMaterial;
    };
}


