#pragma once
#include "mSkill.h"

#include "mSkillFall.h"
namespace m
{
    class SkillMultiFall :
        public Skill
    {
    public:
        SkillMultiFall(eSkillType type, Vector3 iniPos, int fallcount = 2, bool bRandFall = true);
        virtual ~SkillMultiFall();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;

    private:
        std::vector<SkillFall*> fallFragments;
        std::vector<float> randFall;
        bool mbRandFall;
        int curFallIndex;
        float mAccTime;
    };
}

