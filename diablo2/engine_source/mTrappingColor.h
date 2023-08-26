#pragma once
#include "mMeshRenderer.h"
#include "mStructedBuffer.h"

namespace m
{
    class TrappingColor :
        public MeshRenderer
    {
    public:
        TrappingColor();
        virtual ~TrappingColor();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;

        void SetColor(Vector4 color) { mTrappingColor.color = color; }
    private:
        TrapColor mTrappingColor;
        graphics::StructuredBuffer* mTrappingColorBuffer;
    };
}

