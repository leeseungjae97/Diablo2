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

        void SetCurveAngle(float degree) { mCurveDegree = degree; }
        void SetCurveDistance(float distance) { mCurveDistance = distance; }

    private:
        Vector2 bezierInterpolate(Vector2 p0, Vector2 p1, Vector2 p2, float t);
        void moveCurve();

    private:
        float mCurveDegree;
        float mAccCurveTheta;
        float mCurveDistance;
        float macc;
        StraightScript* ss;
        Vector2 controlPosition;

        bool m = false;
        int n = 0;
    };
}

