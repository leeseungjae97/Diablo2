#pragma once

#include "../engine_source/SkillLookUpTables.h"

#include "mMoveAbleObject.h"
namespace m
{
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


    private:
        eSkillType mSkillType;
        bool bSkillFire;
    };
}

