#pragma once
#include "mComputeShader.h"
#include "mStructedBuffer.h"
#include "mCamera.h"
namespace m::graphics
{
    class PathFinderComputeShader :
        public ComputeShader
    {
    public:
        PathFinderComputeShader(int x, int y, int z);
        PathFinderComputeShader();
        virtual ~PathFinderComputeShader();

        void SetPathFinderTileBuffer(StructuredBuffer* buffer) { mPathFinderTileBuffer = buffer; }

        virtual void Binds() override;
        virtual void Clear() override;

        virtual void OnExcute() override;

        void SetCamera(Camera* camera) { mCamera = camera; };
        Camera* GetCamera() { return mCamera; }

    private:
        StructuredBuffer* mPathFinderTileBuffer;

        Camera* mCamera;
    };
}

