#pragma once
#include "mComputeShader.h"
#include "mStructedBuffer.h"
#include "mMaterial.h"
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

        void SetTileBuffer(StructuredBuffer* buffer) { mTileBuffer = buffer; }
        void SetSharedBuffer(StructuredBuffer* buffer) { mSharedBuffer = buffer; }
        void SetTileCoordBuffer(StructuredBuffer* buffer) { mTileCoordBuffer = buffer; }
        void SetMonsterBuffer(StructuredBuffer* buffer) { mMonsterBuffer = buffer; }
        void SetMonsterCoordBuffer(StructuredBuffer* buffer) { mMonsterCoordBuffer = buffer; }
        void SetSkillBuffer(StructuredBuffer* buffer) { mSkillBuffer = buffer; }
        void SetGSkillBuffer(StructuredBuffer* buffer) { mGSkillBuffer = buffer; }

        virtual void OnExcute(ComputedTileCoord** data, int size, ComputedMonsterCoord** data2, int size2, SkillWallCollision** data3, int size3);

        //void SetCamera(Camera* camera) { mCamera = camera; }
        //Camera* GetCamera() { return mCamera; }

    private:
        StructuredBuffer* mTileBuffer;
        StructuredBuffer* mSharedBuffer;
        StructuredBuffer* mTileCoordBuffer;
        StructuredBuffer* mMonsterBuffer;
        StructuredBuffer* mMonsterCoordBuffer;
        StructuredBuffer* mSkillBuffer;
        StructuredBuffer* mGSkillBuffer;
        //Camera* mCamera;
    };
}

