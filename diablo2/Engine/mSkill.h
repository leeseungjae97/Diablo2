#pragma once

#include "../engine_source/mTime.h"
#include "../engine_source/mAnimator.h"
#include "../engine_source/SkillLookUpTables.h"
#include "../engine_source/SkillAnimLookUpTables.h"

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

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;

        virtual void Hit(int damage) override;
        eSkillType GetSkillType() { return mSkillType; }

        bool GetSkillFire() { return bSkillFire; }
        bool GetSkillCrash() { return bSkillCrash; }

        void SetSkillFire(bool fire) { bSkillFire = fire; }
        void SetSkillCrash(bool crash) { bSkillCrash = crash; }

        void SetSkillOwner(eLayerType ownerType);
        eLayerType GetSkillOwner() { return skillOwnerType; }


        void SkillFire() { bSkillFire = true; }
    protected:
        eSkillType mSkillType;
        bool bSkillFire;
        bool bSkillCrash;
        eLayerType skillOwnerType;
    };
}

