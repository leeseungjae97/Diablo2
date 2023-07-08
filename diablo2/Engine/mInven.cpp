#include "mInven.h"

#include "..\engine_source\mMeshRenderer.h"
#include "..\engine_source\mResources.h"
namespace m
{
	Inven::Inven()
	{
		MeshRenderer* invenMr = AddComponent<MeshRenderer>();
		invenMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		invenMr->SetMaterial(Resources::Find<Material>(L"invenRect"));
	}
	Inven::~Inven()
	{}
	void Inven::Initialize()
	{
		UI::Initialize();
	}
	void Inven::Update()
	{
		UI::Update();
	}
	void Inven::LateUpdate()
	{
		UI::LateUpdate();
	}
	void Inven::Render()
	{
		UI::Render();
	}
}