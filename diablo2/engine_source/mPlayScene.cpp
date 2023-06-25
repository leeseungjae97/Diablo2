#include "mPlayScene.h"
#include "mGameObject.h"
#include "mMeshRenderer.h"
#include "mTransform.h"
#include "mResources.h"
#include "mCameraScript.h"
#include "mCamera.h"
#include "mSceneManager.h"
#include "mBackground.h"

namespace m
{
	PlayScene::PlayScene()
	{}
	PlayScene::~PlayScene()
	{}
	void PlayScene::Initialize()
	{
		//GameObject* player = new GameObject();
		////player->SetName(L"Player");
		//AddGameObject(eLayerType::Player, player);
		//MeshRenderer* mr = player->AddComponent<MeshRenderer>();
		//mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		//mr->SetMaterial(Resources::Find<Material>(L"amazonAttack1"));
		//player->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
		////player->AddComponent<CameraScript>();

		//GameObject* player2 = new GameObject();
		//AddGameObject(eLayerType::Player, player2);
		//MeshRenderer* mr2 = player2->AddComponent<MeshRenderer>();
		//mr2->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		//mr2->SetMaterial(Resources::Find<Material>(L"amazonWalk"));
		//player2->GetComponent<Transform>()->SetPosition(Vector3(3.0f, 1.0f, 0.0f));
		
		GameObject* camera = new GameObject();
		//camera->SetName(L"Camera");
		AddGameObject(eLayerType::Player, camera);
		//camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -1.f));
		Camera* cameraComp = camera->AddComponent<Camera>();
		camera->AddComponent<CameraScript>();


		Background* floors = new Background();
		AddGameObject(eLayerType::UI, floors);
		floors->AddComponent<MeshRenderer>();
		floors->GetComponent<MeshRenderer>()->SetMesh(Resources::Find<Mesh>(L"fullRectMesh"));
		floors->GetComponent<MeshRenderer>()->SetMaterial(Resources::Find<Material>(L"townFloors"));

		floors->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.f, 0.0f));
		floors->GetComponent<Transform>()->SetRotation(Vector3(0.0f, 0.0, 0.0f));
		floors->GetComponent<Transform>()->SetScale(Vector3(4.f, 2.6f, 1.0f));


		// 800 / 5
		// 2959 / 37


	}
	void PlayScene::Update()
	{
		Scene::Update();
		if (Input::GetKeyDown(eKeyCode::N))
		{
			SceneManager::LoadScene(wsScenes[(UINT)eSceneType::MainMenuScene]);
		}
	}
	void PlayScene::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void PlayScene::Render()
	{
		Scene::Render();
	}
}