#include "guiEditor.h"

#include "guiDockspace.h"
#include "../engine_source/mMesh.h"
#include "../engine_source/mResources.h"
#include "../engine_source/mTransform.h"
#include "../engine_source/mMeshRenderer.h"
#include "../engine_source/mMaterial.h"
#include "../engine_source/mRenderer.h"
#include "../engine_source/mSceneManager.h"
#include "../engine_source/mApplication.h"

#include "guiGameView.h"
#include "mGridScript.h"

extern m::Application application;

namespace gui
{
	using namespace m::enums;
	using namespace m;
	std::map<std::wstring, Widget*> Editor::mWidgets = {};
	std::vector<EditorObject*> Editor::mEditorObjects = {};
	std::vector<DebugObject*> Editor::mDebugObjects = {};
	bool Editor::noRender = false;
	Dockspace* Editor::mDockspace = nullptr;
	ImGuiIO Editor::mIO = {};

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

		mesh = Resources::Find<Mesh>(L"DebugCircle");
		material = Resources::Find<Material>(L"DebugMaterial");

		mDebugObjects[(UINT)eColliderType::Circle] = new DebugObject();
		mDebugObjects[(UINT)eColliderType::Circle]->AddComponent<Transform>();
		mr = mDebugObjects[(UINT)eColliderType::Circle]->AddComponent<MeshRenderer>();
		mr->SetMaterial(material);
		mr->SetMesh(mesh);

		mDebugObjects[(UINT)eColliderType::Dot] = new DebugObject();
		mDebugObjects[(UINT)eColliderType::Dot]->AddComponent<Transform>();
		mr = mDebugObjects[(UINT)eColliderType::Dot]->AddComponent<MeshRenderer>();
		mr->SetMaterial(material);
		mr->SetMesh(mesh);

		//EditorObject* grid = new EditorObject();
		//grid->SetName(L"Grid");
		////Transform* ttt = grid->AddComponent<Transform>();
		////ttt->SetPosition(Vector3(0.f, 0.f, 2.0f));
		//mr = grid->AddComponent<MeshRenderer>();
		//mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		//mr->SetMaterial(Resources::Find<Material>(L"GridMaterial"));
		////SET_POS_XYZ()
		//GridScript* gridSc = grid->AddComponent<GridScript>();
		//gridSc->SetCamera(renderer::cameras[0]);

		//mEditorObjects.push_back(grid);

		//imguiInit();

		//mDockspace = new Dockspace();
		//mWidgets.insert(std::make_pair(L"mDockSpace", mDockspace));
		//mDockspace->SetName("mDockSpace");


		//GameView* game = new GameView();
		//mWidgets.insert(std::make_pair(L"GameView", game));
		//game->SetName("GameView");
	}
	void Editor::Run()
	{
		if(Input::GetKeyUp(eKeyCode::S))
		{
			noRender = noRender ? false : true;
		}
		Update();
		LateUpdate();
		if(!noRender)
			Render();
		else renderer::debugMeshs.clear();

		//imguiRender();
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
		for (const DebugMesh& mesh : renderer::debugMeshs)
		{
			DebugRender(mesh);
		}
		for (EditorObject* obj : mEditorObjects)
		{
			obj->Render();
		}
		renderer::debugMeshs.clear();
	}
	void Editor::Release()
	{
		for (auto widget : mWidgets)
		{
			delete widget.second;
			widget.second = nullptr;
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
		//imguiRelease();
	}

	void Editor::DebugRender(const DebugMesh& mesh)
	{
		if (!mesh.visible) return;

		DebugObject* debugObj = mDebugObjects[(UINT)mesh.type];

		// 위치 크기 회전 정보를 받아와서
		// 해당 게임오브젝트위에 그려주면된다.
		Transform* tr = debugObj->GetComponent<Transform>();

		Vector3 pos = mesh.position;
		pos.z -= 0.01f;

		tr->SetPosition(pos);
		tr->SetScale(mesh.scale);
		tr->SetRotation(mesh.rotation);
		if (mesh.type == eColliderType::Rect)
		{
			if (mesh.color == eColor::Red)
			{
				debugObj->GetComponent<MeshRenderer>()->SetMesh(Resources::Find<Mesh>(L"DebugRedRect"));
			}
			else if (mesh.color == eColor::Green)
			{
				debugObj->GetComponent<MeshRenderer>()->SetMesh(Resources::Find<Mesh>(L"DebugRect"));
			}
		}
		else if(mesh.type ==eColliderType::Circle
			|| mesh.type == eColliderType::Dot)
		{
			if (mesh.color == eColor::Red)
			{
				debugObj->GetComponent<MeshRenderer>()->SetMesh(Resources::Find<Mesh>(L"DebugRedCircle"));
			}
			else if (mesh.color == eColor::Green)
			{
				debugObj->GetComponent<MeshRenderer>()->SetMesh(Resources::Find<Mesh>(L"DebugCircle"));
			}
		}
		

		Camera* mainCamara = renderer::mainCamera;
		Camera::SetViewMatrix(mesh.view);
		Camera::SetProjectionMatrix(mesh.projection);

		
		if (mesh.visible)
		{
			tr->LateUpdate();
			debugObj->Render();
		}
	}

    void Editor::imguiInit()
    {
		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows
		//io.ConfigViewportsNoAutoMerge = true;
		//io.ConfigViewportsNoTaskBarIcon = true;
		//io.ConfigViewportsNoDefaultParent = true;
		//io.ConfigDockingAlwaysTabBar = true;
		//io.ConfigDockingTransparentPayload = true;
		//io.ConfigFlags |= ImGuiConfigFlags_DpiEnableScaleFonts;     // FIXME-DPI: Experimental. THIS CURRENTLY DOESN'T WORK AS EXPECTED. DON'T USE IN USER APP!
		//io.ConfigFlags |= ImGuiConfigFlags_DpiEnableScaleViewports; // FIXME-DPI: Experimental.

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsLight();

		// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		// Setup Platform/Renderer backends
		ImGui_ImplWin32_Init(application.GetHwnd());
		ImGui_ImplDX11_Init(m::graphics::GetDevice()->GetID3D11Device()
			, m::graphics::GetDevice()->GetID3D11DeviceContext());

		// Load Fonts
		// - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
		// - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
		// - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
		// - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
		// - Use '#define IMGUI_ENABLE_FREETYPE' in your imconfig file to use Freetype for higher quality font rendering.
		// - Read 'docs/FONTS.md' for more instructions and details.
		// - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
		//io.Fonts->AddFontDefault();
		//io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf", 18.0f);
		//io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
		//io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
		//io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
		//ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
		//IM_ASSERT(font != NULL);

		// Our state
		bool show_demo_window = true;
		bool show_another_window = false;
		ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    }

    void Editor::imguiRender()
    {

		//Microsoft::WRL::ComPtr<ID3D11DepthStencilState> ds
		//	= renderer::depthStencilStates[(UINT)ya::graphics::eDSType::Less];
		//ya::graphics::GetDevice()->BindDepthStencilState(ds.Get());

		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		bool show_demo_window = true;

		mDockspace->Render();
		for (auto& widget : mWidgets)
		{
			widget.second->Render();
		}

		if (show_demo_window)
			ImGui::ShowDemoWindow(&show_demo_window);

		// Rendering
		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

		// Update and Render additional Platform Windows
		if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
		}
    }

    void Editor::imguiRelease()
    {
		ImGui_ImplDX11_Shutdown();
		ImGui_ImplWin32_Shutdown();
		ImGui::DestroyContext();
    }
}
