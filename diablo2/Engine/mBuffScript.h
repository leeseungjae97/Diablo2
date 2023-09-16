#pragma once
#include "mScript.h"
namespace m
{
    class BuffScript :
        public Script
    {
    public:
        BuffScript();
        virtual ~BuffScript();

        virtual void Update() override; 
        virtual void LateUpdate() override; 
        virtual void Initialize() override; 
        virtual void Render() override; 
    private:
    };
}

