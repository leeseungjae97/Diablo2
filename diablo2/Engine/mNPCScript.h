#pragma once
#include "mScript.h"
#include "../engine_source/NPCLookUpTables.h"

namespace m
{
    class NPCScript :
        public Script
    {
    public:
        NPCScript(eNPCType type);
        virtual ~NPCScript();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;

    private:
        Animator* mAnimator;
        eNPCType mNPCType;
    };
}
