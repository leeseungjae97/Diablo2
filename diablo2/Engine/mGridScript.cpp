#include "mGridScript.h"

#include "..\engine_source\mTransform.h"
#include "..\engine_source\mGameObject.h"
#include "..\engine_source\mApplication.h"
#include "..\engine_source\mConstantBuffer.h"
#include "..\engine_source\mRenderer.h"

extern m::Application application;

namespace m
{
	GridScript::GridScript()
		: mCamera(nullptr)
	{}
	GridScript::~GridScript()
	{}
	void GridScript::Initialize()
	{}
	void GridScript::Update()
	{
		if (mCamera == nullptr)
			return;

		GameObject* gameObj = mCamera->GetOwner();

		Transform* tr = gameObj->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();

		float scale = mCamera->GetSize();

		HWND hWnd = application.GetHwnd();
		RECT winRect = {};
		GetClientRect(hWnd, &winRect);

		float width = winRect.right - winRect.left;
		float height = winRect.bottom - winRect.top;
		Vector2 resolution(width, height);

		///cs buffer
		graphics::ConstantBuffer* cb
			= renderer::constantBuffers[(int)eCBType::Grid];

		renderer::GridCB data;
		data.CameraPosition = Vector4(pos.x - 800.f, pos.y - 450.f, pos.z, 1.0f);
		data.Resolution = resolution;
		data.CameraScale = Vector2(scale, scale);

		cb->SetData(&data);
		cb->Bind(eShaderStage::VS);
		cb->Bind(eShaderStage::PS);
	}
	void GridScript::LateUpdate()
	{}
	void GridScript::Render()
	{}
}