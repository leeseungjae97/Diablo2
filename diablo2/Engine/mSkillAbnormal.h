#pragma once
#include "mSkill.h"
namespace m
{
    class AbnormalScript;

    class SkillAbnormal :
        public Skill
    {
    public:
        SkillAbnormal(eSkillType type, Vector3 initPos);
        virtual ~SkillAbnormal();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;

        void SetAbnormalCollider(Collider2D* col);
    private:
        AbnormalScript* mAS;

    };
}

