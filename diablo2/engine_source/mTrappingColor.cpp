#include "mTrappingColor.h"
namespace m
{
	TrappingColor::TrappingColor()
		: Component(eComponentType::Light)
		, mTrappingColorBuffer(nullptr)
	{
	}

	TrappingColor::~TrappingColor()
	{
		if(mTrappingColorBuffer)
		{
			delete mTrappingColorBuffer;
			mTrappingColorBuffer = nullptr;
		}

	}

	void TrappingColor::Initialize()
	{
		mTrappingColorBuffer = new graphics::StructuredBuffer();
	}

	void TrappingColor::Update()
	{
		mTrappingColorBuffer->Create(sizeof(TrappingColor), 1, eViewType::SRV, &mTrappinColor, true);
	}

	void TrappingColor::LateUpdate()
	{

	}

	void TrappingColor::Render()
	{
		mTrappingColorBuffer->BindSRV(eShaderStage::PS, 1);

		mTrappingColorBuffer->Clear();
	}
}
