#include "mSkillOverlay.h"

#include "../engine_source/mMeshRenderer.h"
#include "../engine_source/mAnimator.h"

#include "mPlayerManager.h"
#include "mMonster.h"
#include "mTime.h"

namespace m
{
	SkillOverlay::SkillOverlay(int index, eSkillCastType ecType)
		: mCurIndex(index)
	    , fLoopSecond(0.f)
	    , fAccLoop(0.f)
	{
		ADD_COMP(this, MeshRenderer);
		ADD_COMP(this, Animator);
		SET_MESH(this, L"RectMesh");
		SET_MATERIAL(this, L"AnimationMaterial");
		if (mCurIndex == -1)
		{
			//crashNames[0];
			mOESS = AddComponent<OverlayEffectSkillScript>(mCurIndex);
			mOESS->SetSkillCastType(ecType);
		}
		else
		{
			eSkillCastType castType = skillCastTypes[(UINT)PlayerManager::GetSkill(mCurIndex)];

			if (castType == eSkillCastType::END) return;

			SET_SCALE_XYZ(this
						  , castSizes[(UINT)castType].x
						  , castSizes[(UINT)castType].y, 1.f);
			mOESS = AddComponent<OverlayEffectSkillScript>(mCurIndex);
		}
		
	}
	SkillOverlay::~SkillOverlay()
	{
	}
	void SkillOverlay::Update()
	{
		GameObject::Update();
		if (fLoopSecond != 0.f)
		{
			fAccLoop += Time::fDeltaTime();
		}
		if(fLoopSecond != 0.f && fAccLoop >= fLoopSecond)
		{
			fAccLoop = 0.f;
			fLoopSecond = 0.f;
			mOESS->StopOverlaySkill();
			bActiveOverlay = false;
		}
		if (bActiveOverlay)
		{
			mOESS->PlayOverlaySkill();
			bActiveOverlay = false;
		}
		Vector3 pos = GET_POS(this);
		if(mActiveOwner)
		    pos = GET_POS(mActiveOwner);

		pos.z -= 0.00001f;
		SET_POS_VEC(this, pos);
	}
	void SkillOverlay::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void SkillOverlay::Render()
	{
		GameObject::Render();
	}
	void SkillOverlay::Initialize()
	{
		GameObject::Initialize();
	}
	void SkillOverlay::SetActiveOwner(GameObject* owner)
	{
		mActiveOwner = owner;
		SetCamera(mActiveOwner->GetCamera());
	}

    void SkillOverlay::SetSkillCastType(eSkillCastType type)
    {
		if(mOESS)
		{
			mOESS->SetSkillCastType(type);

			SET_SCALE_XYZ(this
				, castSizes[(UINT)type].x
				, castSizes[(UINT)type].y, 1.f);
		}
			
    }
	void SkillOverlay::SetSkillBackCast(eSkillCastType type)
	{
		if (mOESS)
		{
			mOESS->SetSkillCastType(type);

			SET_SCALE_XYZ(this
				, backCastSizes[(UINT)type].x
				, backCastSizes[(UINT)type].y, 1.f);
		}

	}
    void SkillOverlay::Back()
    {
		if(mActiveOwner)
		{
			if (mOESS)
			    mOESS->Back();
			Vector3 pos = GET_POS(mActiveOwner);
			pos.z += 0.00001f;
			SET_POS_VEC(this, pos);
		}
    }

    void SkillOverlay::SetSkillIndex(int skill_index)
    {
		if (mOESS)
		{
			mOESS->SetSkillIndex(skill_index);
		}
    }
}
