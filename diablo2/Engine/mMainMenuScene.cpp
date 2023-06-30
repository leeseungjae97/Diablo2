#include "mMainMenuScene.h"

#include "..\engine_source\mGameObject.h"
#include "..\engine_source\mTransform.h"
#include "..\engine_source\mMeshRenderer.h"
#include "..\engine_source\mCamera.h"
#include "..\engine_source\mSceneManager.h"

#include "mCameraScript.h"
#include "mButton.h"
#include "mBackground.h"
namespace m
{
	MainMenuScene::MainMenuScene()
	{}
	MainMenuScene::~MainMenuScene()
	{}
	void MainMenuScene::Initialize()
	{
		GameObject* camera = new GameObject();
		//camera->SetName(L"Camera");
		AddGameObject(eLayerType::Player, camera);

		Vector2 ccp = Camera::GetCameraCenter();
		camera->GetComponent<Transform>()->SetPosition(Vector3(ccp.x, ccp.y, -1.f));
		camera->AddComponent<CameraScript>();
		Camera* cameraComp = camera->AddComponent<Camera>();
		cameraComp->TurnLayerMask(eLayerType::Player, true);

		Background* back = new Background();
		AddGameObject(eLayerType::Player, back);
		back->AddComponent<MeshRenderer>();
		back->GetComponent<MeshRenderer>()->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		back->GetComponent<MeshRenderer>()->SetMaterial(Resources::Find<Material>(L"mainMenu2"));
		back->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.f, 1.0f));
		back->GetComponent<Transform>()->SetScale(Vector3(1600.f, 900.f, 0.f));

		Background* logo = new Background();
		AddGameObject(eLayerType::Player, logo);
		logo->AddComponent<MeshRenderer>();
		logo->GetComponent<MeshRenderer>()->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		logo->GetComponent<MeshRenderer>()->SetMaterial(Resources::Find<Material>(L"testLogo"));
		logo->GetComponent<Transform>()->SetPosition(Vector3(ccp.x - 365.f * Texture::GetWidRatio() / 2.f, 0.f, 0.999f));
		logo->GetComponent<Transform>()->SetScale(Vector3(365.f * Texture::GetWidRatio(), 183.f * Texture::GetHeiRatio(), 0.f));

		Button* btn1 = new Button();
		AddGameObject(eLayerType::Player, btn1);
		btn1->AddComponent<MeshRenderer>();
		btn1->GetComponent<MeshRenderer>()->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		btn1->GetComponent<MeshRenderer>()->SetMaterial(Resources::Find<Material>(L"mWideButtonBlank"));
		btn1->SetClickMaterial(Resources::Find<Material>(L"mWideButtonBlankClick"));
		btn1->SetNormalMaterial(Resources::Find<Material>(L"mWideButtonBlank"));

		btn1->GetComponent<Transform>()->SetPosition(Vector3(ccp.x - 272.f * Texture::GetWidRatio() / 2.f, -290.f * Texture::GetHeiRatio(), 0.998f));
		btn1->GetComponent<Transform>()->SetScale(Vector3(272.f * Texture::GetWidRatio(), 35.f * Texture::GetHeiRatio(), 0.0f));
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