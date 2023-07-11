#pragma once
#include "..\engine_source\ItemLookUpTables.h"
#include "..\engine_source\SkillLookUpTables.h"
namespace m
{
	class PlayerInfo
	{
	public:
		static int skillPoint;

		static int learnedColdSkill[(int)eColdSkillType::END];
		static int learnedFireSkill[(int)eFireSkillType::END];
		static int learnedLightSkill[(int)eLightningSkillType::END];
	private:
		
	};
}

