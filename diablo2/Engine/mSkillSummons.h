#pragma once
#include "mMoveAbleObject.h"

namespace m
{
    class SkillSummons :
        public MoveAbleObject
    {
    public:
        SkillSummons(int type, Vector3 initPos, Vector3 vLookDirection, float summonTime);
        virtual ~SkillSummons();

        virtual void Initialize() override;
        
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;

        void Hit(int damage, bool attackStun = false);

    private:
        void updateAttackDirection();

    private:
        float fSummonTime;
        int mType;
    };
}

