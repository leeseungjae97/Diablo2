#include "mBackground.h"
#include "mInput.h"
#include "mTransform.h"
namespace m
{
	Background::Background()
	{}
	Background::~Background()
	{}
	void Background::Initialize()
	{}
	void Background::Update()
	{
		GameObject::Update();
	}
	void Background::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Background::Render()
	{
		GameObject::Render();
	}
}