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

        SkillMultiFire(Vector3 iniPos
            , eSkillType type
            , int count = 2
            , eFireType bFireType = eFireType::END
            , eLayerType layerType = eLayerType::Skill
            , Vector2 randFireArange = Vector2::Zero);
        virtual ~SkillMultiFire();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;

    private:
        std::vector<Skill*> skills;
        std::vector<float> mSkillFireTimes;
        eFireType mFireType;
        int curFallIndex;
        float mAccTime;
        bool bFirstUpdate;
    };
}

