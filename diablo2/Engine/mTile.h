#pragma once
#include "../engine_source/mGameObject.h"
#include "../engine_source/mMaterial.h"

namespace m
{
    class Tile :
        public GameObject
    {
    public:
        
        Tile();
        virtual ~Tile();

        virtual void Initialize();
        virtual void Update();
        virtual void LateUpdate();
        virtual void Render();

        bool GetIsWall() { return isWall; }
        void SetIsWall(bool iw) { isWall = iw; }

        Vector2 GetCoord() { return mCoord; }
        void SetCoord(Vector2 coord) { mCoord = coord; }

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
    private:
        Tile* mParentTile;
        Tile* child;
        Vector2 mCoord;
        std::shared_ptr<Material> saveMaterial;
        bool isWall;
        bool inClosed;
        bool inOpen;
        int G; // from cost
        int H; // expected cost

    };
}

