#pragma once
#include "mSkill.h"

#include "mFallScript.h"

namespace m
{
    class SkillFall :
        public Skill
    {
    public:
        SkillFall(eSkillType type, Vector3 iniPos, eAccessorySkillType _acType = eAccessorySkillType::END);
        virtual ~SkillFall();

        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;
        virtual void Initialize() override;

        void SkillFire() { bSkillFire = true; }
    private:
        std::vector<SkillFall*> fallGroup;
        FallScript* mFs;
        float fInitYValue;
        bool bSkillFire;
        bool bMove;
    };
}

