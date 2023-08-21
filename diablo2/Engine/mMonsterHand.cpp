#include "mMonsterHand.h"

#include "MoveAbleObjectAnimLookUpTables.h"
#include "mGameObject.h"
#include "mMonster.h"

namespace m
{
	MonsterHand::MonsterHand(Monster* parent, eMonsterType type, bool fh)
		: Hand(parent, fh)
		, mMonsterType(type)
		, mOwner(parent)
	{
		//mHandScript = ADD_COMP(this, HandScript);

		HandScript* hs = AddComponent<HandScript>(
			monsterHandSizes[(int)mMonsterType]
			, monsterHandLength[(int)mMonsterType]
			, (int)MDDiablo::eAnimationType::End
			, fh ? monsterRHandNames[(int)mMonsterType] : monsterLHandNames[(int)mMonsterType]);
		//mHandScript->SetOwner(parent);
		mHandScript->SetHandSizes(monsterHandSizes[(int)mMonsterType]);
		mHandScript->SetHandLengths(monsterHandLength[(int)mMonsterType]);
		mHandScript->SetAnimationLength((int)MDDiablo::eAnimationType::End);
	}

	MonsterHand::~MonsterHand()
	{
	}

	void MonsterHand::Update()
	{
		Hand::Update();
	}

	void MonsterHand::LateUpdate()
	{
		Hand::LateUpdate();
	}

	void MonsterHand::Render()
	{
		Hand::Render();
	}

	void MonsterHand::Initialize()
	{
		Hand::Initialize();
	}

	void MonsterHand::SetDirection(int direction)
	{
		mHandScript->SetHandDirection(direction);
	}

	void MonsterHand::SetAniType(int aniType)
	{
		mHandScript->SetHandAnimation(aniType);
	}
}
