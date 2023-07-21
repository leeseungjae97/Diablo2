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
	{}
	void MeshRenderer::Initialize()
	{}
	void MeshRenderer::Update()
	{}
	void MeshRenderer::LateUpdate()
	{}
	void MeshRenderer::Render()
	{
		Animator* animator = GetOwner()->GetComponent<Animator>();
		if (animator)
		{
			animator->Binds();
		}

		if (GetOwner()->GetState() != GameObject::eState::Active)
		{
			mMaterial->Clear();
		}
		else
		{
			Transform* tr = GetOwner()->GetComponent<Transform>();
			tr->BindConstantBuffer();

			mMesh->BindBuffer();
			mMaterial->Binds();
		}
	
		mMesh->Render();

		mMaterial->Clear();
	}
}