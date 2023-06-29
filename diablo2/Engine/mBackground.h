#pragma once
#include "..\engine_source\mGameObject.h"
namespace m
{
    class Background :
        public GameObject
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

