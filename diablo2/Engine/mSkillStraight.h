#pragma once
#include "mSkill.h"
#include "mStraightScript.h"
namespace m
{
    class SkillStraight :
        public Skill
    {
    public:
        SkillStraight(eSkillType type, Vector3 iniPos, float speed, bool useLimitDistance = true
                        , bool useAnimator = true);
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
        void SetRandomStraight(float randomY, float fRandomTime);

        void Head() { bHead = true; }
        void HeadLinear() { bUseHead = true; }
        void SetHead(SkillStraight* head) { mHead = head; }

        bool IsHead() { return bHead; }
        bool GetHeadLinear() { return bUseHead; }
        SkillStraight* GetHead() { return mHead; }
    private:
        void randomY();

    private:
        StraightScript* ss;
        float limitDistance;
        bool useLimit;
        int randSign;

        SkillStraight* mHead;
        bool bHead;
        bool bUseHead;

        float moveDistance;
        float fRandomRange;
        float fRandomMoveAcc;
        float fRandomMoveTime;
    };
}

