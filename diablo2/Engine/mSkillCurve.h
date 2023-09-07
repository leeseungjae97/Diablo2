#pragma once
#include "mSkillStraight.h"
namespace m
{
    class SkillCurve :
        public SkillStraight
    {
    public:
        SkillCurve(eSkillType type, Vector3 iniPos, float speed);
        virtual ~SkillCurve();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;

        virtual void Hit(int damage) override;
    private:
    };
}

