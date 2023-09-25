#pragma once
#include "../engine_source/mScript.h"
namespace m
{
    class MoveAbleObject;

    class ChainScript :
        public Script
    {
    public:
        ChainScript(MoveAbleObject* target, MoveAbleObject* prevTarget, int chainCount);
        virtual ~ChainScript();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;

        int GetChianCount() { return iChainCount; }
        void UpdateCollideredMonster();
    private:
        MoveAbleObject* mTarget;
        MoveAbleObject* mPrevTarget;
        int iChainCount;

        std::vector<MoveAbleObject*> chainMonsters;

    };
}

