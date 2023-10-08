#include "mTileDrawManager.h"
namespace m
{
    std::vector<TileDrawSystem*> TileDrawManager::mtiledrawsystems;
    bool TileDrawManager::bDrawTile = true;
    void TileDrawManager::Update()
    {
        if (Input::GetKeyDown(eKeyCode::A))
        {
            bDrawTile = true; 
        }
        if (Input::GetKeyDown(eKeyCode::D))
        {
            bDrawTile = false;
        }
    }
    void TileDrawManager::Add(TileDrawSystem* tds)
    {
        mtiledrawsystems.push_back(tds);
    }

    void TileDrawManager::EraseAll()
    {
        if (!mtiledrawsystems.empty())
            mtiledrawsystems.clear();
    }

    void TileDrawManager::Erase(TileDrawSystem* tds)
    {
        if(!mtiledrawsystems.empty())
            std::erase(mtiledrawsystems, tds);
    }
}
