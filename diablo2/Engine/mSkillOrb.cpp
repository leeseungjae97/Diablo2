#include "mSkillOrb.h"

#include "mInput.h"
#include "mSceneManager.h"
#include "mSkillCurve.h"

namespace m
{
    SkillOrb::SkillOrb(eSkillType type, Vector3 iniPos, float speed, eLayerType layerType)
        : SkillStraight(type, iniPos, speed)
        , mAccSkillTime(0.f)
        , mSectionActiveCount(0)
        , mAddCircleDegree(90.f)
        , mAccDegree(0)
        , iLock(0)
        , bCameraUpdate(false)
        , bFireCircle(false)
        , mMiType(layerType)   
    {
        for(float i = 0.0f ; i <= 2.f ;)
        {
            SkillStraight* ss = new SkillStraight(eSkillType::iceBolt, iniPos, 400.f, true);
            ss->SetState(GameObject::eState::NoRenderUpdate);
            sectionSkills.push_back(ss);
            i += 0.1f;
        }
        for(int i = 0 ; i < 16; ++i)
        {
            SkillCurve* sc = new SkillCurve(eSkillType::iceBolt, iniPos, 600.f);
            sc->SetState(GameObject::eState::NoRenderNoUpdate);
            sectionSkills2.push_back(sc);
        }
        StraightScript* ss = GET_COMP(this, StraightScript);
        ss->SetNoHit(true);
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
            for (SkillStraight* ss : sectionSkills)
            {
                ss->SetCamera(GetCamera());
                SceneManager::GetActiveScene()->AddGameObject(mMiType, ss);
            }
            for (SkillCurve* ss : sectionSkills2)
            {
                ss->SetCamera(GetCamera());
                SceneManager::GetActiveScene()->AddGameObject(mMiType, ss);
            }
            bCameraUpdate = true;
        }
        mAccSkillTime += Time::fDeltaTime();
        if(mSectionActiveCount < sectionSkills.size()
            &&
            math::areAlmostEqual(mAccSkillTime, 0.1f, 0.05))
        {
            
            fireThreeWayDegreeSkill(sectionSkills[mSectionActiveCount]);
            sectionSkills[mSectionActiveCount]->SkillFire();
            sectionSkills[mSectionActiveCount]->SetState(eState::RenderUpdate);
            

            mAccSkillTime = 0.f;
            ++mSectionActiveCount;
        }
        if(mSectionActiveCount >= sectionSkills.size())
        {
            if (!bFireCircle)
                fireCircle();

            SetState(Delete);
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
    void SkillOrb::fireThreeWayDegreeSkill(SkillStraight* skill)
    {
        //if (nullptr == skill) return;
        //if (skill->GetSkillCrash()) return;

        if (iLock >= 3)
        {
            iLock = 0;
        }
        if(iNumUse == 3)
        {
            for (int i = 0; i < 3; ++i)iNDuplicates[i] = 0;
            //for (int i = 0; i < 3; ++i)iMDuplicates[i] = 0;
            iNumUse = 0;
        }
        if(iLock == 0)
        {
            ++iNumUse;
            int n = 0;
            while (iNDuplicates[n] != 0) n = rand() % 3;
            iNDuplicates[n] = 1;

            mAddCircleDegree = iAddDegrees[n];

            //n = 0;
            //while (iMDuplicates[n] != 0) n = rand() % 3;
            //iMDuplicates[n] = 1;

            mAccDegree = iInitDegrees[n];
        }
        ++iLock;

        SET_POS_VEC(skill, GET_POS(this));
        
        float theta = DegreeToRadian((float)mAccDegree);
        mAccDegree += mAddCircleDegree;

        Vector3 pos = GET_POS(this);
        skill->SetInitializePosition(pos);

        pos.x += cosf(theta); 
        pos.y += sinf(theta);

        skill->SetDestPosition(pos);
    }
    void SkillOrb::fireCircle()
    {
        bFireCircle = true;
        for(float i = 0; i < sectionSkills2.size(); ++i )
        {
            if (nullptr == sectionSkills2[i]) continue;
            if (sectionSkills2[i]->GetSkillCrash()) continue;

            Vector3 pos = GET_POS(this);
            SET_POS_VEC(sectionSkills2[i], pos);
            sectionSkills2[i]->SetInitializePosition(pos);
            
            float degree = 360 / sectionSkills2.size() * (i + 1);
            float theta = DegreeToRadian(degree + 90.f);

            pos.x += sinf(theta);
            pos.y += cosf(theta);

            sectionSkills2[i]->SetAddCurve(20.f);
            sectionSkills2[i]->SetDestPosition(pos);
            sectionSkills2[i]->SkillFire();
            sectionSkills2[i]->SetState(RenderUpdate);

            //SceneManager::GetActiveScene()->AddGameObject(mMiType, sectionSkills2[i]);
        }
    }
}
