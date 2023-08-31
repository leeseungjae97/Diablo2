#pragma once
#include "../engine_source/mUI.h"

#include "mItem.h"
namespace m
{
    interface Stash
    {
    public:
        virtual void AddItem(Item* item) = 0;
        virtual void EraseItem(Item* item) = 0;

    private:
        std::vector<Item*> mItems;
    };
}