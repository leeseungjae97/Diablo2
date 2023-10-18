#pragma once
#include "../engine_source/mGameObject.h"
#include "../engine_source/mCamera.h"
#include "../engine_source/mTileManager.h"

#include "mPlayerManager.h"
#include "mMoveAbleObject.h"
#include "mUVUI.h"
namespace m
{
    class ShadowObject;
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

        void Hit(int damage, bool attackStun = true);
        void UseMana(int mana);
        void RestoreHp(int hp);
        void RestoreMp(int mp);
        UVUI* GetHpUI() { return mHp; }
        UVUI* GetMpUI() { return mMp; }

        void SetHpUI(UVUI* hp) { mHp = hp; }
        void SetMpUI(UVUI* mp) { mMp = mp; }

        virtual void AttackedAddition() override;

    private:
        void playerMove();
        void updateColliderPos();
        //void timeWaitAttack();
        
    private:
        UVUI* mHp;
        UVUI* mMp;

        bool bPlayEndVideo;
    };
}

