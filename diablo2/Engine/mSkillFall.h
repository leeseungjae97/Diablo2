#pragma once
#include "mSkill.h"

namespace m
{
    class SkillFall :
        public Skill
    {
    public:
        SkillFall(eSkillType type, Vector3 iniPos);
        virtual ~SkillFall();

        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;
        virtual void Initialize() override;

    private:
        float fInitYValue;
        float fSpeed;

    };
}

