#pragma once
#include "../engine_source/mScript.h"
#include "../engine_source/mAnimation.h"
#include "../engine_source/SkillLookUpTables.h"
#include "../engine_source/SkillAnimLookUpTables.h"

namespace m
{
    class SkillScript :
        public Script
    {
    public:
        SkillScript();
        virtual ~SkillScript();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;

        virtual void SetSkillType(eSkillType type) { mType = type; }

        //virtual void OnCollisionEnter(Collider2D* other) override;
        //virtual void OnCollisionStay(Collider2D* other) override;
        //virtual void OnCollisionExit(Collider2D* other) override;
    protected:
        Animator* mAnimator;
        int mDirection;
        eSkillType mType;
    };
}

