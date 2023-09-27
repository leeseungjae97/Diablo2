#pragma once

#include "_Engine.h"
#include "../engine_source/SkillLookUpTables.h"

namespace m
{
	class Player;
	class InvenItem;
	class PlayerManager
	{
	public:
		static int skillPoint;
		static int money;
		static float hp;
		static float hpCapacity;
		static float hpPercent;
		static float mp;
		static float mpCapacity;
		static float mpPercent;
		static int learnedSkill[3][10];

		static Player* player;

		static void CalHpPercent();
		static void CalMpPercent();
		static void Initialize();

		static eSkillType GetSkill(int num);
		static void SetSkill(int num, eSkillType type);

		static eSkillType SetColdSkillType(eColdSkillType type);
		static eSkillType SetFireSkillType(eFireSkillType type);
		static eSkillType SetLightningSkillType(eLightningSkillType type);
        static bool BuyItem(int cost);

    private:

		static eSkillType skillTypes[2];
		
	};
}

