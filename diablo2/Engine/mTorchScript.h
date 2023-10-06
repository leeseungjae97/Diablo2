#pragma once
#include "../engine_source/mScript.h"

#include "../engine_source/TorchLookUpTables.h"

namespace m
{
    class TorchScript :
        public Script
    {
    public:
        TorchScript(eTorchType type);
        virtual ~TorchScript();

        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;
        virtual void Initialize() override;
    private:
        Animator* mAnimator;
        eTorchType mTorchType;
    };
}

