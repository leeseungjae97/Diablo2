#include "mSkillAbnormal.h"

#include "mAbnormalScript.h"

namespace m
{
    SkillAbnormal::SkillAbnormal(eSkillType type, Vector3 initPos)
        : Skill(type, initPos)
    {
        SET_MESH(this, L"PointMesh");
        SET_MATERIAL(this, L"noneRect");

        mAS = ADD_COMP(this, AbnormalScript);
    }

    SkillAbnormal::~SkillAbnormal()
    {
    }

    void SkillAbnormal::Initialize()
    {
        Skill::Initialize();
    }

    void SkillAbnormal::Update()
    {
        Skill::Update();
        if(mAS)
        {
            if (mAS->GetStatusAbnormal()) SetState(Delete);
        }
    }

    void SkillAbnormal::LateUpdate()
    {
        Skill::LateUpdate();
    }

    void SkillAbnormal::Render()
    {
        Skill::Render();
    }

    void SkillAbnormal::SetAbnormalCollider(Collider2D* col)
    {
        if (mAS)
            mAS->SetAbnormalCollider(col);
    }
}
