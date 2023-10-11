#include "mFieldItemManager.h"

#include "mGameObject.h"


#include "../Engine/mFieldItem.h"

namespace m
{
    std::vector<FieldItem*> FieldItemManager::items;
    void FieldItemManager::Add(FieldItem* item)
    {
        items.push_back(item);
    }

    void FieldItemManager::Erase(FieldItem* item)
    {
        if (items.empty()) return;
        if (nullptr == item) return;

        std::erase(items, item);

        item->SetState(GameObject::eState::Delete);
    }

    void FieldItemManager::EraseAll()
    {
        if (items.empty()) return;

        for(FieldItem* item : items)
        {
            item->SetState(GameObject::eState::Delete);
        }

        items.clear();
    }
}
