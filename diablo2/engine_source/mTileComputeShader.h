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
    private:
        StructedBuffer* mTileBuffer;
        StructedBuffer* mSharedBuffer;
    };
}

