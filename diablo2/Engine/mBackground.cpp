#include "mBackground.h"

#include "..\engine_source\mInput.h"
#include "..\engine_source\mTransform.h"
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