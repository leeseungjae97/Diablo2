#pragma once
#include "../engine_source/mScript.h"
namespace m
{
    class ChainScript :
        public Script
    {
    public:
        ChainScript();
        virtual ~ChainScript();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;

    private:
    };
}

