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

        bool GetIsWall() { return isWall; }
        void SetIsWall(bool iw) { isWall = iw; }

        int GetF() const { return G + H; }
    private:
        Vector2 mCoord;
        bool isWall;
        int G; // from cost
        int H; // expected cost

        // 수직, 수평 이동 10
        // 대각선 이동 14
    };
}

