#pragma once
#include "..\engine_source\mScene.h"
namespace m
{
    class Inventory;
    class SkillUp;
    class Tile;
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
        std::vector<Tile*> tiles;
        Inventory* inven;
        SkillUp* skillUp;
    };
}


