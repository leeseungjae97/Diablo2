#include "mMonsterHand.h"

#include "MoveAbleObjectAnimLookUpTables.h"
#include "mGameObject.h"
#include "mMonster.h"
#include "SkillAnimLookUpTables.h"

#include "../engine_source/mSceneManager.h"

namespace m
{
	MonsterHand::MonsterHand(Monster* parent, eMonsterType type, bool fh)
		: Hand(parent, fh)
		, mMonsterType(type)
		, mOwner(parent)
	{
		//Transform* fr = GET_COMP(this, Transform);
		//fr->SetParent(GET_COMP(parent, Transform));

		ADD_COMP(this, Animator);
		ADD_COMP(this, MeshRenderer);

		SET_MESH(this, L"RectMesh");
		SET_MATERIAL(this, L"AnimationMaterial");

		//mHandScript = ADD_COMP(this, HandScript);
		mHandScript = AddComponent<HandScript>(
			monsterHandSizes[(int)mMonsterType]
			, monsterOffsets[(int)mMonsterType]
			, monsterHandLength[(int)mMonsterType]
			, (int)MDDiablo::eAnimationType::End
			, fh ? monsterRHandNames[(int)mMonsterType] : monsterLHandNames[(int)mMonsterType]
			);
		fh ? mHandScript->RightHand() : mHandScript->LeftHand();

		SET_SCALE_XYZ(this,
			100.f, 100.f, 1.f);
	}

	MonsterHand::~MonsterHand()
	{
	}

	void MonsterHand::Update()
	{
		Hand::Update();
		if (mOwner->GetState() == Delete) {
			SetState(Delete);
			return;
		}

		Vector3 pos = GET_POS(mOwner);
		
		int direction = mHandScript->GetHandDirection();

		if(mHandScript->GetRightHand())
		{
			if (direction == (int)ePathSixteenDirection::Left
				|| direction == (int)ePathSixteenDirection::LeftUp1
				|| direction == (int)ePathSixteenDirection::RightUp1
				|| direction == (int)ePathSixteenDirection::Up)
			{
				if (pos.z == 1.f) pos.z += 0.00001f;
				//SceneManager::GetActiveScene()->GetLayer(eLayerType::Monster)->ChangeLayerIndexGameObject(this, mOwner);
			}
			else
			{
				if (pos.z > 1.f) pos.z -= 0.00001f;;
			}
		}
		


		SET_POS_VEC(this, pos);
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
