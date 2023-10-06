#pragma once
#include "../engine_source/mGameObject.h"
#include "../engine_source/mMaterial.h"

namespace m
{
    class Tile
    {
    public:
        
        Tile();
        virtual ~Tile();


        bool GetIsWall() { return isWall; }
        bool GetIsThrough() { return isThrough; }
        void SetIsWall(bool iw) { isWall = iw; }
        void SetThroughWall(bool through) { isThrough = through; }

        bool GetOnMonster() { return onMonster; }
        void SetOnMonster(bool on) { onMonster = on; }

        Vector2 GetCoord() { return mCoord; }
        void SetCoord(Vector2 coord) { mCoord = coord; }

        int GetMonsterNext() { return willOnMonsterCount; }
        void SetMonsterNext() { ++willOnMonsterCount; }
        void UnSetMonsterNext() { willOnMonsterCount != 0 ? --willOnMonsterCount : willOnMonsterCount; }

        int GetF() const { return G + H; }
        int GetG() const { return G; }
        int GetH() const { return H; }

        void SetG(int g) { G = g; }
        void SetH(int h) { H = h; }
        
        void SetInClosed(bool closed) { inClosed = closed; }
        bool GetInClosed() { return inClosed; }

        void SetInOpen(bool open) { inOpen = open; }
        bool GetInOpen() { return inOpen; }

        void SetParentTile(Tile* parentTile) { mParentTile = parentTile; }
        Tile* GetParentTile() { return mParentTile; }

        void SetSaveMaterial(std::shared_ptr<Material> mat) { saveMaterial = mat; }
        std::shared_ptr<Material> GetSaveMaterial() { return saveMaterial; }

        Vector3 GetPos() { return mPos; }
        void SetPos(Vector3 pos) { mPos = pos; }

        Vector3 GetScale() { return mScale; }
        void SetScale(Vector3 scale) { mScale = scale; }

    private:
        Tile* mParentTile;
        Vector2 mCoord;
        Vector3 mPos;
        Vector3 mScale;
        std::shared_ptr<Material> saveMaterial;
        bool isWall;
        bool isThrough;
        bool onMonster;
        int willOnMonsterCount;
        bool inClosed;
        bool inOpen;
        int G; // from cost
        int H; // expected cost

    };
}

