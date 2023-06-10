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
		mesh = new m::Mesh();
	}

	GameObject::~GameObject()
	{
		if (mesh) delete mesh;
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

		// triangle
		//vertexes.resize(3);
		//
		//vertexes[0].pos = Vector3(0.0f, 0.5f, 0.0f);
		//vertexes[0].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);

		//vertexes[1].pos = Vector3(0.5f, -0.5f, 0.0f);
		//vertexes[1].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);

		//vertexes[2].pos = Vector3(-0.5f, -0.5f, 0.0f);
		//vertexes[2].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);

		//indexes.push_back(0);
		//indexes.push_back(1);
		//indexes.push_back(2);

		// rhombus
		//vertexes.resize(4);
		//
		//vertexes[0].pos = Vector3(0.0f, 0.1f, 0.0f);
		//vertexes[0].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);

		//vertexes[1].pos = Vector3(0.1f, -0.1f, 0.0f);
		//vertexes[1].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);

		//vertexes[2].pos = Vector3(-0.1f, -0.1f, 0.0f);
		//vertexes[2].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
		//
		//vertexes[3].pos = Vector3(0.0f, -0.3f, 0.0f);
		//vertexes[3].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);

		//indexes.push_back(3);
		//indexes.push_back(2);
		//indexes.push_back(1);

		//indexes.push_back(0);
		//indexes.push_back(1);
		//indexes.push_back(2);

		// rect
		//vertexes.resize(4);

		//vertexes[0].pos = Vector4(-0.1f, 0.1f, 0.0f, 0.0f);
		//vertexes[0].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);

		//vertexes[1].pos = Vector4(0.1f, 0.1f, 0.0f, 0.0f);
		//vertexes[1].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);

		//vertexes[2].pos = Vector4(0.1f, -0.1f, 0.0f, 0.0f);
		//vertexes[2].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);

		//vertexes[3].pos = Vector4(-0.1f, -0.1f, 0.0f, 0.0f);
		//vertexes[3].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);

		//indexes.push_back(0);
		//indexes.push_back(2);
		//indexes.push_back(3);

		//indexes.push_back(0);
		//indexes.push_back(1);
		//indexes.push_back(2);


		// circle, polygon
		/*Vertex center = {
			Vector3(0.0f, 0.0f, 0.0f) ,
			Vector4(0.0f, 1.0f, 0.0f, 1.0f)
		};

		vertexes.push_back(center);


		int iSlice = 80;
		float fRadius = 0.5f;
		float fTheta = (3.14159f * 2.f) / (float)iSlice;


		for (float i = 0; i < iSlice; i++)
		{
			Vertex circleLine = {
				Vector3(fRadius * cosf(fTheta * i)
					, fRadius * sinf(fTheta * i)
					, 0.0f),
				Vector4(0.0f, 1.0f, 0.0f, 1.f)
			};
			circleLine.pos.x -= (fRadius * cosf(fTheta * i)) / 2;
			vertexes.push_back(circleLine);
		}

		int j = 0;
		for (int i = vertexes.size() - 1; i >= 0; --i)
		{
			j++;
			indexes.push_back(i + 1);
			if (j == 2)
			{
				j = 0;
				indexes.push_back(1);
				i++;
			}
		}
		indexes.push_back(1);*/

		mesh->CreateVertexBuffer(vertexes.data(), 4);
		mesh->CreateIndexBuffer(indexes.data(), indexes.size());
		mesh->BindBuffer();
		renderer::shader->Binds();

		std::shared_ptr<class m::graphics::ConstantBuffer> cb = renderer::constantBuffers[(UINT)eCBType::Transform];
		cb->SetData(&mVertexInfo);
		cb->Bind(eShaderStage::VS);
		
		graphics::GetDevice()->DrawIndexed(mesh->GetIndexCount(), 0, 0);
	}
}