#pragma once
#include "..\engine_source\mGameObject.h"
namespace m
{
    class Tile :
        public GameObject
    {
    public:
        Tile(Vector2 coord);
        virtual ~Tile();

        virtual void Initialize();
        virtual void Update();
        virtual void LateUpdate();
        virtual void Render();
    private:
        Vector2 mCoord;
    };
}

