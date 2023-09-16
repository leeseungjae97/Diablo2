#include "mSkillBuff.h"

#include "mTeleportScript.h"
#include "mBuffScript.h"

namespace m
{
    SkillBuff::SkillBuff(GameObject* mOwner, int index, eSkillType type)
        : SkillOverlay(index, skillCastTypes[(int)type])
    {
        SetActiveOwner(mOwner);
        if(type == eSkillType::teleport)
        {
            TeleportScript* ts =ADD_COMP(this, TeleportScript);
            ts->SetTeleportOwner(mOwner);
        }
        else
        {
            BuffScript* bs = ADD_COMP(this, BuffScript);
        }
    }

    SkillBuff::~SkillBuff()
    {
    }

    void SkillBuff::Initialize()
    {
        SkillOverlay::Initialize();
    }

    void SkillBuff::Update()
    {
        SkillOverlay::Update();
    }

    void SkillBuff::LateUpdate()
    {
        SkillOverlay::LateUpdate();
    }

    void SkillBuff::Render()
    {
        SkillOverlay::Render();
    }

    void SkillBuff::ActiveOverlay()
    {
        SkillOverlay::ActiveOverlay();
    }
}