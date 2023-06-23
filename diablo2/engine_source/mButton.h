#pragma once
#include "mBackground.h"
namespace m
{
    class Button :
        public Background
    {
    public:
        Button();
        ~Button();

        virtual void Initialize();
        virtual void Update();
        virtual void LateUpdate();
        virtual void Render();

        bool GetHover() { return bHover; }
        bool GetClick() { return bClick; }
    private:
        bool bHover;
        bool bClick;
    };
}

