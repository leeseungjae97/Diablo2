#pragma once
#include "mSkill.h"
namespace m
{
    class StraightScript;

    class SkillCurve :
        public Skill
    {
    public:
        SkillCurve(eSkillType type, Vector3 iniPos, float speed);
        virtual ~SkillCurve();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;

        void SetAddCurve(float degree) { mAddCurve = degree; }
    private:
        void moveCurve();

    private:
        float mOriginDegree;
        float mAddCurve;
        float macc;
        
        StraightScript* ss;

        bool bLock;
        int iLockCount;
    };
}

