#include "mSkillCurve.h"
namespace m
{
    SkillCurve::SkillCurve(eSkillType type, Vector3 iniPos, float speed)
        : SkillStraight(type, iniPos, speed)
    {
    }

    SkillCurve::~SkillCurve()
    {
    }

    void SkillCurve::Initialize()
    {
        SkillStraight::Initialize();
    }

    void SkillCurve::Update()
    {
        SkillStraight::Update();
    }

    void SkillCurve::LateUpdate()
    {
        SkillStraight::LateUpdate();
    }

    void SkillCurve::Render()
    {
        SkillStraight::Render();
    }

    void SkillCurve::Hit(int damage)
    {
        SkillStraight::Hit(damage);
    }
}
