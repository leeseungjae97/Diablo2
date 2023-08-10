#include "mSkillFall.h"

#include "../engine_source/mAnimator.h"
#include "../engine_source/mMeshRenderer.h"
#include "../engine_source/mInput.h"
#include "../engine_source/mTime.h"

#include "mFallScript.h"

namespace m
{
	SkillFall::SkillFall(eSkillType type, Vector3 iniPos)
		: Skill(type, iniPos)
	{
		ADD_COMP(this, Animator);
		ADD_COMP(this, MeshRenderer);
		SET_MESH(this, L"RectMesh");
		SET_MATERIAL(this, L"noneRect");
		ADD_COMP(this, FallScript);
		Matrix proj = Matrix::Identity;
		Matrix view = Matrix::Identity;
		proj = GetCamera()->GetPrivateProjectionMatrix();
		view = GetCamera()->GetPrivateViewMatrix();
		Vector3 unprojMousePos = Input::GetUnprojectionMousePos(iniPos.z, proj, view);
		int randX = rand() % 200;

		unprojMousePos.y += 300.f;
		fInitYValue = unprojMousePos.y;
		unprojMousePos.x += (float)randX;

		SET_POS_VEC(this, unprojMousePos);
	}
	SkillFall::~SkillFall()
	{
	}
	void SkillFall::Update()
	{
		Vector3 mPos =GET_POS(this);
		if (fInitYValue - 300 <= mPos.y) return;
		mPos.y = mPos.y - fSpeed * Time::fDeltaTime();
		SET_POS_VEC(this, mPos);
	}
	void SkillFall::LateUpdate()
	{
	}
	void SkillFall::Render()
	{
	}
	void SkillFall::Initialize()
	{
	}
}