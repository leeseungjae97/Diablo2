#include "mSkillOrb.h"

#include "mInput.h"
#include "mSceneManager.h"

namespace m
{
    SkillOrb::SkillOrb(eSkillType type, Vector3 iniPos, float speed)
        : SkillStraight(type, iniPos, speed)
        , mAccSkillTime(0.f)
        , mSectionActiveCount(0)
        , mRandomCircleDegree(45.f)
        , bCameraUpdate(false)
    {
        SetLimitDistance(400.f);

        for(float i = 0.0f ; i <= 1.f ;)
        {
            SkillStraight* ss = new SkillStraight(eSkillType::iceBolt, Vector3::Zero, 300.f);
            SceneManager::GetActiveScene()->AddGameObject(GetLayerType(), ss);
            sectionSkills.push_back(ss);
            sectionTimes.push_back(i);
            i += 0.05f;
        }
    }

    SkillOrb::~SkillOrb()
    {
    }

    void SkillOrb::Initialize()
    {
        SkillStraight::Initialize();
    }

    void SkillOrb::Update()
    {
        SkillStraight::Update();
        if(!bCameraUpdate)
        {
            for (SkillStraight* ss : sectionSkills) ss->SetCamera(GetCamera());
            bCameraUpdate = true;
        }

        mAccSkillTime += Time::fDeltaTime();
        if(mSectionActiveCount < sectionSkills.size()
            &&
            mAccSkillTime >= 0.05f)
        {
            fireRandomDegreeSkill(sectionSkills[mSectionActiveCount]);
            sectionSkills[mSectionActiveCount]->SkillFire();
            mAccSkillTime = 0.f;
            ++mSectionActiveCount;
        }
        if (mSectionActiveCount >= sectionSkills.size())
        {
            // circle fire
        }
    }

    void SkillOrb::LateUpdate()
    {
        SkillStraight::LateUpdate();
    }

    void SkillOrb::Render()
    {
        SkillStraight::Render();
    }
    void SkillOrb::fireRandomDegreeSkill(SkillStraight* skill)
    {
        SET_POS_VEC(skill, GET_POS(this));
        
        if (mRandomCircleDegree >= 360.f)
        {
            mRandomCircleDegree = 0.f;
            
        }else
        {
            //mRandomCircleDegree -= 30.f;
            //mRandomCircleDegree += 60.f;
        }
        mRandomCircleDegree += 60.f;
        

        float theta = DegreeToRadian(mRandomCircleDegree);
        Vector3 pos = GET_POS(this);
        skill->SetInitializePosition(pos);

        pos.x += sinf(theta); 
        pos.y += cosf(theta);

        skill->SetDestPosition(pos);
    }
    void SkillOrb::fireCircle()
    {
        Vector3 pos = GET_POS(this);
        for(int i = 0; i < 20; ++i )
        {
            float theta = DegreeToRadian(360 / 20 * i);
            SkillStraight* ss = new SkillStraight(eSkillType::iceBolt, pos, 300.f);
            ss->SetDestPosition(Vector3(cosf(theta), sinf(theta), pos.z));
            ss->SetCamera(GetCamera());
            ss->SkillFire();

            SceneManager::GetActiveScene()->AddGameObject(GetLayerType(), ss);
        }
    }
}
