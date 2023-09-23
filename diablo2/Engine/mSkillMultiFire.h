#pragma once
#include "mSkill.h"

#include "mSkillFall.h"
#include "mSkillStraight.h"
namespace m
{
	class SkillMultiFire :
		public Skill
	{
	public:
		enum class eFireType
		{
			Linear,
			FixedLinear,
			RandomLinear,
			RadialRandomStraight,
			RandomFall,
			Radial,
			Circle,
			END,
		};


        
		SkillMultiFire(Vector3 iniPos
                       , eSkillType type
                       , int count = 2
                       , int bFireType = (int)eFireType::END
                       , eLayerType layerType = eLayerType::Skill
                       , Vector2 randFireRange = Vector2::Zero
                       , Camera* camera = nullptr
                       , float skillGenTime = 0.05f
                       , bool addSkill = false);
		virtual ~SkillMultiFire();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:
		SkillStraight* makeRadialRandomStraight(float randomY, Vector3 vector3, eSkillType type, Camera* camera
			, eLayerType layerType, float initDegree, float addDegree);
		Skill* makeRandomLinear(float randomY, Vector3 vector3, eSkillType type, Camera* camera, eLayerType layerType);
		SkillStraight* makeCircleStraights(Vector3 vector3, eSkillType type, float addDegree);
		SkillFall* makeRandomFall(Vector2 vector2, Vector3 startPos, eSkillType type, std::default_random_engine generator);
		SkillStraight* makeRadialStraight(Vector3 startPos, eSkillType type
			, float initDegree, float addDegree);

	private:
		std::vector<Skill*> skills;
		std::vector<float> mSkillFireTimes;
		eFireType mFireType;
		int curIndex;
		int mCount;
		float mAccTime;
		bool bFirstUpdate;
	};
}

