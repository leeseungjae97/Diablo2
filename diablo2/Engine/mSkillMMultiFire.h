#pragma once
#include "mSkill.h"

namespace m
{
    class SkillMultiFire;
    class SkillMMultiFire :
        public Skill
    {
    public:
        SkillMMultiFire(eSkillType type, Vector3 initPos, int count, eLayerType layerType, Camera* camera);
        virtual ~SkillMMultiFire();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;
    private:
        std::vector<SkillMultiFire*> skills;
    };
}

