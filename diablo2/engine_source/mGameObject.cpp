#include "mGameObject.h"
#include "mGraphicDevice_DX11.h"
#include "mConstantBuffer.h"
#include "mTime.h"
#include "mInput.h"
#include "mScene.h"

namespace m
{
	GameObject::GameObject(Vector4 initPos
		, Vector4 initColor
		, enums::eGameObjectType objectType
		, float _fSize
		, Scene* scene)
		: mState(eState::Active)
		, mObjectType(objectType)
		, fSize(_fSize)
		, onwerScene(scene)
	{
		mVertexInfo.pos = initPos;
		mVertexInfo.color = initColor;
	}

	GameObject::~GameObject()
	{
	}

	void GameObject::Initialize()
	{
	}

	void GameObject::Update()
	{

		if (mObjectType == enums::eGameObjectType::Player)
		{
			float ratio = 16.f / 9.f;
			for (GameObject* gameObj : onwerScene->GetGameObjects())
			{
				if (gameObj->GetGameObjectType() == enums::eGameObjectType::Player) continue;

				if (fabs(mVertexInfo.pos.x - gameObj->GetPos().x) < (fSize / ratio + gameObj->GetSize() / ratio)
					&& fabs(mVertexInfo.pos.y - gameObj->GetPos().y) < (fSize + gameObj->GetSize()))
				{
					if (gameObj->GetState() != eState::Dead)
					{
						fSize += 0.01f;
					}
					gameObj->SetState(eState::Dead);
				}
			}
		}
		

		if (mObjectType == enums::eGameObjectType::Player)
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
		vector<renderer::Vertex> vertexes;
		vector<UINT> indexes;

		vertexes.resize(4);
		float ratio = 16.f / 9.f;
		vertexes[0].pos = Vector4(-fSize / ratio, fSize, 0.0f, 0.0f);
		vertexes[0].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);

		vertexes[1].pos = Vector4(fSize / ratio, fSize, 0.0f, 0.0f);
		vertexes[1].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);

		vertexes[2].pos = Vector4(fSize / ratio, -fSize, 0.0f, 0.0f);
		vertexes[2].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);

		vertexes[3].pos = Vector4(-fSize / ratio, -fSize, 0.0f, 0.0f);
		vertexes[3].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);

		indexes.push_back(0);
		indexes.push_back(2);
		indexes.push_back(3);

		indexes.push_back(0);
		indexes.push_back(1);
		indexes.push_back(2);

		mesh = new m::Mesh();

		mesh->CreateVertexBuffer(vertexes.data(), 4);
		mesh->CreateIndexBuffer(indexes.data(), indexes.size());

		renderer::constantBuffers[(UINT)eCBType::Transform]->SetData(&mVertexInfo);
		renderer::constantBuffers[(UINT)eCBType::Transform]->Bind(eShaderStage::VS);

		mesh->BindBuffer();
		//renderer::mesh->BindBuffer();
		renderer::shader->Binds();
		graphics::GetDevice()->DrawIndexed(mesh->GetIndexCount(), 0, 0);
	}
}