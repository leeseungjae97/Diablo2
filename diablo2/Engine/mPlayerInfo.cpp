#include "mPlayerInfo.h"
namespace m
{
	int PlayerInfo::learnedColdSkill[(int)eColdSkillType::END]= {1,0,1};
	int PlayerInfo::learnedFireSkill[(int)eFireSkillType::END]= {};
	int PlayerInfo::learnedLightSkill[(int)eLightningSkillType::END]= {};
	int PlayerInfo::skillPoint = 10;
}