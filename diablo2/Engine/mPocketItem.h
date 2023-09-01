#pragma once
#include "mItem.h"
namespace m
{
    class PocketItem :
        public Item
    {
    public:
        PocketItem(eItem item);
        virtual ~PocketItem();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;

    private:
    };
}

