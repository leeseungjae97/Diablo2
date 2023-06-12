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
	bool GameObject::CrossCircleLine(GameObject* other)
	{
		float dX = mVertexInfo.pos.x - other->GetPos().x;
		float dY = mVertexInfo.pos.y - other->GetPos().y;

		float length = sqrt(dX * dX + dY * dY);

		for (Vector4 vIndexPos : other->GetCircleIndexes())
		{
			float length2 = vIndexPos.Length();

			for (Vector4 vMIndexPos : circleIndexes)
			{
				//if (vIndexPos + other->GetPos() == vMIndexPos + mVertexInfo.pos)
				//{
				//	return true;
				//}

				//float length3 = vMIndexPos.Length();
				//if (length <= length2 + length3)
				//{
				//	return true;
				//}

				if (fSize + other->GetSize() >= length)
				{
					return true;
				}
			}
			
		}
		return false;
	}
	void GameObject::Update()
	{

		if (mObjectType == enums::eGameObjectType::Player)
		{
			//check rect 
			//float ratio = 16.f / 9.f;
			//for (GameObject* gameObj : onwerScene->GetGameObjects())
			//{
			//	if (gameObj->GetGameObjectType() == enums::eGameObjectType::Player) continue;

			//	if (fabs(mVertexInfo.pos.x - gameObj->GetPos().x) < (fSize / ratio + gameObj->GetSize() / ratio)
			//		&& fabs(mVertexInfo.pos.y - gameObj->GetPos().y) < (fSize + gameObj->GetSize()))
			//	{
			//		if (gameObj->GetState() != eState::Dead)
			//		{
			//			fSize += 0.01f;
			//		}
			//		gameObj->SetState(eState::Dead);
			//	}
			//}

			for (GameObject* gameObj : onwerScene->GetGameObjects())
			{
				if (gameObj->GetGameObjectType() == enums::eGameObjectType::Player) continue;

				if (CrossCircleLine(gameObj))
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

		//vertexes.resize(4);
		//float ratio = 16.f / 9.f;
		//vertexes[0].pos = Vector4(-fSize / ratio, fSize, 0.0f, 0.0f);
		//vertexes[0].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);

		//vertexes[1].pos = Vector4(fSize / ratio, fSize, 0.0f, 0.0f);
		//vertexes[1].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);

		//vertexes[2].pos = Vector4(fSize / ratio, -fSize, 0.0f, 0.0f);
		//vertexes[2].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);

		//vertexes[3].pos = Vector4(-fSize / ratio, -fSize, 0.0f, 0.0f);
		//vertexes[3].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);

		//indexes.push_back(0);
		//indexes.push_back(2);
		//indexes.push_back(3);

		//indexes.push_back(0);
		//indexes.push_back(1);
		//indexes.push_back(2);

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
		circleIndexes.clear();

		renderer::Vertex center = {
			Vector4(0.0f, 0.0f, 0.0f, 0.0f) ,
			Vector4(0.0f, 1.0f, 0.0f, 1.0f)
		};

		vertexes.push_back(center);
		

		int iSlice = 80;
		float fTheta = (3.14159f * 2.f) / (float)iSlice;
		
		for (float i = 0; i < iSlice; i++)
		{
			renderer::Vertex circleLine = {
				Vector4(fSize * cosf(fTheta * i)
					, fSize * sinf(fTheta * i)
					, 0.0f, 0.0f),
				Vector4(0.0f, 1.0f, 0.0f, 1.f)
			};
			//circleLine.pos.x -= (fSize * cosf(fTheta * i)) / 2;
			circleIndexes.push_back(circleLine.pos);
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
		indexes.push_back(1);

		mesh->CreateVertexBuffer(vertexes.data(), vertexes.size() - 1);
		mesh->CreateIndexBuffer(indexes.data(), indexes.size());
		mesh->BindBuffer();
		renderer::shader->Binds();

		std::shared_ptr<class m::graphics::ConstantBuffer> cb = renderer::constantBuffers[(UINT)eCBType::Transform];
		//cb->SetProjectionMatrix(Matrix::CreateOrthographicLH(1600.f, 900.f, 1.f, 1000.f));
		cb->SetProjectionMatrix(Matrix::CreatePerspectiveFieldOfViewLH(XM_2PI / 6.0f, (16.f / 9.f), 1.f, 1000.f));
		cb->SetView(Matrix::Identity, Vector3(mVertexInfo.pos.x, mVertexInfo.pos.y, mVertexInfo.pos.z));

		cb->SetData(&mVertexInfo);
		cb->Bind(eShaderStage::VS);
		cb->Bind(eShaderStage::HS);
		cb->Bind(eShaderStage::DS);
		cb->Bind(eShaderStage::GS);
		cb->Bind(eShaderStage::PS);
		cb->Bind(eShaderStage::CS);
		
		graphics::GetDevice()->DrawIndexed(mesh->GetIndexCount(), 0, 0);
	}
}