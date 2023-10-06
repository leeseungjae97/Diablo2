#include "mWallObjectManager.h"
namespace m
{
    std::vector<GameObject*> WallObjectManager::objs;
    void WallObjectManager::EraseAll()
    {
        if (objs.empty()) return;

        for(GameObject* obj : objs)
        {
            if (nullptr == obj) continue;
            if (obj->GetState() == GameObject::eState::Delete) continue;

            obj->SetState(GameObject::eState::Delete);
        }
        objs.clear();
    }

    void WallObjectManager::Add(GameObject* obj)
    {
        objs.push_back(obj);
    }
}
