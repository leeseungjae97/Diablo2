#include "mUVUI.h"

#include "../engine_source/mConstantBuffer.h"
#include "../engine_source/mRenderer.h"
#include "../engine_source/mMeshRenderer.h"

namespace m
{
	UVUI::UVUI()
		: mUVCoord(0.0f)
	    , mType(1)
	{
		mAddictionMaterial = RESOURCE_FIND(graphics::Material, L"addictionHp");
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
		data.uvControlType = mType;
		ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::UVControl];
		cb->SetData(&data);

		cb->Bind(eShaderStage::VS);
		cb->Bind(eShaderStage::PS);
		UI::Render();
	}

    void UVUI::SetAddiction()
    {
		SET_MATERIAL_D(this, mAddictionMaterial);
    }

    void UVUI::SetOrigin()
    {
		SET_MATERIAL_D(this, mOriginMaterial);
    }
}
