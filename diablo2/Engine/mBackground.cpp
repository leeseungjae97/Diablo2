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
		UI::Update();
	}
	void Background::LateUpdate()
	{
		UI::LateUpdate();
	}
	void Background::Render()
	{
		UI::Render();
	}
}