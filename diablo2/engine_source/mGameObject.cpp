#include "mGameObject.h"
#include "mRenderer.h"
#include "mGraphicDevice_DX11.h"
#include "mTime.h"
#include "mInput.h"

namespace m
{
	GameObject::GameObject(Vector4 initPos, Vector4 initColor, bool _moveable)
		: mState(eState::Active)
		, moveable(_moveable)
	{
		mVertexInfo.pos = initPos;
		mVertexInfo.color = initColor;
		constantBuffer = new m::graphics::ConstantBuffer(eCBType::Transform);
		constantBuffer->Create(sizeof(Vertex));

		constantBuffer->SetData(&mVertexInfo);
		constantBuffer->Bind(eShaderStage::VS);
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
		if (moveable)
		{
			Vector4 pos = mVertexInfo.pos;
			if (KEY_PRESSED(eKeyCode::UP))
			{
				pos.y += 0.1f * (float)Time::DeltaTime();
			}
			if (KEY_PRESSED(eKeyCode::DOWN))
			{
				pos.y -= 0.1f * (float)Time::DeltaTime();
			}
			if (KEY_PRESSED(eKeyCode::LEFT))
			{
				pos.x -= 0.1f * (float)Time::DeltaTime();
			}
			if (KEY_PRESSED(eKeyCode::RIGHT))
			{
				pos.x += 0.1f * (float)Time::DeltaTime();
			}
			if (pos != mVertexInfo.pos)
			{
				mVertexInfo.pos = pos;
			}
		}
	}

	void GameObject::LateUpdate()
	{

	}

	void GameObject::Render()
	{
		//상수버퍼로 위치정보 크기정보, 색깔, 업데이트 해줘야한다.
		constantBuffer->SetData(&mVertexInfo);
		constantBuffer->Bind(eShaderStage::VS);

		renderer::mesh->BindBuffer();
		renderer::shader->Binds();
		graphics::GetDevice()->DrawIndexed(renderer::mesh->GetIndexCount(), 0, 0);
	}
}