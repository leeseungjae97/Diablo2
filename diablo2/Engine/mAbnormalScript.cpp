#include "mAbnormalScript.h"

#include "mPlayer.h"
#include "mPlayerManager.h"
#include "mPlayerScript.h"
#include "mSkill.h"

namespace m
{
    AbnormalScript::AbnormalScript()
        : mAbnormalCollider(nullptr)
    {
    }

    AbnormalScript::~AbnormalScript()
    {
    }

    void AbnormalScript::Initialize()
    {
        Script::Initialize();
    }

    void AbnormalScript::Update()
    {
        Script::Update();

        abnormalAttack();
    }
    void AbnormalScript::abnormalAttack()
    {
        eSkillType type = dynamic_cast<Skill*>(GetOwner())->GetSkillType();
        eLayerType mLayerType = dynamic_cast<Skill*>(GetOwner())->GetSkillOwnerLayer();
        eSkillCrashType sct= skillCrashTypes[(UINT)type];
        eCrashType ct = crashFunction[(int)sct];

        if(mLayerType == eLayerType::PlayerSkill)
        {
            
        }else
        {
            if (mAbnormalCollider->SearchObjectGameObjectId(PlayerManager::player->GetGameObjectId()))
            {
                if (ct == eCrashType::Stun)
                {
                    //PlayerScript* ps = PlayerManager::player->GetComponent<PlayerScript>();
                    
                    PlayerScript* ps = PlayerManager::player->GetComponent<PlayerScript>();

                    if (ps->GetStun()) return;

                    ps->SetStun(0.5f);
                    SET_SCALE_XYZ(ps->GetHSO()
                        , crashSizes[(int)sct].x
                        , crashSizes[(int)sct].y
                        , 1.f
                    );
                    OverlayEffectSkillScript* mOESS = ps->GetHSO()->GetComponent<OverlayEffectSkillScript>();
                    mOESS->SetSkillType(type);
                    ps->GetHSO()->ActiveOverlay();
                    //ps->GetHSO()->SetLoopSecond(0.5f);
                }
            }
        }
        

       
    }
    void AbnormalScript::LateUpdate()
    {
        Script::LateUpdate();
    }

    void AbnormalScript::Render()
    {
        Script::Render();
    }
}
