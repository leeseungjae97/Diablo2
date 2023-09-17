#include "mUI.h"

#include "mFontWrapper.h"
#include "../engine_source/mTransform.h"
#include "../engine_source/mMeshRenderer.h"
#include "../engine_source/mCamera.h"
#include "../engine_source/mInput.h"
#include "../engine_source/mMouseManager.h"
#include "../engine_source/mApplication.h"

extern m::Application application;
namespace m
{
	UI::UI()
		: wsText(L"")
		, fTextSize(20.f)
		, vTextColor(Vector4(1.f, 1.f, 1.f, 1.f))

	{
		AddComponent<MeshRenderer>();
	}

	UI::UI(bool useDefaultMeshRenderer)
		: wsText(L"")
		, fTextSize(20.f)
		, vTextColor(Vector4(1.f, 1.f, 1.f, 1.f))
	{

	}

	UI::~UI()
	{
	}
	void UI::Initialize()
	{
	}
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
		drawText();
	}
	void UI::drawText()
	{
		if (wsText == L"") return;

		Vector3 pos = GET_POS(this);

		Matrix proj = Matrix::Identity;
		Matrix view = Matrix::Identity;

		if (nullptr == GetCamera())
		{
			proj = Camera::GetProjectionMatrix();
			view = Camera::GetViewMatrix();
		}
		else
		{
			proj = GetCamera()->GetPrivateProjectionMatrix();
			view = GetCamera()->GetPrivateViewMatrix();
		}
		Viewport viewport = {
		0.f,
		0.f,
		RESOL_WID,
		RESOL_HEI,
		10.f,
	-1.f,
		};
		Vector3 unPos = Vector3(pos.x, pos.y, pos.z);
		Vector3 unprojPos = viewport.Unproject(unPos, proj, view, Matrix::Identity);

		FontWrapper::DrawFont(wsText.c_str(), unprojPos.x, unprojPos.y, fTextSize
			, FONT_RGBA(vTextColor.x, vTextColor.y, vTextColor.z, vTextColor.w));
		//FontWrapper::DrawFont(wsText.c_str(), 10, 10, fTextSize
		//	, FONT_RGBA(vTextColor.x, vTextColor.y, vTextColor.z, vTextColor.w));
	}
}