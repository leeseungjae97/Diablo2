#pragma once
#include "_Engine.h"

namespace m
{
	class PlayerStatus
	{
	public:
		static void Initialize();
		static void Update();
		static void LateUpdate();

		static void StatusInteraction();
		static void GetDamage();

		static void LevelUp();
		static void UpStrength();
		static void UpDexterity();
		static void UpVitality();
		static void UpEnergy();
		
		static std::wstring playerName;
		static std::wstring className;
		static int level;
		static int experiance;
		static int nextLevelUpexperiance;

		static int strength;
		static int dexterity;
		static int vitality;
		static int energy;

		static int statusPoint;

		static int defense;
		static int stanmina;
		static int life;
		static int mana;

		static int maxDamage;
		static int minDamage;
	};
}


