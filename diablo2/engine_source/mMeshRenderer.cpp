#include "mMeshRenderer.h"
#include "mTransform.h"
#include "mGameObject.h"
#include "mAnimator.h"
namespace m
{
	MeshRenderer::MeshRenderer()
		: Component(eComponentType::MeshRenderer)
	{}
	MeshRenderer::~MeshRenderer()
	{
		if (mTrappingColorBuffer)
		{
			delete mTrappingColorBuffer;
			mTrappingColorBuffer = nullptr;
		}
	}
	void MeshRenderer::Initialize()
	{}
	void MeshRenderer::Update()
	{}
	void MeshRenderer::LateUpdate()
	{
		if (mTrappingColorBuffer)
		    mTrappingColorBuffer->SetData(&mTrappingColor, 1);
	}
	void MeshRenderer::Render()
	{
		Animator* animator = GetOwner()->GetComponent<Animator>();
		if (animator)
		{
			animator->Binds();
		}


		if (GetOwner()->GetState() != GameObject::eState::RenderUpdate)
		{
			mMaterial->Clear();
		}
		else
		{
			Transform* tr = GetOwner()->GetComponent<Transform>();
			tr->BindConstantBuffer();

			mMesh->BindBuffer();
			mMaterial->Binds();
			if (mTrappingColorBuffer)
			{
				mTrappingColorBuffer->BindSRV(eShaderStage::PS, 20);
				mTrappingColorBuffer->BindSRV(eShaderStage::VS, 20);
			}

		}
		mMesh->Render();
		mMaterial->Clear();
		if (mTrappingColorBuffer)
			mTrappingColorBuffer->Clear();
	}

    void MeshRenderer::AddTrappingColorBuffer()
    {
		mTrappingColorBuffer = new graphics::StructuredBuffer();
		mTrappingColorBuffer->Create(sizeof(TrapColor), 1, eViewType::SRV, nullptr, true);
    }
}
