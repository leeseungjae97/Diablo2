#pragma once
#include "..\engine_source\mGameObject.h"
#include "..\engine_source\mCamera.h"
#include "..\engine_source\mTileManager.h"

#include "mPlayerInfo.h"
#include "mUVUI.h"
namespace m
{
    class Tile;
    class Player :
        public GameObject
    {
    public:
        Player(Vector3 iniPos);
        virtual ~Player();

        virtual void Initialize();
        virtual void Update();
        virtual void LateUpdate();
        virtual void Render();

        Vector3 GetPrevPosition() { return prevPosition; }
        Vector3 GetDestPosition() { return destPosition; }
        Vector3 GetDirection() { return vDirection; }

        bool Stop() { return fRemainDistance < fStartDistance ? false : true; }
        void Hit(int damage) { 
            if (PlayerInfo::hp - damage < 0) PlayerInfo::hp = 0;
            else PlayerInfo::hp -= damage; 

            PlayerInfo::CalHpPercent();
            mHp->SetUVCoord(PlayerInfo::hpPercent);
            
            bGetHit = true;
        }
        bool GetHit() { return bGetHit; }
        void SetHit(bool hit) { bGetHit = hit; }

        void SetTile(TILES vec) { tiles = vec; }

        UVUI* GetHpUI() { return mHp; }
        UVUI* GetMpUI() { return mMp; }

        void SetHpUI(UVUI* hp) { mHp = hp; }
        void SetMpUI(UVUI* mp) { mMp = mp; }

        Collider2D* GetRangeCollider() { return rangeCollider; }

    private:
        Collider2D* rangeCollider;

        Vector3 prevPosition;
        Vector3 destPosition;
        Vector3 vDirection;
        Vector3 vS;

        float fRemainDistance;
        float fStartDistance;
        float fSpeed;

        bool bGetHit;

        TILES tiles;

        UVUI* mHp;
        UVUI* mMp;
    };
}

