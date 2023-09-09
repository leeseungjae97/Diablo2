#pragma once
#include "mSkillStraight.h"
namespace m
{
    class SkillCurve;
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
        void fireThreeWayDegreeSkill(SkillStraight* skill);
        void fireCircle();

    private:
        std::vector<SkillStraight*> sectionSkills;
        std::vector<SkillCurve*> sectionSkills2;

        bool bCameraUpdate;
        int mAddCircleDegree;
        int mAccDegree;
        int iLock;
        

        int iInitDegrees[3] = {-135, -45, 45};
        int iAddDegrees[3] = {135, 90, 60};
        int iNDuplicates[3] = {};
        int iMDuplicates[3] = {};
        int iNumUse;
        float mAccSkillTime;

        bool bFireCircle;
        int mSectionActiveCount;
    }; 
}

