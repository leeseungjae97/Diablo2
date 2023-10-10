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
		, vTextHoverColor(Vector4(1.f, 1.f, 1.f, 1.f))
		, vTextNormalColor(Vector4(1.f, 1.f, 1.f, 1.f))
	    , vTextOffset(Vector2::Zero)

	{
		AddComponent<MeshRenderer>();
	}

	UI::UI(bool useDefaultMeshRenderer)
		: wsText(L"")
		, fTextSize(20.f)
		, vTextColor(Vector4(1.f, 1.f, 1.f, 1.f))
		, vTextHoverColor(Vector4(1.f, 1.f, 1.f, 1.f))
		, vTextNormalColor(Vector4(1.f, 1.f, 1.f, 1.f))
		, vTextOffset(Vector2::Zero)
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
		if(GetHover())
		{
			if(vTextHoverColor != Vector4::One)
			    vTextColor = vTextHoverColor;
		}else
		{
			if (vTextNormalColor != Vector4::One)
			    vTextColor = vTextNormalColor;
		}

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
		Vector2 fontSize = FontWrapper::GetTextSize(wsText.c_str(), fTextSize);
		Vector3 pp = GetComponent<Transform>()->ProjectionCetnerPosition(fontSize);

		pp.x += vTextOffset.x;
		pp.y += vTextOffset.y;

		FontWrapper::DrawFont(wsText.c_str(), pp.x, pp.y, fTextSize
			, FONT_RGBA(vTextColor.x, vTextColor.y, vTextColor.z, vTextColor.w));
		//FontWrapper::DrawFont(wsText.c_str(), 10, 10, fTextSize
		//	, FONT_RGBA(vTextNormalColor.x, vTextNormalColor.y, vTextNormalColor.z, vTextNormalColor.w));
	}
}