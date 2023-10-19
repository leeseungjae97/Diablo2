#include "mCheatManager.h"

#include "../Engine/mPlayerManager.h"
#include "../Engine/mPlayerStatus.h"

#include "mInput.h"
namespace m
{
    void CheatManager::Update()
    {
        if(Input::GetKeyDown(eKeyCode::L))
        {
            PlayerManager::money = 10000;
        }
        if (Input::GetKeyDown(eKeyCode::K))
        {
            PlayerStatus::statusPoint = 50;
        }
        if (Input::GetKeyDown(eKeyCode::J))
        {
            PlayerManager::skillPoint = 50;
        }
        if (Input::GetKeyDown(eKeyCode::H))
        {
            PlayerStatus::damage = 1000;
        }
        if (Input::GetKeyDown(eKeyCode::G))
        {
            PlayerStatus::damage = 10;
        }
    }
}
