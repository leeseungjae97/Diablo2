#include "mSkillManager.h"

#include "../Engine/mSkillFollower.h"

namespace m
{
    std::vector<Skill*> SkillManager::skills;

    void SkillManager::Update()
    {

    }
    void SkillManager::AddSkill(Skill* skill)
    {
        eLayerType layerType = skill->GetLayerType();

        //if (layerType == eLayerType::AdapterSkill
        //    || layerType == eLayerType::PlayerAura
        //    || layerType == eLayerType::MonsterAura
        //    || layerType == eLayerType::MonsterOverlay
        //    || layerType == eLayerType::PlayerOverlay
        //    )
        //    return;

        eSkillFunctionType type = skillFunctionTypes[(int)skill->GetSkillType()];
        if (type == eSkillFunctionType::MultiFall
            || type == eSkillFunctionType::Fall
            || type == eSkillFunctionType::FallExplosion)
                return;

        skills.push_back(skill);
    }
    void SkillManager::EraseSkill(int skillId)
    {
        std::vector<Skill*>::iterator iter = skills.begin();

        while(iter != skills.end())
        {
            if((*iter)->GetSkillId() == skillId)
            {
                iter = skills.erase(iter);
            }else
            {
                ++iter;
            }
        }
    }
    void SkillManager::AllSkillCrash()
    {
        for (Skill* skill : skills)
        {
            //eSkillType type = skill->GetSkillType();
            //eSkillCrashType skillCrashType = skillCrashTypes[(int)type];
            //eCrashType crashType = crashFunction[(int)skillCrashType];
            if(skill)
                skill->SetSkillCrash(true);
        }
    }
    void SkillManager::SkillCrash(int skillId)
    {
        for (Skill* skill : skills)
        {
            if (skill->GetSkillId() == skillId)
            {
                //eSkillType type = skill->GetSkillType();
                //eSkillCrashType skillCrashType =skillCrashTypes[(int)type];
                //eCrashType crashType = crashFunction[(int)skillCrashType];
                //if (crashType != eCrashType::Collide)
                //{
                //    if(dynamic_cast<SkillFollower*>(skill))
                //    {
                //        skill->SetSkillCrash(true);
                //    }else
                //    {
                //        skill->SetSkillCrash(true);
                //        //skill->SetState(GameObject::eState::Delete);
                //    }
                //}
                //else
                //{
                //    skill->SetSkillCrash(true);
                //}

                if(skill)
                    skill->SetSkillCrash(true);
            }
        }
    }

    Skill* SkillManager::GetSkill(int skillId)
    {
        for(Skill* skill : skills)
        {
            if (skill->GetSkillId() == skillId) return skill;
        }
        return nullptr;
    }
}
