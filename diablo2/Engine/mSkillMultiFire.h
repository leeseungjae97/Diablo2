#pragma once
#include "mSkill.h"

#include "mSkillFall.h"
#include "mSkillStraight.h"
namespace m
{
    class SkillMultiFire :
        public Skill
    {
    public:
        enum class eFireType
        {
            Linear,
            Random,
            END,
        };

        SkillMultiFire(eSkillType type, Vector3 iniPos, int count = 2, eFireType bFireType = eFireType::END, Vector2 randFireArange = Vector2::Zero);
        virtual ~SkillMultiFire();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;

    private:
        std::vector<SkillFall*> skills;
        std::vector<float> mSkillFireTimes;
        eFireType mFireType;
        int curFallIndex;
        float mAccTime;
    };
}

