#pragma once
#include "mSkill.h"
namespace m
{
    class SkillStraight :
        public Skill
    {
    public:
        SkillStraight(eSkillType type, Vector3 iniPos);
        virtual ~SkillStraight();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;

        virtual void Hit(int damage) override;
    private:
    };
}

