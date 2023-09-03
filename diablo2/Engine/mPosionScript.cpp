#include "mPosionScript.h"

#include "mPlayerInfo.h"
#include "mPlayer.h"
#include "mInvenItem.h"

namespace m
{
    PosionScript::PosionScript()
        : mOwnerState()
        , mOwnerItem()
    {
    }

    PosionScript::~PosionScript()
    {
    }

    void PosionScript::Initialize()
    {
        ItemScript::Initialize();
    }

    void PosionScript::Update()
    {
        ItemScript::Update();
        if(static_cast<InvenItem*>(GetOwner())->GetDoItemFunction())
        {
            if (mOwnerItem == eItem::hpPosion1)
                PlayerInfo::player->RestoreHp(10);

            if (mOwnerItem == eItem::mpPosion1)
                PlayerInfo::player->RestoreMp(10);

            GetOwner()->SetState(GameObject::eState::Delete);
        }
    }

    void PosionScript::LateUpdate()
    {
        ItemScript::LateUpdate();
    }

    void PosionScript::Render()
    {
        ItemScript::Render();
    }
}
