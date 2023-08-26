#include "mTrappingColor.h"
#include "mGameObject.h"
namespace m
{
	TrappingColor::TrappingColor()
		: MeshRenderer()
		, mTrappingColorBuffer(nullptr)
	{
		mTrappingColorBuffer = new graphics::StructuredBuffer();
		mTrappingColorBuffer->Create(sizeof(TrapColor), 1, eViewType::SRV, nullptr, true);
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
		MeshRenderer::Initialize();
	}

	void TrappingColor::Update()
	{
		MeshRenderer::Update();
		//MeshRenderer* mr = GET_COMP(GetOwner(), MeshRenderer);
		//if (mr && nullptr == GetMaterial() && nullptr == GetMesh())
		//{
		//	if (mr->GetMaterial()) SetMaterial(mr->GetMaterial());
		//	if (mr->GetMesh()) SetMesh(mr->GetMesh());
		//}
		//
		//
		SetColor(Vector4(0.1f, 0.1f, 0.1f, 1.f));
	}

	void TrappingColor::LateUpdate()
	{
		MeshRenderer::LateUpdate();
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
