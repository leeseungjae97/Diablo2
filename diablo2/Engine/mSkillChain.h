#pragma once
#include "mChainScript.h"
#include "mSkill.h"

namespace m
{
    class SkillMultiFire;
    class SkillStraight;

    class SkillChain :
        public Skill
    {
    public:
        SkillChain(eSkillType type, Vector3 initPos, int chainCount, eLayerType layerType, Camera* camera);
        virtual ~SkillChain();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;

    private:
        bool searchChain();
        void firstLinearCount(Vector3 initPos);

    private:
        MoveAbleObject* mTarget;
        MoveAbleObject* mPrevTarget;
        eLayerType mFireLayerType;
        Skill* mCurChainHead;
        ChainScript* mCS;

        std::vector<Monster*> chainMonsters;
        bool bFire;

        int iChainCount;
        int iChainMissileCount;
    };

}

