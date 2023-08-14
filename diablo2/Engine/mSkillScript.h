#pragma once
#include "../engine_source/mScript.h"
#include "../engine_source/mAnimator.h"
#include "../engine_source/mAnimation.h"
#include "../engine_source/mMaterial.h"
#include "../engine_source/mResources.h"
#include "../engine_source/SkillLookUpTables.h"
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

        //virtual void OnCollisionEnter(Collider2D* other) override;
        //virtual void OnCollisionStay(Collider2D* other) override;
        //virtual void OnCollisionExit(Collider2D* other) override;
    protected:
        Animator* mAnimator;
        eSkillDirection mDirection;
        eSkillType mType;
    };
}

