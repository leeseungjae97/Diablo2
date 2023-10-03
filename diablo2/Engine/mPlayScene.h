#pragma once
#include "../engine_source/mScene.h"
namespace m
{
    class UI;
    class NPC;
    class Portal;
    class Shop;
    class Inventory;
    class Pocket;
    class SkillStatus;
    class Tile;
    class BottomUI;
    class PlayScene :
        public Scene
    {
    public:
        PlayScene();
        virtual ~PlayScene();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;

        void SystemUI();
        void MakeWall();
        void Stage1();
        void Stage2();
        void Stage3();
        void Stage4();
        void NPCRender();
        void NPCNoRender();
    private:
        Inventory* inventory;
        SkillStatus* skillUp;
        BottomUI* uiBottomBar;
        Shop* shop;

        GameObject* curMap;
        Monster* mBossMonster;
        Portal* mPortal;

        NPC* mNpc1;
        NPC* mNpc2;

        UI* mEnterNameUI;
        float fAcc;

        bool bStageInit;
        bool bStageStart;
    };
}


