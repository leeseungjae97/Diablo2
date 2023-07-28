#pragma once
#include "../engine_source/mScript.h"
#include "../engine_source/AnimLookUpTables.h"
#include "../engine_source/mResources.h"

namespace m
{
    class Animator;
    template <typename T>
    class MonsterScript :
        public Script
    {
    public:
        MonsterScript();
        virtual ~MonsterScript();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;

    private:
        std::vector<SHARED_TEX> texs;
        Animator* mAnimator;
    };
}

