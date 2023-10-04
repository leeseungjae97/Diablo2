#include "mSkillManager.h"
namespace m
{
    std::vector<Skill*> SkillManager::skills;

    void SkillManager::Update()
    {

    }
    void SkillManager::AddSkill(Skill* skill)
    {
        eSkillFunctionType type = skillFunctionTypes[(int)skill->GetSkillType()];
        if (type == eSkillFunctionType::MultiFall
            || type == eSkillFunctionType::Fall
            || type == eSkillFunctionType::FallExplosion)
                return;

        skills.push_back(skill);
    }
    void SkillManager::EraseSkill(UINT skillId)
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

    void SkillManager::SkillCrash(UINT skillId)
    {
        for (Skill* skill : skills)
        {
            if (skill->GetSkillId() == skillId)
            {
                //skill->SetState(GameObject::eState::Delete);
                eSkillType type = skill->GetSkillType();
                eSkillCrashType skillCrashType =skillCrashTypes[(int)type];
                eCrashType crashType = crashFunction[(int)skillCrashType];
                if (crashType != eCrashType::Collide)
                    skill->SetState(GameObject::eState::NoRenderNoUpdate);
                else 
                    skill->SetSkillCrash(true);
            }
        }
    }

    Skill* SkillManager::GetSkill(UINT skillId)
    {
        for(Skill* skill : skills)
        {
            if (skill->GetSkillId() == skillId) return skill;
        }
        return nullptr;
    }
}
