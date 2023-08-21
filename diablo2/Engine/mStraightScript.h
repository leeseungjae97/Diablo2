#pragma once
#include "mSkillScript.h"

namespace m
{
    class StraightScript :
        public SkillScript
    {
    public:
        StraightScript(int _directionCount = 16);
        virtual ~StraightScript();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;

        virtual void OnCollisionEnter(Collider2D* other) override;
        virtual void OnCollisionStay(Collider2D* other) override;
        virtual void OnCollisionExit(Collider2D* other) override;
    private:
        int mDirectionCount;
        eSixteenDirection* mDirections;
        eSkillCrashType mSkillCrashType;
        eCrashType mCrashType;
    };
}

