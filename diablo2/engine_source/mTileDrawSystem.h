#pragma once
#include "mMeshRenderer.h"
#include "mStructedBuffer.h"
#include "mTileComputeShader.h"
#include "mTileManager.h"

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


    private:
        graphics::StructedBuffer* mBuffer;
        graphics::StructedBuffer* mSharedBuffer
    	;
        std::shared_ptr<TileComputeShader> mCS;
    };
}

