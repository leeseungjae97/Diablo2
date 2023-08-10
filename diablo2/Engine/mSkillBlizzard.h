#pragma once
#include "mSkill.h"
namespace m
{
    class SkillBlizzard :
        public Skill
    {
    public:
        SkillBlizzard(eSkillType type, Vector3 iniPos);
        virtual ~SkillBlizzard();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;
    private:
    };
}

