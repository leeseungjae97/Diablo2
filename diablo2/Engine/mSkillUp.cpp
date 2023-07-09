#include "mSkillUp.h"

#include "..\engine_source\mMeshRenderer.h"
#include "..\engine_source\mTransform.h"


namespace m
{
	SkillUp::SkillUp()
	{
		Transform* tr = GetComponent<Transform>();
		MeshRenderer* mr = AddComponent<MeshRenderer>();


	}
	SkillUp::~SkillUp()
	{}
	void SkillUp::Initialize()
	{
		UI::Initialize();
	}
	void SkillUp::Update()
	{
		UI::Update();
	}
	void SkillUp::LateUpdate()
	{
		UI::LateUpdate();
	}
	void SkillUp::Render()
	{
		UI::Render();
	}
}