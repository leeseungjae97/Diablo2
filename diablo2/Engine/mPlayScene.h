#pragma once
#include "../engine_source/mScene.h"
namespace m
{
    class Floor;
    class CharacterStatus;
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
        void MakeStage4Wall();
        void MakeStageBWall();
        void MakeStage3Wall();
        void MakeStage2Wall();
        void MakeStage1Wall();
        void MakeStage0Wall();
        void MakeStageEndWall();
        void Stage0();
        void Stage1();
        void Stage2();
        void Stage3();
        void StageB();
        void Stage4();
        void StageEnd();
        void NPCRender();
        void NPCNoRender();
    private:
        Inventory* inventory;
        SkillStatus* skillUp;
        CharacterStatus* status;

        BottomUI* uiBottomBar;
        Shop* shop;

        GameObject* curMap;
        GameObject* dayLight;
        Monster* mBossMonster;
        Portal* mPortal;

        Floor* floor;

        NPC* mNpc1;
        NPC* mNpc2;

        UI* mEnterNameUI;

        float fAcc;
        bool bPlaySceneFireUpdate;

        bool bStageInit;
        bool bStageStart;
    };
}


