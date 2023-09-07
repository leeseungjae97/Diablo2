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

        //for(float i = 0.0f ; i <= 1.f ;)
        //{
        //    SkillStraight* ss = new SkillStraight(eSkillType::iceBolt, Vector3::Zero, 600.f);
        //    sectionSkills.push_back(ss);
        //    i += 0.05f;
        //}
        for(int i = 0 ; i < 30; ++i)
        {
            SkillStraight* ss = new SkillStraight(eSkillType::iceBolt, Vector3::Zero, 600.f);
            ss->SetName(L"orb");
            sectionSkills2.push_back(ss);
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
            //for (SkillStraight* ss : sectionSkills)
            //{
            //    ss->SetCamera(GetCamera());
            //    SceneManager::GetActiveScene()->AddGameObject(GetLayerType(), ss);
            //}

            for (SkillStraight* ss : sectionSkills2)
            {
                ss->SetCamera(GetCamera());
                SceneManager::GetActiveScene()->AddGameObject(GetLayerType(), ss);
            }
            bCameraUpdate = true;

            fireCircle();
        }
        if(!bMove)
        {
            //for (SkillStraight* ss : sectionSkills)
            //{
            //    ss->SetState(Delete);
            //}

            for (SkillStraight* ss : sectionSkills2)
            {
                ss->SetState(Delete);
            }
        }
        /*mAccSkillTime += Time::fDeltaTime();
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
            
        }*/
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
        
        for(float i = 0; i < sectionSkills2.size(); ++i )
        {
            Vector3 pos = GET_POS(this);
            SET_POS_VEC(sectionSkills2[i], pos);
            sectionSkills2[i]->SetInitializePosition(pos);
            float degree = 360 / sectionSkills2.size() * (i + 1);

            float theta = DegreeToRadian(degree);

            //if (degree >= 180) theta *= -1;

            pos.y += cosf(theta);
            pos.x += sinf(theta);

            //if (degree >= 180)
            //    pos.y -= cosf(theta);
            //else 
            //    pos.y += cosf(theta);


            //if (degree >= 180)
            //{
            //    pos.y -= cosf(theta);
            //    pos.x -= sinf(theta);
            //}
            //else if (degree < 180)
            //{

            //}
            sectionSkills2[i]->SetDestPosition(pos);
            sectionSkills2[i]->SkillFire();
        }
    }
}
