#pragma once
#include "..\engine_source\mUI.h"
namespace m
{
    class Background :
        public UI
    {
    public:
        Background();
        ~Background();

        virtual void Initialize();
        virtual void Update();
        virtual void LateUpdate();
        virtual void Render();

    private:
    };
}

