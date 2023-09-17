#include "mPanel.h"
#include "../engine_source/mInput.h"
#include "../engine_source/mTransform.h"
#include "../engine_source/mMeshRenderer.h"
#include "../engine_source/mApplication.h"

extern m::Application application;
namespace m
{
	Panel::Panel()
	{}
	Panel::~Panel()
	{}
	void Panel::Initialize()
	{
		GameObject::Initialize();
	}
	void Panel::Update()
	{
		GameObject::Update();
	}
	void Panel::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Panel::Render()
	{
		GameObject::Render();
	}
}