#include "mGameObject.h"
#include "mRenderer.h"
#include "mGraphicDevice_DX11.h"

namespace m
{
	GameObject::GameObject()
		: mState(eState::Active)
	{
	}

	GameObject::~GameObject()
	{
	}

	void GameObject::Initialize()
	{
	}

	void GameObject::Update()
	{
		// �� ������ ����



		// ����

	}

	void GameObject::LateUpdate()
	{

	}

	void GameObject::Render()
	{
		//������۷� ��ġ���� ũ������, ����, ������Ʈ ������Ѵ�.
		//renderer::mesh->BindBuffer();
		//renderer::shader->Binds();
		//graphics::GetDevice()->DrawIndexed(renderer::mesh->GetIndexCount(), 0, 0);
	}
}