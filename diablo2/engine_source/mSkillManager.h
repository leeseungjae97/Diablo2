#pragma once

#include "../Engine/mSkill.h"
#include "../Engine/mMoveAbleObject.h"

namespace m
{
	class SkillManager
	{
	public:
		static void Update();
		static void AddSkill(Skill* skill);
        static void EraseSkill(UINT skillId);
		static void AllSkillCrash();
		static void SkillCrash(UINT skillId);
        static Skill* GetSkill(UINT skillId);

		static std::vector<Skill*> skills;
	private:
	};
}

