#include "mSelectCharacterScene.h"
#include "mSceneManager.h"
#include "mCamera.h"
#include "mCameraScript.h"
#include "mTransform.h"
#include "mGameObject.h"
#include "mBackground.h"
#include "mMeshRenderer.h"
#include "mResources.h"
#include "mButton.h"

namespace m
{
	SelectCharacterScene::SelectCharacterScene()
	{}
	SelectCharacterScene::~SelectCharacterScene()
	{}
	void SelectCharacterScene::Initialize()
	{
		Vector2 ccp = Camera::GetCameraCenter();

		GameObject* camera = new GameObject();
		//camera->SetName(L"Camera");
		AddGameObject(eLayerType::Player, camera);
		camera->GetComponent<Transform>()->SetPosition(Vector3(ccp.x, ccp.y, -1.0f));
		Camera* cameraComp = camera->AddComponent<Camera>();

		Background* back = new Background();
		AddGameObject(eLayerType::UI, back);
		back->AddComponent<MeshRenderer>();
		back->GetComponent<MeshRenderer>()->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		back->GetComponent<MeshRenderer>()->SetMaterial(Resources::Find<Material>(L"characterSelect1"));
		back->GetComponent<Transform>()->SetPosition(Vector3(0.f, 0.f, 1.f));
		back->GetComponent<Transform>()->SetScale(Vector3(1600.f, 900.f, 0.f));

		Background* fire = new Background();
		AddGameObject(eLayerType::UI, fire);
		fire->AddComponent<MeshRenderer>();
		fire->GetComponent<MeshRenderer>()->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		fire->GetComponent<MeshRenderer>()->SetMaterial(Resources::Find<Material>(L"characterSelect1"));
		fire->GetComponent<Transform>()->SetPosition(Vector3(0.f, 0.f, 1.f));
		fire->GetComponent<Transform>()->SetScale(Vector3(0.f, 0.f, 0.f));

		Background* amazon = new Background();
		AddGameObject(eLayerType::UI, amazon);
		amazon->AddComponent<MeshRenderer>();
		amazon->GetComponent<MeshRenderer>()->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		amazon->GetComponent<MeshRenderer>()->SetMaterial(Resources::Find<Material>(L"characterSelect1"));
		amazon->GetComponent<Transform>()->SetPosition(Vector3(0.f, 0.f, 1.f));
		amazon->GetComponent<Transform>()->SetScale(Vector3(0.f, 0.f, 0.f));

		Button* exitBtn = new Button();
		AddGameObject(eLayerType::UI, exitBtn);
		exitBtn->AddComponent<MeshRenderer>();
		exitBtn->GetComponent<MeshRenderer>()->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		exitBtn->GetComponent<MeshRenderer>()->SetMaterial(Resources::Find<Material>(L"mWideButtonBlank"));
		exitBtn->SetClickMaterial(Resources::Find<Material>(L"mWideButtonBlankClick"));
		exitBtn->SetNormalMaterial(Resources::Find<Material>(L"mWideButtonBlank"));

		exitBtn->GetComponent<Transform>()->SetPosition(Vector3(20.f, -870.f + 40.f * Texture::GetHeiRatio(), 0.998f));
		exitBtn->GetComponent<Transform>()->SetScale(Vector3(130.f * Texture::GetWidRatio(), 40.f * Texture::GetHeiRatio(), 0.0f));
	}
	void SelectCharacterScene::Update()
	{
		Scene::Update();
		if (Input::GetKeyDown(eKeyCode::N))
		{
			SceneManager::LoadScene(wsScenes[(UINT)eSceneType::PlayScene]);
		}
	}
	void SelectCharacterScene::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void SelectCharacterScene::Render()
	{
		Scene::Render();
	}
}