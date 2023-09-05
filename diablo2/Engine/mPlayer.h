#pragma once
#include "../engine_source/mGameObject.h"
#include "../engine_source/mCamera.h"
#include "../engine_source/mTileManager.h"

#include "mPlayerManager.h"
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

        void Hit(int damage);

        void UseMana(int mana);
        void RestoreHp(int hp);
        void RestoreMp(int mp);
        UVUI* GetHpUI() { return mHp; }
        UVUI* GetMpUI() { return mMp; }

        void SetHpUI(UVUI* hp) { mHp = hp; }
        void SetMpUI(UVUI* mp) { mMp = mp; }

        //int GetFMID() { return mFollowingMonsterId; }
        //void SetFMID(int id) { mFollowingMonsterId = id; }

        //bool GetAttack() { return bAttack; }
        //void SetAttack(bool attack) { bAttack = attack; }
    private:
        UVUI* mHp;
        UVUI* mMp;

        //int mFollowingMonsterId;
        //bool bAttack;
    };
}

