#pragma once
#include "mSkill.h"

#include "mFallScript.h"

namespace m
{
    class SkillFall :
        public Skill
    {
    public:
        SkillFall(eSkillType type, Vector3 iniPos, float fallHeight = 300.f, bool diagonalFall = false, bool deco = false, eAccessorySkillType _acType = eAccessorySkillType::END);
        virtual ~SkillFall();

        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;
        virtual void Initialize() override;


    private:
        void fallArrival();
        void adjustmentPosition();
        void fall();
    protected:
        FallScript* mFs;
        float fInitYValue;
        float mFallHeight;
        bool mDiagonalFall;

    private:
        bool degreeUpdate;
        eSkillType mSkillType;
        eAccessorySkillType mAcType;
    };
}

