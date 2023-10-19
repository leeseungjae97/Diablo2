#include "mMeshRenderer.h"
#include "mTransform.h"
#include "mGameObject.h"
#include "mAnimator.h"
namespace m
{
	MeshRenderer::MeshRenderer()
		: Component(eComponentType::MeshRenderer)
	    , mTrappingColorBuffer(nullptr)
	    , mSpriteOffSetCenterBuffer(nullptr)
	    , mSpriteAlphaBuffer(nullptr)
	{
	}
	MeshRenderer::~MeshRenderer()
	{
		if (mTrappingColorBuffer)
		{
			delete mTrappingColorBuffer;
			mTrappingColorBuffer = nullptr;
		}
		if(mSpriteOffSetCenterBuffer)
		{
			delete mSpriteOffSetCenterBuffer;
			mSpriteOffSetCenterBuffer = nullptr;
		}
		if(mSpriteAlphaBuffer)
		{
			delete mSpriteAlphaBuffer;
			mSpriteAlphaBuffer = nullptr;
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
		if (mSpriteOffSetCenterBuffer)
			mSpriteOffSetCenterBuffer->SetData(&mSpriteOffsetCenter, 1);
		if(mSpriteAlphaBuffer)
			mSpriteAlphaBuffer->SetData(&mSpriteAlpha, 1);
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
			if(mSpriteOffSetCenterBuffer)
			{
				mSpriteOffSetCenterBuffer->BindSRV(eShaderStage::PS, 21);
				mSpriteOffSetCenterBuffer->BindSRV(eShaderStage::VS, 21);
			}
			if(mSpriteAlphaBuffer)
			{
				mSpriteAlphaBuffer->BindSRV(eShaderStage::PS, 22);
				mSpriteAlphaBuffer->BindSRV(eShaderStage::VS, 22);
			}

		}
		mMesh->Render();
		mMaterial->Clear();
		if (mTrappingColorBuffer)
			mTrappingColorBuffer->Clear();
		if (mSpriteOffSetCenterBuffer)
			mSpriteOffSetCenterBuffer->Clear();
		if (mSpriteAlphaBuffer)
			mSpriteAlphaBuffer->Clear();
	}

    void MeshRenderer::AddTrappingColorBuffer()
    {
		mTrappingColorBuffer = new graphics::StructuredBuffer();
		mTrappingColorBuffer->Create(sizeof(TrapColor), 1, eViewType::SRV, nullptr, true);
    }

    void MeshRenderer::AddSpriteOffSetCenterBuffer()
    {
		mSpriteOffSetCenterBuffer = new graphics::StructuredBuffer();
		mSpriteOffSetCenterBuffer->Create(sizeof(SpriteOffsetCenter), 1, eViewType::SRV, nullptr, true);
    }

    void MeshRenderer::AddSpriteAlphaBuffer()
    {
		mSpriteAlphaBuffer = new graphics::StructuredBuffer();
		mSpriteAlphaBuffer->Create(sizeof(SpriteAlpha), 1, eViewType::SRV, nullptr, true);
    }
}
