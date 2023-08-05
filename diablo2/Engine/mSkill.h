#pragma once

#include "../engine_source/SkillLookUpTables.h"
#include "../engine_source/mTime.h"

#include "mMoveAbleObject.h"
namespace m
{
    class Animator;
    class Skill :
        public MoveAbleObject
    {
    public:
        Skill(eSkillType type, Vector3 iniPos);
        virtual ~Skill();

        virtual void Initialize();
        virtual void Update();
        virtual void LateUpdate();
        virtual void Render();

        virtual void Hit(int damage) override;
        eSkillType GetSkillType() { return mSkillType; }

    protected:
        eSkillType mSkillType;
        bool bSkillFire;
    };
}

