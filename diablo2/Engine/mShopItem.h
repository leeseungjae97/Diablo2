#pragma once
#include "mItem.h"
namespace m
{
    class ShopItem :
        public Item
    {
    public:
        ShopItem(eItem type);
        virtual ~ShopItem();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;
    private:
    };
}

