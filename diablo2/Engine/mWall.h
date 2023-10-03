#pragma once
#include "mGameObject.h"

#include "../engine_source/WallLookUpTables.h"
namespace m
{
    class Wall :
        public GameObject
    {
    public:
        Wall(eWallType type, Camera* camera, Vector2 coord);
        virtual ~Wall();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;

        void MarkingWallToPathFinder();
    private:
        eWallType mWallType;
        Vector2 mCoord;
    };
}

