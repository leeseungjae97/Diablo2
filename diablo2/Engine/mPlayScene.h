#pragma once
#include "../engine_source/mScene.h"
namespace m
{
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
    private:
        Inventory* inventory;
        SkillStatus* skillUp;
        BottomUI* uiBottomBar;
    };
}


