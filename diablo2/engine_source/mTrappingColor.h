#pragma once
#include "mComponent.h"
#include "mStructedBuffer.h"

namespace m
{
    class TrappingColor :
        public Component
    {
    public:
        TrappingColor();
        virtual ~TrappingColor();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;

        void SetColor(Vector4 color) { mTrappinColor.color = color; }
    private:
        TrapColor mTrappinColor;
        graphics::StructuredBuffer* mTrappingColorBuffer;
    };
}

