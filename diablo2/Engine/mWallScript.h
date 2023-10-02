#pragma once
#include "../engine_source/mScript.h"
namespace m
{
    class WallScript :
        public Script
    {
    public:
        WallScript();
        virtual ~WallScript();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;
    private:
    };
}