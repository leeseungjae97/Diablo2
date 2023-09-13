#pragma once
#include "mSkillFall.h"

namespace m
{
    class TileAffectOverlay;
}

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

    private:
        void afterFall();
        void updateSkills();
        void makeAffectOverlay(eLayerType type);
        void activeAffectOverlay();

    private:
        std::vector<SkillFall*> skills;
        std::vector<TileAffectOverlay*> overlays;
        SkillIndicator* mIndicator;

        bool bAfterFall;

    };
}

