#include "mAnimator.h"
namespace m
{
	Animator::Animator()
		:Component(eComponentType::Animator)
		, mActiveAnimation(nullptr)
		, mbLoop(false)
	{

	}
	Animator::~Animator()
	{
	}
	void Animator::Initialize()
	{
	}
	void Animator::Update()
	{
	}
	void Animator::LateUpdate()
	{
	}
	void Animator::Render()
	{
	}
	void Animator::Create(std::wstring name
						  , std::shared_ptr<graphics::Texture> atlas
						  , Vector2 leftTop
						  , Vector2 size
						  , UINT columnLength
						  , Vector2 offset
						  , float duration)
	{

	}
}