#pragma once
#include "mGameObject.h"
#include "SkillAnimLookUpTables.h"

namespace m
{
    class Skill;

    class SkillIndicator :
        public GameObject
    {
    public:
        SkillIndicator(Vector3 initPos, eIndicatorType type);
        virtual ~SkillIndicator();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;

        void IndicatorOff();
        void SetOwnerSkill(Skill* skill) { mOwner = skill; }
    private:
        Animator* mAnimator;
        Skill* mOwner;
    };
}

