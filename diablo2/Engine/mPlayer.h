#pragma once
#include "..\engine_source\mGameObject.h"
#include "..\engine_source\mCamera.h"
#include "..\engine_source\mTileManager.h"

#include "mPlayerInfo.h"
#include "mMoveAbleObject.h"
#include "mUVUI.h"
namespace m
{
    class Tile;
    class Player :
        public MoveAbleObject
    {
    public:
        Player(Vector3 iniPos);
        virtual ~Player();

        virtual void Initialize();
        virtual void Update();
        virtual void LateUpdate();
        virtual void Render();

        void Hit(int damage) { 
            if (PlayerInfo::hp - damage < 0) PlayerInfo::hp = 0;
            else PlayerInfo::hp -= damage; 

            PlayerInfo::CalHpPercent();
            mHp->SetUVCoord(PlayerInfo::hpPercent);
            
            SetHit(true);
        }

        UVUI* GetHpUI() { return mHp; }
        UVUI* GetMpUI() { return mMp; }

        void SetHpUI(UVUI* hp) { mHp = hp; }
        void SetMpUI(UVUI* mp) { mMp = mp; }

    private:
        UVUI* mHp;
        UVUI* mMp;
    };
}

