#pragma once
#include "mSkillFall.h"
namespace m
{
    class SkillIndicator;

    class SkillFallExplosion :
        public Skill
    {
    public:
        SkillFallExplosion(eSkillType type, Vector3 iniPos, eLayerType layerType);
        virtual ~SkillFallExplosion();

        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;
        virtual void Initialize() override;

        bool ReturnCrash();
    private:
        void updateSkills();

    private:

        std::vector<SkillFall*> skills;
        SkillIndicator* mIndicator;
    };
}

