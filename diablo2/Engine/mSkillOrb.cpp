#include "mSkillOrb.h"
namespace m
{
    SkillOrb::SkillOrb(eSkillType type, Vector3 iniPos, float speed)
        : SkillStraight(type, iniPos, speed)
    {
        SetLimitDistance(400.f);

        for(int i = 0 ; i < 3; ++i)
        {
            
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
    }

    void SkillOrb::LateUpdate()
    {
        SkillStraight::LateUpdate();
    }

    void SkillOrb::Render()
    {
        SkillStraight::Render();
    }
}
