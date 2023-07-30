#include "mUVUI.h"

#include "../engine_source/mConstantBuffer.h"
#include "../engine_source/mRenderer.h"

namespace m
{
	UVUI::UVUI()
		: mUVCoord(0.0f)
	{
	}
	UVUI::~UVUI()
	{
	}
	void UVUI::Initialize()
	{
		UI::Initialize();
	}
	void UVUI::Update()
	{
		UI::Update();
	}
	void UVUI::LateUpdate()
	{
		UI::LateUpdate();	
	}
	void UVUI::Render()
	{
		renderer::UVControlCB data = {};
		data.UVYCoord = mUVCoord;
		data.uvControlType = 1;
		ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::UVControl];
		cb->SetData(&data);

		cb->Bind(eShaderStage::VS);
		cb->Bind(eShaderStage::PS);
		UI::Render();
	}
}