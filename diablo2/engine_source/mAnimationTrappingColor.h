#pragma once
#include "mComponent.h"
#include "mGraphics.h"
#include "mStructedBuffer.h"

namespace m
{
    class AnimationTrappingColor :
        public Component
    {
    public:
        AnimationTrappingColor();
        virtual ~AnimationTrappingColor();

        virtual void Initialize();
        virtual void Update();
        virtual void LateUpdate();
        virtual void Render();

        void SetColor(Vector4 color) { mTrappingColor.color = color; }
    private:
        TrapColor mTrappingColor;
        graphics::StructuredBuffer* mTrappingColorBuffer;
    };
}

