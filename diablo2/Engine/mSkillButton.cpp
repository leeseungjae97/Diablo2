#include "mSkillButton.h"
#include "../engine_source/mTransform.h"
#include "../engine_source/mMeshRenderer.h"
namespace m
{
	SkillButton::SkillButton(int _indexX, int _indexY
		, float _startX, float _startY
		, float _intervalX, float _intervalY
		, int _skillIndex)
		: Button(false)
		, indexX(_indexX)
		, indexY(_indexY)
		, startX(_startX)
		, startY(_startY)
		, intervalX(_intervalX)
		, intervalY(_intervalY)
		, skillIndex(_skillIndex)
	{
		Transform* tr = GetComponent<Transform>();
		tr->SetPosition(Vector3((startX + indexX * intervalX) * Texture::GetWidRatio(), (startY - indexY * intervalY) * Texture::GetHeiRatio(), -1.f));

		mTC = ADD_COMP(this, TrappingColor);
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
		if (GetCanClick())
		{
			mTC->SetColor(Vector4(1.0f, 1.0f, 1.0f, 1.f));
		}
		else
		{
			mTC->SetColor(Vector4(0.2f, 0.2f, 0.2f, 1.f));
		}
		if (GetHover())
		{
			mTC->SetColor(Vector4(0.0f, 0.0f, 1.0f, 1.f));
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