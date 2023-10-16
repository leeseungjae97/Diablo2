#include "mPlayerStatus.h"

#include "../engine_source/mSoundManager.h"
#include "../engine_source/SkillLookUpTables.h"

#include "mPlayer.h"
#include "mPlayerManager.h"

namespace m
{
    int PlayerStatus::level = 1;
    int PlayerStatus::experiance = 0;
    int PlayerStatus::nextLevelUpexperiance = 500;
    int PlayerStatus::damage = 10;

    int PlayerStatus::strength = 10;
    int PlayerStatus::dexterity = 25;
    int PlayerStatus::vitality = 10;
    int PlayerStatus::energy = 35;

    int PlayerStatus::statusPoint = 100;

    int PlayerStatus::defense = 6;
    int PlayerStatus::stanmina = 74;
    int PlayerStatus::life = 40;
    int PlayerStatus::mana = 35;

    std::wstring PlayerStatus::playerName = L"플레이어";
    std::wstring PlayerStatus::className = L"소서리스";

    void PlayerStatus::Initialize()
    {

    }

    void PlayerStatus::Update()
    {
        if(experiance >= nextLevelUpexperiance)
        {
            LevelUp();
        }
    }

    void PlayerStatus::LateUpdate()
    {
    }

    void PlayerStatus::LevelUp()
    {
        ++level;
        nextLevelUpexperiance *= 10;
        statusPoint += 10;
        PlayerManager::skillPoint += 10;
    }

    void PlayerStatus::UpStrength()
    {
        if (statusPoint == 0) return;

        --statusPoint;
        ++strength;
        StatusInteraction();
        SoundManager::ExternUISound(eUISoundType::PointUse, false, 30.f);
        SoundManager::ResetPlayed(SoundManager::eExternAudioType::UI);
    }

    void PlayerStatus::UpDexterity()
    {
        if (statusPoint == 0) return;

        --statusPoint;
        ++dexterity;
        StatusInteraction();
        SoundManager::ExternUISound(eUISoundType::PointUse, false, 30.f);
        SoundManager::ResetPlayed(SoundManager::eExternAudioType::UI);
    }

    void PlayerStatus::UpVitality()
    {
        if (statusPoint == 0) return;

        --statusPoint;
        ++vitality;
        StatusInteraction();
        SoundManager::ExternUISound(eUISoundType::PointUse, false, 30.f);
        SoundManager::ResetPlayed(SoundManager::eExternAudioType::UI);
    }

    void PlayerStatus::UpEnergy()
    {
        if (statusPoint == 0) return;

        --statusPoint;
        ++energy;
        StatusInteraction();
        SoundManager::ExternUISound(eUISoundType::PointUse, false, 30.f);
        SoundManager::ResetPlayed(SoundManager::eExternAudioType::UI);
    }

    void PlayerStatus::GetDamage()
    {
        
    }

    void PlayerStatus::StatusInteraction()
    {
        defense = (dexterity / 5) + 1;
        stanmina = vitality + 64;
        life = 20 + vitality * 2;
        mana = energy * 2 - 35;

        PlayerManager::hpCapacity = static_cast<float>(life);
        PlayerManager::mpCapacity = static_cast<float>(mana);
        if (PlayerManager::player)
        {
            //UIUV update
            PlayerManager::player->RestoreHp(0);
            PlayerManager::player->RestoreMp(0);
        }
    }
}
