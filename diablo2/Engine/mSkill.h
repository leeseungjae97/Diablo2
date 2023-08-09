#pragma once

#include "../engine_source/SkillLookUpTables.h"
#include "../engine_source/mTime.h"
#include "../engine_source/mAnimator.h"

#include "mMoveAbleObject.h"
namespace m
{
    class Skill :
        public MoveAbleObject
    {
    public:
        Skill(eSkillType type
            , Vector3 iniPos
            , bool useHitArea = false
            , bool useRange = false
            , bool useTilePos = false
            , bool useAstar = false
        );
        virtual ~Skill();

        virtual void Initialize();
        virtual void Update();
        virtual void LateUpdate();
        virtual void Render();

        virtual void Hit(int damage) override;
        eSkillType GetSkillType() { return mSkillType; }

        bool GetSkillFire() { return bSkillFire; }
        bool GetSkillCrash() { return bSkillCrash; }

        void SetSkillFire(bool fire) { bSkillFire = fire; }
        void SetSkillCrash(bool crash) { bSkillCrash = crash; }

    protected:
        eSkillType mSkillType;
        bool bSkillFire;
        bool bSkillCrash;
    };
}

