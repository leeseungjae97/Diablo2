#include "mUI.h"

#include "..\engine_source\mTransform.h"
#include "..\engine_source\mMeshRenderer.h"
#include "..\engine_source\mCamera.h"
#include "..\engine_source\mInput.h"
#include "..\engine_source\mMouseManager.h"
#include "..\engine_source\mApplication.h"

extern m::Application application;
namespace m
{
	UI::UI()
	{
		AddComponent<MeshRenderer>();
	}
	UI::~UI()
	{}
	void UI::Initialize()
	{}
	void UI::Update()
	{
		GameObject::Update();
	}
	void UI::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void UI::Render()
	{
		GameObject::Render();
	}
}