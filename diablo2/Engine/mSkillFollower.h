#pragma once
#include "mSkillStraight.h"
namespace m
{
    class TileAffectOverlay;

    class SkillFollower :
        public SkillStraight
    {
    public:
        SkillFollower(eSkillType type, int count, Vector3 initPos, Vector3 destPosition);
        virtual ~SkillFollower();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;

        void SetFollowerGenerateTime(float time) { fFollowerGenerateTime = time; }

    private:
        void generateFollower();
        void makeFollower();

    private:
        std::vector<TileAffectOverlay*> followers;
        int iFollowerCount;
        int iCurCount;
        float fFollowerGenerateTime;
        float fAcc;
    };
}

