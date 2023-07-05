#pragma once
#include "mItem.h"
namespace m
{
    class InvenItem :
        public Item
    {
    public:
        InvenItem(eItemType type);
        virtual ~InvenItem();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;
    private:
        bool bSetMouseFollow;
    };
}

