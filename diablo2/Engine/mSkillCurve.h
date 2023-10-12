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
        void StopMove() { bMove = false; }

        void Mute(bool mute) { bMute = mute; }
        bool IsMute() { return bMute; }
    private:
        void moveCurve();

    private:
        float mOriginDegree;
        float mAddCurve;
        float macc;
        
        StraightScript* ss;
        bool bMute;

        bool bLock;
        int iLockCount;
    };
}

