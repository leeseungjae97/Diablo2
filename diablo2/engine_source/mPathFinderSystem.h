#pragma once
#include "mMeshRenderer.h"
#include "mStructedBuffer.h"
#include "mPathFinderComputeShader.h"

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

    private:
        graphics::StructedBuffer* mBuffer;

        std::shared_ptr<PathFinderComputeShader> mCS;
    };
}

