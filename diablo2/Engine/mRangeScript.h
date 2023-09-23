#pragma once
#include "mSkillRange.h"
#include "SkillLookUpTables.h"
#include "../engine_source/mScript.h"
namespace m
{
    class RangeScript :
        public Script
    {
    public:
        RangeScript(eSkillType type, eLayerType layerType);
        virtual ~RangeScript();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;
        void ActiveRange() { bActive = true; }
        bool GetActive() { return bActive; }

        bool GetAttackEnd() { return bAttackEnd; }
    private:
        void rangeDamage();

    private:
        eSkillType mSkillType;

        eLayerType mLayerType;
        bool bActive;
        bool bAttackEnd;
    };
}

