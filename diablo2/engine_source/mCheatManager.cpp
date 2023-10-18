#include "mCheatManager.h"

#include "../Engine/mPlayerManager.h"
#include "../Engine/mPlayerStatus.h"

#include "mInput.h"
namespace m
{
    void CheatManager::Update()
    {
        if(Input::GetKeyDown(eKeyCode::M))
        {
            PlayerManager::money = 10000;
        }
        if (Input::GetKeyDown(eKeyCode::N))
        {
            PlayerStatus::statusPoint = 50;
        }
        if (Input::GetKeyDown(eKeyCode::B))
        {
            PlayerManager::skillPoint = 50;
        }
        if (Input::GetKeyDown(eKeyCode::V))
        {
            PlayerStatus::damage = 1000;
        }
    }
}
