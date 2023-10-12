#pragma once
#include "MoveAbleObjectAnimLookUpTables.h"
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

        void SetNoHit(bool hit) { bNoHit = hit; }

        void SkillFire() { bSkillFire = true; }
        void Mute(bool mute) { bMute = mute; }

    private:
        int mDirectionCount;
        bool bNoHit;
        bool bSkillFire;
        bool bMute;

        std::wstring skillName;
        eSixteenDirection* mDirections;
        eSkillCrashType mSkillCrashType;
        eCrashType mCrashType;
    };
}

