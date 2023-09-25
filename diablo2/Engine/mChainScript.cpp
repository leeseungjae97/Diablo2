#include "mChainScript.h"

#include "mMonster.h"
#include "mMoveAbleObject.h"

namespace m
{
	ChainScript::ChainScript(MoveAbleObject* target, MoveAbleObject* prevTarget, int chainCount)
		: mTarget(target)
		, mPrevTarget(prevTarget)
		, iChainCount(chainCount)
	{

	}

	ChainScript::~ChainScript()
	{
	}

	void ChainScript::Initialize()
	{
		Script::Initialize();
	}

	void ChainScript::Update()
	{
		Script::Update();
		UpdateCollideredMonster();
	}

	void ChainScript::LateUpdate()
	{
		Script::LateUpdate();
	}

	void ChainScript::Render()
	{
		Script::Render();
	}

	void ChainScript::UpdateCollideredMonster()
	{
	
	}
}
