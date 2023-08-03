#pragma once
#include "mTileManager.h"

#include "../Engine/mSkill.h"
#include "../Engine/mMoveAbleObject.h"

namespace m
{
	class SkillManager
	{
	public:
		static void AddSkill();
		static MoveAbleObject* GetSkill();

		static std::vector<MoveAbleObject*> skills;
	private:
	};
}

