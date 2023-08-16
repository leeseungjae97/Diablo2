#include "mSkillOverlay.h"

#include "../engine_source/mMeshRenderer.h"
#include "../engine_source/mAnimator.h"

#include "mPlayerInfo.h"
#include "mPlayer.h"
#include "mMonster.h"
namespace m
{
	SkillOverlay::SkillOverlay(int index)
		: mCurIndex(index)
	{
		ADD_COMP(this, MeshRenderer);
		ADD_COMP(this, Animator);
		SET_MESH(this, L"RectMesh");
		SET_MATERIAL(this, L"AnimationMaterial");
		if (mCurIndex == -1)
		{
			//crashNames[0];
			mOESS = AddComponent<OverlayEffectSkillScript>(mCurIndex);
		}
		else
		{
		
			eSkillCastType castType = skillCastTypes[(UINT)PlayerInfo::GetSkill(mCurIndex)];

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
		if (bActiveOverlay)
		{
			mOESS->PlayOverlaySkill();
			bActiveOverlay = false;
		}
		SET_POS_VEC(this, GET_POS(mActiveOwner));
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
}