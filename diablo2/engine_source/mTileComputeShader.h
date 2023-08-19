#pragma once
#include "mComputeShader.h"
#include "mStructedBuffer.h"

namespace m::graphics
{
    class TileComputeShader :
        public ComputeShader
    {
    public:
        TileComputeShader();
        virtual ~TileComputeShader();

        virtual void Binds() override;
        virtual void Clear() override;

        void SetTileBuffer(StructedBuffer* buffer) { mTileBuffer = buffer; }
        void SetSharedBuffer(StructedBuffer* buffer) { mSharedBuffer = buffer; }
        void SetTileCoordBuffer(StructedBuffer* buffer) { mTileCoordBuffer = buffer; }
        void SetMonsterBuffer(StructedBuffer* buffer) { mMonsterBuffer = buffer; }

        virtual void OnExcute(ComputeTileCoord** data, int size);

        void SetCamera(Camera* camera) { mCamera = camera; }
        Camera* GetCamera() { return mCamera; }

    private:
        StructedBuffer* mTileBuffer;
        StructedBuffer* mSharedBuffer;
        StructedBuffer* mTileCoordBuffer;
        StructedBuffer* mMonsterBuffer;
        Camera* mCamera;
    };
}

