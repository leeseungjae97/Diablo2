#include "guiEditor.h"
#include "../engine_source/mMesh.h"
#include "../engine_source/mResources.h"
#include "../engine_source/mTransform.h"
#include "../engine_source/mMeshRenderer.h"
#include "../engine_source/mMaterial.h"
#include "../engine_source/mRenderer.h"
#include "../engine_source/mSceneManager.h"

#include "mGridScript.h"
namespace gui
{
	using namespace m::enums;
	using namespace m;
	std::vector<Widget*> Editor::mWidgets = {};
	std::vector<EditorObject*> Editor::mEditorObjects = {};
	std::vector<DebugObject*> Editor::mDebugObjects = {};

	void Editor::Initialize()
	{
		mDebugObjects.resize((UINT)eColliderType::End);

		std::shared_ptr<Mesh> mesh
			= Resources::Find<Mesh>(L"DebugRect");
		std::shared_ptr<Material> material
			= Resources::Find<Material>(L"DebugMaterial");

		mDebugObjects[(UINT)eColliderType::Rect] = new DebugObject();
		mDebugObjects[(UINT)eColliderType::Rect]->AddComponent<Transform>();
		MeshRenderer* mr
			= mDebugObjects[(UINT)eColliderType::Rect]->AddComponent<MeshRenderer>();
		mr->SetMaterial(material);
		mr->SetMesh(mesh);


		EditorObject* grid = new EditorObject();
		grid->SetName(L"Grid");
		mr = grid->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"GridMaterial"));
		GridScript* gridSc = grid->AddComponent<GridScript>();
		gridSc->SetCamera(renderer::cameras[0]);

		SceneManager::GetActiveScene();

		mEditorObjects.push_back(grid);
	}
	void Editor::Run()
	{
		Update();
		LateUpdate();
		Render();
	}
	void Editor::Update()
	{
		for (EditorObject* obj : mEditorObjects)
		{
			obj->Update();
		}
	}
	void Editor::LateUpdate()
	{
		for (EditorObject* obj : mEditorObjects)
		{
			obj->LateUpdate();
		}
	}
	void Editor::Render()
	{
		//Microsoft::WRL::ComPtr<ID3D11DepthStencilState> ds
		//	= renderer::depthStencilStates[(UINT)ya::graphics::eDSType::Less];
		//ya::graphics::GetDevice()->BindDepthStencilState(ds.Get());

		for (EditorObject* obj : mEditorObjects)
		{
			obj->Render();
		}

		for (const DebugMesh& mesh : renderer::debugMeshs)
		{
			DebugRender(mesh);
		}
		renderer::debugMeshs.clear();
	}
	void Editor::Release()
	{
		for (auto widget : mWidgets)
		{
			delete widget;
			widget = nullptr;
		}

		for (auto editorObj : mEditorObjects)
		{
			delete editorObj;
			editorObj = nullptr;
		}

		for (auto debugObj : mDebugObjects)
		{
			delete debugObj;
			debugObj = nullptr;
		}
	}

	void Editor::DebugRender(const DebugMesh& mesh)
	{
		DebugObject* debugObj = mDebugObjects[(UINT)mesh.type];


		// 위치 크기 회전 정보를 받아와서
		// 해당 게임오브젝트위에 그려주면된다.
		Transform* tr = debugObj->GetComponent<Transform>();

		Vector3 pos = mesh.position;
		pos.z -= 0.01f;

		tr->SetPosition(pos);
		tr->SetScale(mesh.scale);
		tr->SetRotation(mesh.rotation);

		Camera* mainCamara = renderer::mainCamera;
		Camera::SetViewMatrix(mainCamara->GetPrivateViewMatrix());
		Camera::SetProjectionMatrix(mainCamara->GetPrivateProjectionMatrix());

		tr->LateUpdate();

		/*ya::MeshRenderer * mr
			= debugObj->GetComponent<ya::MeshRenderer>();*/
			// main camera
		
		debugObj->Render();
	}
}
