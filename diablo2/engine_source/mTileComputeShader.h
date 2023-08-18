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

        void SetTileBuffer(StructedBuffer* particleBuffer);
        void SetSharedBuffer(StructedBuffer* sharedBuffer) { mSharedBuffer = sharedBuffer; }


        virtual void OnExcute(ComputeTileCoord** data, int size);

        void SetCamera(Camera* camera) { mCamera = camera; }
        Camera* GetCamera() { return mCamera; }

    private:
        StructedBuffer* mTileBuffer;
        StructedBuffer* mSharedBuffer;
        Camera* mCamera;
    };
}

