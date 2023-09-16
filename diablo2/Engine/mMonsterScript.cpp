#include "mMonsterScript.h"

#include "../engine_source/mSceneManager.h"
#include "../engine_source/mMaterial.h"
#include "../engine_source/mAnimator.h"
#include "../engine_source/mAnimation.h"
#include "../engine_source/mTime.h"

#include "mPlayer.h"
#include "mMonster.h"
#include "mPlayerManager.h"
#include "mSkillAbnormal.h"
#include "mSkillBuff.h"
#include "mSkillFallExplosion.h"
#include "mSkillOverlay.h"
#include "mSkillMultiFire.h"
#include "mSkillOrb.h"
#include "mAura.h"

namespace m
{
	template <typename T>
	MonsterScript<T>::MonsterScript()
		: mAnimator(nullptr)
		, mSkill(nullptr)
		, mMonster(nullptr)
		, mClass(eMonsterClass::Normal)
		, bFire(false)
		, fAttackDelay(0.f)
		, mDirection(0)
		, iCurSkillIndex(0)
		, skillMake(false)
		, mLeftHand(nullptr)
		, mRightHand(nullptr)
	    , mAura(nullptr)

	{
		curMonsterData = T{};
		mClass = curMonsterData.mClass;
	}
	template <typename T>
	MonsterScript<T>::~MonsterScript()
	{
	}
	template <typename T>
	void MonsterScript<T>::Initialize()
	{
		mAnimator = GET_COMP(GetOwner(), Animator);
		dynamic_cast<MoveAbleObject*>(GetOwner())->SetMadePath(curMonsterData.bPathImage);
		dynamic_cast<MoveAbleObject*>(GetOwner())->SetSixteenDirection(false);
		Scene* curScene = SceneManager::GetActiveScene();
		Monster* monster = dynamic_cast<Monster*>(GetOwner());

		if(curMonsterData.passiveAura != eAuraType::End)
		{
			mAura = new Aura(GetOwner(), curMonsterData.passiveAura, curMonsterData.auraOffSet);
			curScene->AddGameObject(eLayerType::Aura, mAura);
		}

		//mLeftHand = new MonsterHand(monster, curMonsterData.mMonsterType, false);
		if (curMonsterData.bHandAnim)
		{
			mRightHand = new MonsterHand(monster, curMonsterData.mMonsterType, true);

			//mLeftHand->SetCamera(GetOwner()->GetCamera());
			mRightHand->SetCamera(GetOwner()->GetCamera());
			Animator* rightAnimator = GET_COMP(mRightHand, Animator);
			rightAnimator->SetSyncAnimator(mAnimator);
			rightAnimator->Sync();
			curScene->AddGameObject(eLayerType::Monster, mRightHand);
		}
		//curScene->AddGameObject(eLayerType::Monster, mLeftHand);

		if (curMonsterData.bPathImage)
		{
			mPlusDirections = pathPlusEightDirections;
			mMinusDirections = pathMinusEightDirections;
			animStrings = pathSixteenDirectionString;
		}
		else
		{
			mPlusDirections = plusEightDirections;
			mMinusDirections = minusEightDirections;
			animStrings = sixteenDirectionString;
		}

		int m = 0;
		for (int i = 0; i < (UINT)T::eAnimationType::End; ++i)
		{
			if (curMonsterData.textureString[i] == L"") continue;

			SHARED_MAT mat = RESOURCE_FIND(Material, curMonsterData.textureString[i]);

			for (int j = 0; j < 8; ++j)
			{
				if (!curMonsterData.bPathImage) m = eEightDirection[j];
				else m = j;

				mAnimator->Create(
					curMonsterData.animationString[i] + animStrings[m]
					, mat->GetTexture()
					, Vector2(0.0f, curMonsterData.animationSizes[i].y * j)
					, curMonsterData.animationSizes[i]
					, curMonsterData.animationLength[i]
					, curMonsterData.animationOffset[i]
					, curMonsterData.animationDuration[i]
				);
				if (i == (UINT)T::eAnimationType::Natural)
				{
					mAnimator->StartEvent(curMonsterData.animationString[i] + animStrings[m])
						= [this]()
					{
						mAnimator->SetAnimationStartIndex(0);
					};
				}
				if (i == (UINT)T::eAnimationType::Attack1)
				{
					mAnimator->StartEvent(curMonsterData.animationString[i] + animStrings[m])
						= [this]()
					{
						AnimationStart(GameObject::eBattleState::Attack);
						mAnimator->SetAnimationProgressIndex(curMonsterData.animProgressStartIndex[(UINT)T::eAnimationType::Attack1]);
					};
					mAnimator->EndEvent(curMonsterData.animationString[i] + animStrings[m])
						= [this]()
					{
						//fAttackDelay = 0.f;
						AnimationComplete(GameObject::eBattleState::Idle);
						mAnimator->SetAnimationProgressIndex(0);
					};
					mAnimator->ProgressEvent(curMonsterData.animationString[i] + animStrings[m])
						= [this]() { AttackProgress(); };
				}
				if (i == (UINT)T::eAnimationType::Hit)
				{
					mAnimator->StartEvent(curMonsterData.animationString[i] + animStrings[m])
						= [this]()
					{
						fAttackDelay = 0.f;
						Hit(true, GameObject::eBattleState::Hit);
						//mAnimator->SetAnimationStartIndex(curMonsterData.animStartIndex[(UINT)T::eAnimationType::Hit]);
					};
					mAnimator->EndEvent(curMonsterData.animationString[i] + animStrings[m])
						= [this]() { Hit(false, GameObject::eBattleState::Idle); };
				}
				if (i == (UINT)T::eAnimationType::SpecialCast
					|| i == (UINT)T::eAnimationType::Special1
					|| i == (UINT)T::eAnimationType::Special2
					|| i == (UINT)T::eAnimationType::Special3
					|| i == (UINT)T::eAnimationType::Special4)
				{
					makeSkillCastAnimation(i, m);
				}
			}
		}
		mAnimationType = T::eAnimationType::Natural;
		mAnimator->PlayAnimation(curMonsterData.animationString[(UINT)mAnimationType] + animStrings[mDirection], true);
		SET_SCALE_XYZ(GetOwner(), curMonsterData.animationSizes[(UINT)mAnimationType].x, curMonsterData.animationSizes[(UINT)mAnimationType].y, 0.f);

		mMonster = static_cast<Monster*>(GetOwner());
	}
	template <typename T>
	void MonsterScript<T>::Update()
	{
		Script::Update();
		if (nullptr == mMonster)
			return;

		MakeDirection();

		//if (!skillMake)

		//if(mLeftHand)
			//mLeftHand->SetDirection(mDirection);

		if (mRightHand)
			mRightHand->SetDirection(mDirection);

		if (mMonster->GetBattleState() == GameObject::eBattleState::Idle
			|| mMonster->GetBattleState() == GameObject::eBattleState::Run
			&& (nullptr == mSkill && nullptr == mSkillBuff))
		{
			int selectSpecialSkillBranshNum = rand() % 1000;
			if(selectSpecialSkillBranshNum == (int)T::eAnimationType::SpecialCast
				|| selectSpecialSkillBranshNum == (int)T::eAnimationType::Special1
				|| selectSpecialSkillBranshNum == (int)T::eAnimationType::Special2
				|| selectSpecialSkillBranshNum == (int)T::eAnimationType::Special3
				|| selectSpecialSkillBranshNum == (int)T::eAnimationType::Special4
				)
			{
			    if(curMonsterData.textureString[selectSpecialSkillBranshNum] != L"")
					SpecialAttackAnimation(selectSpecialSkillBranshNum);
			}
		}

		if (mMonster->GetBattleState() == GameObject::eBattleState::Cast
			&& curMonsterData.textureString[(UINT)T::eAnimationType::SpecialCast] != L"")
		{
			SpecialAttackAnimationConitnue();
		}

		//if (mMonster->Arrival())
		//{
		//	AttackAnimation();
		//}

		if (curMonsterData.mClass != eMonsterClass::Boss && mMonster->GetHit())
		{
			//GetOwner()->SetBattleState(GameObject::Hit);
			HitAnimation();
		}

		//mLeftHand->SetAniType((int)mAnimationType);
		if (mRightHand)
			mRightHand->SetAniType((int)mAnimationType);

		if (
			GetOwner()->GetBattleState() == GameObject::Idle
			|| GetOwner()->GetBattleState() == GameObject::Run
			)
		{
			if (mMonster->StopF())
			{
				GetOwner()->SetBattleState(GameObject::Idle);
				mAnimationType = T::eAnimationType::Natural;
			}
			else
			{
				GetOwner()->SetBattleState(GameObject::Run);
				mAnimationType = T::eAnimationType::Run;
			}

			ElseAnimationPlay();
			//mLeftHand->SetAniType((int)mAnimationType);
			if (mRightHand)
				mRightHand->SetAniType((int)mAnimationType);
		}
	}
	template <typename T>
	void MonsterScript<T>::ElseAnimationPlay()
	{
		if (mAnimator->GetActiveAnimation()->GetKey() != curMonsterData.animationString[(UINT)mAnimationType] + animStrings[mDirection]
			&& curMonsterData.textureString[(UINT)mAnimationType] != L"")
		{

			SET_SCALE_XYZ(GetOwner(), curMonsterData.animationSizes[(UINT)mAnimationType].x, curMonsterData.animationSizes[(UINT)mAnimationType].y, 0.f);

			WSTRING_SUBSTR(mAnimator->GetActiveAnimation()->GetKey(), L'@', subStr1);

			int prevIndex = 0;
			if (subStr1 == curMonsterData.animationString[(UINT)T::eAnimationType::Run])
			{
				prevIndex = mAnimator->GetAnimationIndex();
			}

			mAnimator->PlayAnimation(curMonsterData.animationString[(UINT)mAnimationType] + animStrings[mDirection], true);
			if (mAnimationType == T::eAnimationType::Run)
			{
				mAnimator->SetAnimationStartIndex(curMonsterData.animStartIndex[(UINT)mAnimationType]);
				mAnimator->SetAnimationIndex(prevIndex);
			}
		}
	}
	template <typename T>
	void MonsterScript<T>::HitAnimation()
	{
		//if (mMonster->GetBattleState() != GameObject::eBattleState::Idle) return;

		mAnimationType = T::eAnimationType::Hit;
		SET_SCALE_XYZ(GetOwner(), curMonsterData.animationSizes[(UINT)mAnimationType].x, curMonsterData.animationSizes[(UINT)mAnimationType].y, 0.f);
		if (mAnimator->GetActiveAnimation()->GetKey() != curMonsterData.animationString[(UINT)mAnimationType] + animStrings[mDirection])
		{
			mAnimator->PlayAnimation(curMonsterData.animationString[(UINT)mAnimationType] + animStrings[mDirection], false);
		}
	}

	template <typename T>
	void MonsterScript<T>::AttackAnimation()
	{
		if (mMonster->GetBattleState() != GameObject::eBattleState::Idle) return;
		

		if (mMonster->GetRangeCollider()->SearchObjectGameObjectId(PlayerManager::player->GetGameObjectId()))
		{
			fAttackDelay += Time::fDeltaTime();
			if (curMonsterData.fAttackDelay <= fAttackDelay)
			{
				fAttackDelay = 0.f;
				//int randAttackMotion = rand() % 2 + 1;
				//mAnimationType = randAttackMotion == 1 ? T::eAnimationType::Attack1 : T::eAnimationType::Attack2;
				GetOwner()->SetBattleState(GameObject::Attack);
				mAnimationType = T::eAnimationType::Attack1;
				SET_SCALE_XYZ(GetOwner(), curMonsterData.animationSizes[(UINT)mAnimationType].x, curMonsterData.animationSizes[(UINT)mAnimationType].y, 0.f);
				if (mAnimator->GetActiveAnimation()->GetKey() != curMonsterData.animationString[(UINT)mAnimationType] + animStrings[mDirection])
				{
					mAnimator->PlayAnimation(curMonsterData.animationString[(UINT)mAnimationType] + animStrings[mDirection], false);
				}
			}
		}
	}

	template <typename T>
	void MonsterScript<T>::SpecialAttackAnimationConitnue()
	{
		WSTRING_SUBSTR(mAnimator->GetActiveAnimation()->GetKey(), L'@', subStr1);
		int prevIndex = 0;
		if (subStr1 == curMonsterData.animationString[(UINT)T::eAnimationType::SpecialCast])
		{
			prevIndex = mAnimator->GetAnimationIndex();
		}
		mAnimationType = T::eAnimationType::SpecialCast;
		SET_SCALE_XYZ(GetOwner(), curMonsterData.animationSizes[(UINT)mAnimationType].x, curMonsterData.animationSizes[(UINT)mAnimationType].y, 0.f);
		if (mAnimator->GetActiveAnimation()->GetKey() != curMonsterData.animationString[(UINT)mAnimationType] + animStrings[mDirection])
		{
			mAnimator->PlayAnimation(curMonsterData.animationString[(UINT)mAnimationType] + animStrings[mDirection], true);
			mAnimator->SetAnimationIndex(prevIndex);
		}
	}
	template <typename T>
	Collider2D* MonsterScript<T>::getSkillActiveCollider()
	{
		switch (curMonsterData.mSkillActiveColliderType[iCurSkillIndex])
		{
		case eColliderFunctionType::Sight:
		{
			return mMonster->GetSightCollider();
		}
		case eColliderFunctionType::Range:
		{
			return mMonster->GetRangeCollider();
		}
		case eColliderFunctionType::HitArea:
		{
			return mMonster->GetHitAreaCollider();
		}
		default:
		{
			return mMonster->GetSightCollider();
		}
		}
	}
	template <typename T>
	void MonsterScript<T>::SpecialAttackAnimation(int skillIndex)
	{
		if (curMonsterData.animationSizes[(UINT)skillIndex] == Vector2::Zero) return;

		Collider2D* speiclaAttackCollider = getSkillActiveCollider();

		if (speiclaAttackCollider->SearchObjectGameObjectId(PlayerManager::player->GetGameObjectId()))
		{
			mAnimationType = T::eAnimationType(skillIndex);
			GetOwner()->SetBattleState(GameObject::Cast);
			//mAnimationType = T::eAnimationType::SpecialCast;

			SET_SCALE_XYZ(GetOwner()
				, curMonsterData.animationSizes[(UINT)mAnimationType].x
				, curMonsterData.animationSizes[(UINT)mAnimationType].y
				, 0.f
			);
			if (mAnimator->GetActiveAnimation()->GetKey() != curMonsterData.animationString[(UINT)mAnimationType] + animStrings[mDirection])
			{
				mAnimator->PlayAnimation(curMonsterData.animationString[(UINT)mAnimationType] + animStrings[mDirection], true);

				if(curMonsterData.animStartIndex[(UINT)mAnimationType] != 0)
				    mAnimator->SetAnimationStartIndex(curMonsterData.animStartIndex[(UINT)mAnimationType]);
			}
		}
	}

	template <typename T>
	void MonsterScript<T>::LateUpdate()
	{
	}
	template <typename T>
	void MonsterScript<T>::Render()
	{
	}

	template <typename T>
	void MonsterScript<T>::MakeDirection()
	{
		Vector3 initPos = mMonster->GetPrevPosition();
		Vector3 destPos = mMonster->GetDestPosition();

		Vector3 moveVector = destPos - initPos;

		moveVector.Normalize();

		degree = RadianToDegree(atan2(moveVector.x, moveVector.y));


		int n = degree / (180.f / 5.f);
		if (n > 4) n = 4;

		if (n > 0)
			mDirection = mPlusDirections[n];
		else
			mDirection = mMinusDirections[abs(n)];
	}

	template <typename T>
	void MonsterScript<T>::AnimationStart(GameObject::eBattleState state)
	{
		GetOwner()->SetBattleState(state);
	}
	template <typename T>
	void MonsterScript<T>::AnimationComplete(GameObject::eBattleState state)
	{
		GetOwner()->SetBattleState(state);
	}

	//template<typename T>
	//void MonsterScript<T>::OnCollisionEnter(Collider2D* other)
	//{
	//	
	//}

	//template<typename T>
	//void MonsterScript<T>::OnCollisionStay(Collider2D* other)
	//{
	//	
	//}

	//template<typename T>
	//void MonsterScript<T>::OnCollisionExit(Collider2D* other)
	//{
	//}

	template<typename T>
	void MonsterScript<T>::AttackProgress()
	{
		if (mMonster->GetRangeCollider()->SearchObjectGameObjectId(PlayerManager::player->GetGameObjectId()))
		{
			PlayerManager::player->Hit(10);
		}
	}

	template<typename T>
	void MonsterScript<T>::Hit(bool hit, GameObject::eBattleState state)
	{
		mMonster->SetHit(hit);
		GetOwner()->SetBattleState(state);
	}
	template<typename T>
	void MonsterScript<T>::makeSkillCastAnimation(int type, int direction)
	{
		mAnimator->StartEvent(curMonsterData.animationString[type] + animStrings[direction])
			= [=]()
		{
			fAttackDelay = 0.f;
			if (curMonsterData.animStartIndex[(UINT)type] != 0)
				mAnimator->SetAnimationStartIndex(curMonsterData.animStartIndex[(UINT)type]);
			if (curMonsterData.animProgressStartIndex[(UINT)type] != 0)
				mAnimator->SetAnimationProgressIndex(curMonsterData.animProgressStartIndex[(UINT)type]);
			if (curMonsterData.animEndIndex[(UINT)type] != 0)
				mAnimator->SetAnimationEndIndex(curMonsterData.animEndIndex[(UINT)type]);
		};
		mAnimator->ProgressEvent(curMonsterData.animationString[type] + animStrings[direction])
			= [=]()
		{
			if (skillMake)
			{
				if (nullptr != mSkill)
				{
					if (mSkill->GetSkillFire())
					{
						if (curMonsterData.bSpecialSkillStopInProgress[iCurSkillIndex])
						{
							mMonster->SetBattleState(GameObject::eBattleState::Idle);
							skillMake = false;
						}

					}
				}
				else
				{
					if (curMonsterData.bSpecialSkillStopInProgress[iCurSkillIndex])
					{
						mMonster->SetBattleState(GameObject::eBattleState::Idle);
						skillMake = false;
					}
				}
			}
			else
			{
				iCurSkillIndex = 1;
				eSkillType skilltype = curMonsterData.mSpecialSkills[iCurSkillIndex];
				if (skilltype != eSkillType::END)
				{
					makeMonsterSkill(skilltype
						, GET_POS(GetOwner())
						, eLayerType::MonsterSkill
						, curMonsterData.mSpecialSkillAddFunction[iCurSkillIndex]
						, curMonsterData.mSpecialSkillCount[iCurSkillIndex]
					);
				}
			}
		};
		mAnimator->EndEvent(curMonsterData.animationString[type] + animStrings[direction])
			= [=]()
		{
			mMonster->SetBattleState(GameObject::eBattleState::Idle);
			skillMake = false;
		};
	}
	template<typename T>
	void MonsterScript<T>::makeMonsterSkill(eSkillType skillType, Vector3 vector3Pos
		, eLayerType fireLayerType, int addFunction, int skillCount)
	{
		Vector3 targetPos = TileManager::GetPlayerPosition();
		switch (skillFunctionTypes[(int)skillType])
		{
		case m::eSkillFunctionType::Straight:
		{
			mSkill = new SkillStraight(skillType, vector3Pos, skillSpeed[(int)skillType]);
			mSkill->SetCamera(GetOwner()->GetCamera());
			mSkill->SkillFire();
			SceneManager::GetActiveScene()->AddGameObject(fireLayerType, mSkill);
		}
		break;
		case m::eSkillFunctionType::Fall:
		{
			mSkill = new SkillFall(skillType, targetPos);
			mSkill->SetCamera(GetOwner()->GetCamera());
			mSkill->SkillFire();
			SceneManager::GetActiveScene()->AddGameObject(fireLayerType, mSkill);
		}
		case m::eSkillFunctionType::FallExplosion:
		{
			mSkill = new SkillFallExplosion(skillType, targetPos, fireLayerType);
			mSkill->SetCamera(GetOwner()->GetCamera());
			mSkill->SkillFire();
			SceneManager::GetActiveScene()->AddGameObject(fireLayerType, mSkill);
		}
		break;
		case m::eSkillFunctionType::MutiFall:
		{
			mSkill = new SkillMultiFire(targetPos, skillType, skillCount, addFunction, fireLayerType, Vector2(200.f, 50.f));
			mSkill->SetCamera(GetOwner()->GetCamera());
			//skill->SkillFire(); 
			SceneManager::GetActiveScene()->AddGameObject(eLayerType::AdapterSkill, mSkill);
		}
		break;
		case m::eSkillFunctionType::MultiStraight:
		case m::eSkillFunctionType::Raidal:
		{
			mSkill = new SkillMultiFire(GET_POS(GetOwner()), skillType, skillCount, addFunction, fireLayerType);
			mSkill->SetCamera(GetOwner()->GetCamera());
			//skill->SkillFire(); 
			SceneManager::GetActiveScene()->AddGameObject(eLayerType::AdapterSkill, mSkill);
		}
		break;
		case m::eSkillFunctionType::CircleFire:
		{
			mSkill = new SkillMultiFire(GET_POS(GetOwner()), skillType, skillCount, (int)SkillMultiFire::eFireType::Circle, fireLayerType);
			mSkill->SetCamera(GetOwner()->GetCamera());

			mSkill->SkillFire();
			SceneManager::GetActiveScene()->AddGameObject(eLayerType::AdapterSkill, mSkill);
		}
		case m::eSkillFunctionType::Buff:
		{
			mSkillBuff = new SkillBuff(GetOwner(), -1, skillType);
			mSkillBuff->SetCamera(GetOwner()->GetCamera());
			mSkillBuff->ActiveOverlay();
			SceneManager::GetActiveScene()->AddGameObject(fireLayerType, mSkillBuff);
		}
		break;
		case m::eSkillFunctionType::StunAttack:
		{
			mSkill = new SkillAbnormal(skillType, GET_POS(GetOwner()));
			mSkill->SetSkillOwnerLayer(fireLayerType);
			//Collider2D* rangeCol = dynamic_cast<MoveAbleObject*>(GetOwner())->GetRangeCollider();
			dynamic_cast<SkillAbnormal*>(mSkill)->SetAbnormalCollider(getSkillActiveCollider());
			SceneManager::GetActiveScene()->AddGameObject(fireLayerType, mSkill);
		}
		break;
		case m::eSkillFunctionType::Orb:
		{
			mSkill = new SkillOrb(skillType, GET_POS(GetOwner()), skillSpeed[(int)skillType]);
			mSkill->SetCamera(GetOwner()->GetCamera());
			mSkill->SkillFire();
			SceneManager::GetActiveScene()->AddGameObject(fireLayerType, mSkill);
		}
		break;
		case m::eSkillFunctionType::None:
			break;
		case m::eSkillFunctionType::END:
			break;
		default:
		{
			mSkill = new Skill(skillType, vector3Pos);
			mSkill->SetCamera(GetOwner()->GetCamera());
			mSkill->SkillFire();
			SceneManager::GetActiveScene()->AddGameObject(fireLayerType, mSkill);
		}
		break;
		}

		if (nullptr != mSkill || nullptr != mSkillBuff)
		{
			skillMake = true;
		}
	}
}
