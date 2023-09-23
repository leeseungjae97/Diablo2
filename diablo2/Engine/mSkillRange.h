#pragma once
#include "mSkill.h"
namespace m
{
    class RangeScript;

    class SkillRange :
        public Skill
    {
    public:
        SkillRange(eSkillType type, GameObject* owner, eLayerType layerType, Camera* camera);
        virtual ~SkillRange();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;

    private:
        GameObject* mCenterOwner;
        RangeScript* mRS;
    };
}


