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
        void fireRandomDegreeSkill(SkillStraight* skill);
        void fireCircle();
    private:
        std::vector<SkillStraight*> sectionSkills;
        std::vector<SkillStraight*> sectionSkills2;

        bool bCameraUpdate;
        float mRandomCircleDegree;
        float mAccSkillTime;

        int mSectionActiveCount;
    }; 
}

