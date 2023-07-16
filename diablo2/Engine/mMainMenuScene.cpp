#include "mMainMenuScene.h"

#include "..\engine_source\mGameObject.h"
#include "..\engine_source\mTransform.h"
#include "..\engine_source\mMeshRenderer.h"
#include "..\engine_source\mCamera.h"
#include "..\engine_source\mSceneManager.h"
#include "..\engine_source\mFontWrapper.h"
#include "..\engine_source\mRenderer.h"


#include "mCameraScript.h"
#include "mButton.h"
#include "mBackground.h"
#include "mGridScript.h"

namespace m
{
	MainMenuScene::MainMenuScene()
	{}
	MainMenuScene::~MainMenuScene()
	{}
	void MainMenuScene::Initialize()
	{
		Scene::Initialize();
		GameObject* camera = new GameObject();
		//camera->SetName(L"Camera");
		AddGameObject(eLayerType::UI, camera);

		Vector2 ccp = Camera::GetCameraCenter();
		camera->GetComponent<Transform>()->SetPosition(Vector3(0.f, 0.f, -10.f));
		//camera->GetComponent<Transform>()->SetPosition(Vector3(0.f, 0.f, -1.f));
		camera->AddComponent<CameraScript>();
		SetSceneMainCamera(camera->AddComponent<Camera>());
		GetSceneMainCamera()->TurnLayerMask(eLayerType::UI, true);

		//GameObject* grid = new GameObject();
		//grid->SetName(L"Grid");
		//AddGameObject(eLayerType::Grid, grid);
		//MeshRenderer* mr = grid->AddComponent<MeshRenderer>();
		//grid->GetComponent<Transform>()->SetPosition(Vector3(-800.f, -450.f, 0.999f));
		//mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		//mr->SetMaterial(Resources::Find<Material>(L"GridMaterial"));
		//GridScript* gridSc = grid->AddComponent<GridScript>();
		//gridSc->SetCamera(cameraComp);

		Background* back = new Background();
		AddGameObject(eLayerType::UI, back);
		back->SetCamera(GetSceneMainCamera());
		back->GetComponent<MeshRenderer>()->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		back->GetComponent<MeshRenderer>()->SetMaterial(Resources::Find<Material>(L"mainMenu2"));
		back->GetComponent<Transform>()->SetPosition(Vector3(0.f, 0.f, 1.0f));
		//back->GetComponent<Transform>()->SetScale(Vector3(800.f * Texture::GetWidRatio(), 600.f * Texture::GetHeiRatio(), 0.f));
		back->GetComponent<Transform>()->SetScale(Vector3(RESOL_WID, RESOL_HEI, 0.f));					 

		Background* logo = new Background();
		AddGameObject(eLayerType::UI, logo);
		logo->SetCamera(GetSceneMainCamera());
		logo->GetComponent<MeshRenderer>()->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		logo->GetComponent<MeshRenderer>()->SetMaterial(Resources::Find<Material>(L"testLogo"));
		logo->GetComponent<Transform>()->SetPosition(Vector3(0.f, 450.f - (183.f * Texture::GetHeiRatio() / 2.f), 1.f));
		logo->GetComponent<Transform>()->SetScale(Vector3(365.f * Texture::GetWidRatio(), 183.f * Texture::GetHeiRatio(), 0.f));

		Button* btn1 = new Button();
		AddGameObject(eLayerType::UI, btn1);
		btn1->SetCamera(GetSceneMainCamera());
		btn1->GetComponent<MeshRenderer>()->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		btn1->GetComponent<MeshRenderer>()->SetMaterial(Resources::Find<Material>(L"mWideButtonBlank"));
		btn1->SetClickMaterial(Resources::Find<Material>(L"mWideButtonBlankClick"));
		btn1->SetNormalMaterial(Resources::Find<Material>(L"mWideButtonBlank"));
		btn1->SetCamera(GetSceneMainCamera());
		btn1->SetClickFunction(
			[]() { SceneManager::LoadScene(L"SelectCharacterScene"); }
		);
		btn1->GetComponent<Transform>()->SetPosition(Vector3(0.f, 450.f - (288.f * Texture::GetHeiRatio()) , 1.f));
		btn1->GetComponent<Transform>()->SetScale(Vector3(272.f * Texture::GetWidRatio(), 35.f * Texture::GetHeiRatio(), 0.0f));		

		UI* info1 = new UI();
		AddGameObject(eLayerType::UI, info1);
		info1->SetCamera(GetSceneMainCamera());
		info1->GetComponent<MeshRenderer>()->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		info1->GetComponent<MeshRenderer>()->SetMaterial(Resources::Find<Material>(L"tt1"));
		info1->GetComponent<Transform>()->SetScale(Vector3(150.f * Texture::GetWidRatio()
			, 40.f * Texture::GetHeiRatio(), 0.f));
		info1->GetComponent<Transform>()->SetPosition(Vector3(-800.f + 150.f * Texture::GetWidRatio() / 2.f
			, 450.f - 40.f * Texture::GetHeiRatio(), 1.f));

		//FontWrapper::DrawFont(L"TEST", 10, 10, 100, FONT_RGBA(255, 0, 255, 255));
	}
	void MainMenuScene::Update()
	{
		Scene::Update();
		if (Input::GetKeyDown(eKeyCode::N))
		{
			SceneManager::LoadScene(L"SelectCharacterScene");
		}
	}
	void MainMenuScene::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void MainMenuScene::Render()
	{
		Scene::Render();
	}
}