#pragma once
#include "../engine_source/mScript.h"
namespace m
{
    class TileScript :
        public Script
    {
    public:
        TileScript();
        virtual ~TileScript();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;

    private:
    };
}

