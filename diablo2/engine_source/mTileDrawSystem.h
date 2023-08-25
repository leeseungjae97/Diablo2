#pragma once
#include "mMeshRenderer.h"
#include "mStructedBuffer.h"
#include "mTileComputeShader.h"
#include "mTileManager.h"
#include "mTileDrawComputeShader.h"

namespace m
{
    class TileDrawSystem :
        public MeshRenderer
    {
    public:
        TileDrawSystem();
        virtual ~TileDrawSystem();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;

        void MakePathTileBuffer(std::vector<Tile*> pathtiles);
    private:
        graphics::StructuredBuffer* mPathTileBuffer;
        graphics::StructuredBuffer* mSharedBuffer;

        int mTileSize;
        std::shared_ptr<TileDrawComputeShader> mCS;
    };
}

