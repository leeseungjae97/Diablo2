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
        static void EraseSkill(int skillId);
		static void AllSkillCrash();
		static void SkillCrash(int skillId);
        static Skill* GetSkill(int skillId);

		static std::vector<Skill*> skills;
	private:
	};
}

