#include "mSkillButton.h"
#include "..\engine_source\mTransform.h"
#include "..\engine_source\mMeshRenderer.h"
namespace m
{
	SkillButton::SkillButton(int _indexX, int _indexY
							 , float _startX, float _startY
							 , float _intervalX, float _intervalY
							 , int _skillIndex)
		: indexX(_indexX)
		, indexY(_indexY)
		, startX(_startX)
		, startY(_startY)
		, intervalX(_intervalX)
		, intervalY(_intervalY)
		, skillIndex(_skillIndex)
	{
		Transform* tr = GetComponent<Transform>();
		tr->SetPosition(Vector3((startX + indexX * intervalX) * Texture::GetWidRatio(), (startY - indexY * intervalY) * Texture::GetHeiRatio(), -1.f));
	}
	SkillButton::~SkillButton()
	{
	}
	void SkillButton::Initialize()
	{
		Button::Initialize();
	}
	void SkillButton::Update()
	{
		Button::Update();
		MeshRenderer* mr = GetComponent<MeshRenderer>();

		if (bCanClick)
		{
			mr->SetMaterial(DeClickMaterial);
			if(GetHover()) mr->SetMaterial(DeClickMaterial);
		}
	}
	void SkillButton::LateUpdate()
	{
		Button::LateUpdate();
	}
	void SkillButton::Render()
	{
		Button::Render();
	}
}