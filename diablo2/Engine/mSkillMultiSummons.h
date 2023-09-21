#pragma once
#include "mSkill.h"
#include "SummonsLookUpTables.h"

namespace m
{
    class SkillSummons;

    class SkillMultiSummons
        : public GameObject
	{
	public:
		SkillMultiSummons(eSummonsType type, Vector3 initPos, Camera* camera
			, float summonTime, int count, eLayerType layerType);
		virtual ~SkillMultiSummons();

		virtual void Initialize() override;
		virtual void Update() override;
	private:
		std::vector<SkillSummons*> skills;
	};
}

