#include "mOverlay.h"

#include "../engine_source/mMeshRenderer.h"
#include "mOverlayScript.h"
#include "mMoveAbleObject.h"

namespace m
{
	Overlay::Overlay(const std::wstring& overlayName
		, Vector3 initPos
		, Vector2 size
		, Vector2 offset
		, Vector2 centerPos
		, int length
		, float duration
		, bool loop
	)
	{
		ADD_COMP(this, MeshRenderer);
		ADD_COMP(this, Animator);

		SET_MESH(this, L"RectMesh");
		SET_MATERIAL(this, L"AnimationMaterial");

		SET_POS_VEC(this, initPos);
		SET_SCALE_XYZ(this, size.x, size.y, 1.f);
		OverlayScript* os = ADD_COMP(this, OverlayScript);
		os->MakeOverlayAnimation(overlayName, size, offset, centerPos, length, duration, loop);
	}

	Overlay::~Overlay()
	{
	}

	void Overlay::Initialize()
	{
		GameObject::Initialize();
	}

	void Overlay::Update()
	{
		GameObject::Update();

		Vector3 pos = GET_POS(mOwnerObject);
		if(bOverDraw)
			pos.z -= 0.00001f;

		SET_POS_VEC(this, pos);
	}

	void Overlay::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void Overlay::Render()
	{
		GameObject::Render();
	}

    void Overlay::MakeOverlay(std::wstring overlayName, Vector2 size, Vector2 offset,
        Vector2 centerPos, int length, float duration, bool loop)
    {
		//wsOverlayName = overlayName;
		
		//if (nullptr == mat->GetTexture()) return;
		
		OverlayScript* os = GET_COMP(this, OverlayScript);
		if(os)
		    os->MakeOverlayAnimation(overlayName, size, offset, centerPos, length, duration, loop);
    }

    void Overlay::SetDirection(int direction)
    {
		OverlayScript* os = GET_COMP(this, OverlayScript);
		if(os)
		    os->SetDirection(direction);
    }
	void Overlay::SetSyncPlay(Animator* animator)
	{
		OverlayScript* os = GET_COMP(this, OverlayScript);
		if(os)
		    os->SetSyncPlay(animator);
	}
}
