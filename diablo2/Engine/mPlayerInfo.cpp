#include "mPlayerInfo.h"
namespace m
{
	int PlayerInfo::learnedSkill[3][10]= {};
	int PlayerInfo::skillPoint = 0;
	void PlayerInfo::Initialize()
	{
		skillPoint = 100;
	}
}