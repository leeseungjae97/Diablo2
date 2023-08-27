#include "mDrawMaterials.h"
#include "mTransform.h"
#include "mGameObject.h"

namespace m
{
	DrawMaterials::DrawMaterials()
		: MeshRenderer()
		, mDrawMats(nullptr)
	{
		mDrawMats = new graphics::StructuredBuffer();
		mDrawMats->Create(sizeof(DrawObject), 1, eViewType::SRV, nullptr, true);
	}

	DrawMaterials::~DrawMaterials()
	{
		if (mDrawMats)
		{
			delete mDrawMats;
			mDrawMats = nullptr;
		}
	}

	void DrawMaterials::Initialize()
	{
	}

	void DrawMaterials::Update()
	{
		//배운 스킬 위치저장, 배우지 않은 스킬 0, 0
		//불러올때 skillMatPos[y * 10  + x] == Vector2(0.f, 0.f) continue;
	
	}

	void DrawMaterials::LateUpdate()
	{
		
		//std::vector<DrawObject> objs;
		//for (int i = 0; i < mats.size(); ++i)
		//{
		//	DrawObject dObj;
		//	Vector4 pos = Vector4(poss[i].x, poss[i].y, GET_POS(GetOwner()).z, 0.f);
		//	dObj.position = pos;
		//	dObj.size = Vector2(30.f, 30.f);
		//	objs.push_back(dObj);
		//}
		//mDrawMats->SetData(objs.data(), objs.size());
	}

	void DrawMaterials::Render()
	{
		//if (GetOwner()->GetState() != GameObject::eState::RenderUpdate)
		//{
		//	for (int i = 0; i < mats.size(); ++i)
		//	{
		//		if (poss[i] == Vector2(0.f, 0.f)) continue;
		//		mats[i]->Clear();
		//	}
		//}
		//else
		//{
		//	
		//	std::shared_ptr<Mesh> pointMesh = Resources::Find<Mesh>(L"PointMesh");

		//	for (int i = 0; i < mats.size(); ++i)
		//	{
		//		if (poss[i] == Vector2(0.f, 0.f)) continue;
		//		pointMesh->BindBuffer();
		//		
		//		mats[i]->GetShader()->UseGS();
		//		mats[i]->Binds();

		//		pointMesh->RenderInstanced(1);
		//		mats[i]->Clear();
		//		mats[i]->GetShader()->CloseGS();
		//	}
		//	mDrawMats->BindSRV(eShaderStage::GS, 20);
		//}
		//mDrawMats->Clear();
	}
}
