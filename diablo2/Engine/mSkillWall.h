#pragma once
#include "mSkill.h"
namespace m
{
    class SkillWall :
        public Skill
    {
    public:
        SkillWall(eSkillType type, Vector3 initPos, Camera* camera, eLayerType ownerLayer);
        virtual ~SkillWall();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;

    private:
        void makeNormalVector(Camera* camera, Vector3 initPos, eSkillType type);

    private:
    };
}

