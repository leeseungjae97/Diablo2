#pragma once
#include "mGameObject.h"
namespace m
{
    class Tile :
        public GameObject
    {
    public:
        Tile(Vector3 iniPos, Vector2 coord);
        virtual ~Tile();

        virtual void Initialize();
        virtual void Update();
        virtual void LateUpdate();
        virtual void Render();
    private:
        Vector2 mCoord;
        Vector3 mPosition;
    };
}

