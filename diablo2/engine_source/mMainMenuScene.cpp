#include "mMainMenuScene.h"
#include "mGameObject.h"
#include "mTransform.h"
#include "mBackground.h"
#include "mMeshRenderer.h"
#include "mButton.h"
#include "mCamera.h"
#include "mCameraScript.h"
namespace m
{
	MainMenuScene::MainMenuScene()
	{}
	MainMenuScene::~MainMenuScene()
	{}
	void MainMenuScene::Initialize()
	{
		//GameObject* camera = new GameObject();
		////camera->SetName(L"Camera");
		//AddGameObject(eLayerType::Player, camera);
		//camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -1.f));
		//Camera* cameraComp = camera->AddComponent<Camera>();
		//camera->AddComponent<CameraScript>();

		Background* back = new Background();
		AddGameObject(eLayerType::UI, back);
		back->AddComponent<MeshRenderer>();
		back->GetComponent<MeshRenderer>()->SetMesh(Resources::Find<Mesh>(L"fullRectMesh"));
		back->GetComponent<MeshRenderer>()->SetMaterial(Resources::Find<Material>(L"mainMenu1"));

		back->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.f, 0.0f));
		back->GetComponent<Transform>()->SetRotation(Vector3(0.0f, 0.0, 0.0f));
		back->GetComponent<Transform>()->SetScale(Vector3(1.0f, 1.0f, 0.0f));

		//Button* btn1 = new Button();
		//AddGameObject(eLayerType::UI, btn1);
		//btn1->AddComponent<MeshRenderer>();
		//btn1->GetComponent<MeshRenderer>()->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		//btn1->GetComponent<MeshRenderer>()->SetMaterial(Resources::Find<Material>(L"tabBt"));
		//btn1->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
		//btn1->GetComponent<Transform>()->SetScale(Vector3(10.0f, 50.0f, 0.0f));
	}
	void MainMenuScene::Update()
	{
		Scene::Update();
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