#include "mTrappingColor.h"
#include "mGameObject.h"
namespace m
{
	TrappingColor::TrappingColor()
		: MeshRenderer()
		, mTrappingColorBuffer(nullptr)
	{
		mTrappingColorBuffer = new graphics::StructuredBuffer();
		mTrappingColorBuffer->Create(sizeof(TrapColor), 1, eViewType::SRV, &mTrappingColor, true);
	}

	TrappingColor::~TrappingColor()
	{
		if (mTrappingColorBuffer)
		{
			delete mTrappingColorBuffer;
			mTrappingColorBuffer = nullptr;
		}
	}

	void TrappingColor::Initialize()
	{
	}

	void TrappingColor::Update()
	{
	}

	void TrappingColor::LateUpdate()
	{
		mTrappingColorBuffer->SetData(&mTrappingColor, 1);
	}

	void TrappingColor::Render()
	{
		//MeshRenderer* mr = GET_COMP(GetOwner(), MeshRenderer);
		//if (mr) mr->Render();

		if (GetOwner()->GetState() != GameObject::eState::RenderUpdate)
		{
			GetMaterial()->Clear();
		}
		else
		{
			Transform* tr = GetOwner()->GetComponent<Transform>();
			tr->BindConstantBuffer();
			GetMesh()->BindBuffer();
			GetMaterial()->Binds();

			mTrappingColorBuffer->BindSRV(eShaderStage::PS, 20);
			mTrappingColorBuffer->BindSRV(eShaderStage::VS, 20);
		}
		GetMesh()->Render();
		GetMaterial()->Clear();
		mTrappingColorBuffer->Clear();
	}
}
