#include "mPotionScript.h"

#include "../engine_source/mAudioSource.h"

#include "mPlayerManager.h"
#include "mPlayer.h"
#include "mInvenItem.h"

namespace m
{
    PotionScript::PotionScript()
        : mOwnerState()
        , mOwnerItem()
    {
    }

    PotionScript::~PotionScript()
    {
    }

    void PotionScript::Initialize()
    {
        ItemScript::Initialize();
    }

    void PotionScript::Update()
    {
        ItemScript::Update();
        if(static_cast<InvenItem*>(GetOwner())->GetDoItemFunction())
        {
            AudioSource* as = GET_COMP(GetOwner(), AudioSource);
            as->PlayOnce(0, buttonSoundPaths[(int)eUISoundType::PotionUse], false, false, true);

            if (mOwnerItem == eItem::hpPotion1)
                PlayerManager::player->RestoreHp(10);

            if (mOwnerItem == eItem::mpPotion1)
                PlayerManager::player->RestoreMp(10);

            GetOwner()->SetState(GameObject::eState::Delete);
        }
    }

    void PotionScript::LateUpdate()
    {
        ItemScript::LateUpdate();
    }

    void PotionScript::Render()
    {
        ItemScript::Render();
    }
}
