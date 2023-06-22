#include "mPlayScene.h"
#include "mGameObject.h"
#include "mMeshRenderer.h"
#include "mTransform.h"
#include "mResources.h"
#include "mCameraScript.h"
#include "mCamera.h"

namespace m
{
	PlayScene::PlayScene()
	{}
	PlayScene::~PlayScene()
	{}
	void PlayScene::Initialize()
	{
		GameObject* player = new GameObject();
		//player->SetName(L"Player");
		AddGameObject(eLayerType::Player, player);
		MeshRenderer* mr = player->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"amazonAttack1"));
		player->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
		//player->AddComponent<CameraScript>();

		GameObject* player2 = new GameObject();
		AddGameObject(eLayerType::Player, player2);
		MeshRenderer* mr2 = player2->AddComponent<MeshRenderer>();
		mr2->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr2->SetMaterial(Resources::Find<Material>(L"amazonWalk"));
		player2->GetComponent<Transform>()->SetPosition(Vector3(3.0f, 1.0f, 0.0f));

		GameObject* camera = new GameObject();
		//camera->SetName(L"Camera");
		AddGameObject(eLayerType::Player, camera);
		camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -20.f));
		Camera* cameraComp = camera->AddComponent<Camera>();
		camera->AddComponent<CameraScript>();
	}
	void PlayScene::Update()
	{
		Scene::Update();
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