#pragma once
#include "mHandScript.h"
namespace m
{
    class RightHandScript :
        public HandScript
    {
    public:
        RightHandScript();
        virtual ~RightHandScript();

        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;
        virtual void Initialize() override;
    private:
    };
}


