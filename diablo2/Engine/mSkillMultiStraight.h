#pragma once
#include "mSkill.h"
namespace m
{
    class SkillMultiStraight :
        public Skill
    {
    public:
        SkillMultiStraight(eSkillType type, Vector3 iniPos, int count, int fireType);
        virtual ~SkillMultiStraight();
        
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;
        virtual void Initialize() override;
    private:
        int mCount;
        int mFireType;
    };
}

