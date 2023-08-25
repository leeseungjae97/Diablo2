#pragma once
#include "mComputeShader.h"
namespace m::graphics
{
    class TileDrawComputeShader :
        public ComputeShader
    {
    public:
        TileDrawComputeShader();
        TileDrawComputeShader(int x, int y, int z);
        virtual ~TileDrawComputeShader();

        virtual void Binds() override;
        virtual void Clear() override;

        virtual void OnExcute() override;

        void SetPathTileBuffer(StructuredBuffer* buffer) { mPathTileBuffer = buffer; }
        //void SetCamera(Camera* camera) { mCamera = camera; }
    private:
        StructuredBuffer* mPathTileBuffer;
        //Camera* mCamera;
    };
}

