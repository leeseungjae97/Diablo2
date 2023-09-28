#pragma once
#include "mComponent.h"
namespace m
{
    class Shadow :
        public Component
    {
    public:
        Shadow();
        virtual ~Shadow();

        virtual void Initialize();
        virtual void Update();
        virtual void LateUpdate();
        virtual void Render();

    private:
    };
}


