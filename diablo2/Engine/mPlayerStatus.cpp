#include "mPlayerStatus.h"

#include "SkillLookUpTables.h"
#include "mPlayerManager.h"

namespace m
{
    int PlayerStatus::level = 1;
    int PlayerStatus::experiance = 0;
    int PlayerStatus::nextLevelUpexperiance = 500;
    int PlayerStatus::maxDamage = 2;
    int PlayerStatus::minDamage = 1;

    int PlayerStatus::strength = 10;
    int PlayerStatus::dexterity = 25;
    int PlayerStatus::vitality = 10;
    int PlayerStatus::energy = 35;

    int PlayerStatus::statusPoint = 0;

    int PlayerStatus::defense = 6;
    int PlayerStatus::stanmina = 74;
    int PlayerStatus::life = 40;
    int PlayerStatus::mana = 35;

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
    }

    void PlayerStatus::UpStrength()
    {
        ++strength;
    }

    void PlayerStatus::UpDexterity()
    {
        ++dexterity;
    }

    void PlayerStatus::UpVitality()
    {
        ++vitality;
    }

    void PlayerStatus::UpEnergy()
    {
        ++energy;
    }

    void PlayerStatus::GetDamage()
    {
        
    }

    void PlayerStatus::StatusInteraction()
    {
        defense = (dexterity / 5) + 1;
        stanmina = vitality + 64;
        life = vitality * 2;
        mana = energy * 2;
        minDamage;
        maxDamage;
    }
}
