#pragma once
#include "mSkill.h"
namespace m
{
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

    private:
        MoveAbleObject* mTarget;
        MoveAbleObject* mPrevTarget;
        eLayerType mLayerType;
        std::vector<Monster*> chainMonsters;
        bool bFire;

        int iChainCount;
        int iChainMissileCount;
    };

}

