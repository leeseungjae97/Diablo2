#include "mSkillFallExplosion.h"

#include "../engine_source/mSceneManager.h"

#include "mSkillOverlay.h"
#include "mSkillIndicator.h"

namespace m
{
    SkillFallExplosion::SkillFallExplosion(eSkillType type, Vector3 iniPos, eLayerType layerType)
        : Skill(type, iniPos)
        , mIndicator(nullptr)
    {
        SET_MESH(this, L"PointMesh");
        SET_MATERIAL(this, L"noneRect");
        Vector3 initYpos = iniPos;
        initYpos.y += 1000.f;
        
        SkillFall* body = new SkillFall(type, initYpos, 1000.f, true);
        body->SetSpeed(1000.f / 2.f);
        SceneManager::GetActiveScene()->AddGameObject(layerType, body);
        skills.push_back(body);

        if(type == eSkillType::meteor)
        {
            Vector3 meteorHeadPos = Vector3(
                initYpos.x + 10.f
                , initYpos.y - 29.f
                , iniPos.z);
            SkillFall* acc = new SkillFall(type, meteorHeadPos, 1000.f, true, true, eAccessorySkillType::MeteorHead);
            acc->SetSpeed(1000.f / 2.f);
            skills.push_back(acc);
            SceneManager::GetActiveScene()->AddGameObject(layerType, acc);

            mIndicator = new SkillIndicator(iniPos, eIndicatorType::MeteorTargetIndicator);
            mIndicator->SetOwnerSkill(body);
            SceneManager::GetActiveScene()->AddGameObject(layerType, mIndicator);
        }
        
        //iniPos;
        //int randX = rand() % (int)randFireArange.x;
        //int randY = rand() % (int)randFireArange.y;
    }

    SkillFallExplosion::~SkillFallExplosion()
    {
    }
    void SkillFallExplosion::Initialize()
    {
        Skill::Initialize();
    }
    void SkillFallExplosion::Update()
    {
        Skill::Update();
        if(bSkillFire)
        {
            updateSkills();
            bSkillFire = false;
        }
        
    }

    void SkillFallExplosion::LateUpdate()
    {
        Skill::LateUpdate();
    }

    void SkillFallExplosion::Render()
    {
        Skill::Render();
    }
    bool SkillFallExplosion::ReturnCrash()
    {
        return skills[0]->GetSkillCrash();
    }
    void SkillFallExplosion::updateSkills()
    {
        if(mIndicator)
            mIndicator->SetCamera(GetCamera());

        for(int i = 0 ; i < skills.size() ; ++i)
        {
            skills[i]->SetCamera(GetCamera());
            skills[i]->SkillFire();
        }
    }

    
}
