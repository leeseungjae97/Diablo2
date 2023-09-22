#pragma once
#include "mSkill.h"
namespace m
{
    class TileAffectOverlay;

    class SkillFollowing :
        public Skill
    {
    public:
        SkillFollowing(eSkillType type, GameObject* owner, int count, Vector3 initPos, Camera* camera);
        virtual ~SkillFollowing();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;

        void SetFollowerGenerateTime(float time) { fFollowerGenerateTime = time; }
        void SetFollowerLoopCount(int loopCount) { iFollowerLoopCount = loopCount; }

    private:
        void makeFollower();
        void generateFollower();

    private:
        std::vector<TileAffectOverlay*> followers;
        GameObject* mFollowing;
        int iFollowerCount;
        int iCurCount;
        int iFollowerLoopCount;
        float fFollowerGenerateTime;
        float fAcc;
    };
}

