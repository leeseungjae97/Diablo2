#pragma once
#include "mSkill.h"
#include "mStraightScript.h"
namespace m
{
    class SkillStraight :
        public Skill
    {
    public:
        SkillStraight(eSkillType type, Vector3 iniPos, float speed, bool useLimitDistance = true);
        virtual ~SkillStraight();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;

        virtual void Hit(int damage, bool attackStun) override;

        void SetLimitDistance(float distance) { limitDistance = distance; }
        float GetLimitDistance() { return limitDistance; }
        float GetMoveDistance() { return moveDistance; }
        void StopMove() { bMove = false; }
    private:
        StraightScript* ss;
        float limitDistance;
        bool useLimit;

        float moveDistance;
    };
}

