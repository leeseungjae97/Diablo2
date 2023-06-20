#pragma once
#include "mComponent.h"
namespace m
{
    class Script :
        public Component
    {
    public:
        Script();
        ~Script();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;
    private:
    };
}

