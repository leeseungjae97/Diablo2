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
		// 공 움직임 구현



		// 렌더

	}

	void GameObject::LateUpdate()
	{

	}

	void GameObject::Render()
	{
		//상수버퍼로 위치정보 크기정보, 색깔, 업데이트 해줘야한다.
		//renderer::mesh->BindBuffer();
		//renderer::shader->Binds();
		//graphics::GetDevice()->DrawIndexed(renderer::mesh->GetIndexCount(), 0, 0);
	}
}