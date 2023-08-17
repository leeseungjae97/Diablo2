#include "mGridScript.h"

#include "../engine_source/mTransform.h"
#include "../engine_source/mGameObject.h"
#include "../engine_source/mApplication.h"
#include "../engine_source/mConstantBuffer.h"
#include "../engine_source/mRenderer.h"
#include "../engine_source/mTexture.h"

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
		//pos.z += 1.1f;
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
		data.CameraPosition = Vector4(pos.x - RESOL_WID / 2.f, pos.y - RESOL_HEI / 2.f, pos.z, 1.0f);
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