#pragma once
#include "mSkillStraight.h"
namespace m
{
    class SkillOrb :
        public SkillStraight
    {
    public:
        SkillOrb(eSkillType type, Vector3 iniPos, float speed);
        virtual ~SkillOrb();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;

    private:

    }; 
}

