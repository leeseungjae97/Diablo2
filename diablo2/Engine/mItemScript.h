#pragma once
#include "../engine_source/mScript.h"
namespace m
{
    class ItemScript :
        public Script
    {
    public:
        ItemScript();
        virtual ~ItemScript();

        virtual void Initialize() override;
        virtual void Update() override;
    private:
    };
}

