#pragma once
#include "mMeshRenderer.h"
#include "mStructedBuffer.h"
#include "mPathFinderComputeShader.h"
#include "mPathFinder.h"
namespace m
{
    class PathFinderSystem :
        public MeshRenderer
    {
    public:
        PathFinderSystem();
        virtual ~PathFinderSystem();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;

        //void SetPathFinder(PathFinder* pathfinder) { mOwnerpathFinder = pathfinder; }

        void OpenVectorAdd(Tile* curTile);
    private:
        graphics::StructuredBuffer* mBuffer;
        std::shared_ptr<PathFinderComputeShader> mCS;
        //PathFinder* mOwnerpathFinder;
    };
}

