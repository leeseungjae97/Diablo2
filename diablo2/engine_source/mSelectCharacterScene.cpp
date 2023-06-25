#include "mSelectCharacterScene.h"
#include "mSceneManager.h"
#include "mCamera.h"
#include "mCameraScript.h"
#include "mTransform.h"
#include "mGameObject.h"
#include "mBackground.h"
#include "mMeshRenderer.h"
#include "mResources.h"

namespace m
{
	SelectCharacterScene::SelectCharacterScene()
	{}
	SelectCharacterScene::~SelectCharacterScene()
	{}
	void SelectCharacterScene::Initialize()
	{
		GameObject* camera = new GameObject();
		//camera->SetName(L"Camera");
		AddGameObject(eLayerType::Player, camera);
		Camera* cameraComp = camera->AddComponent<Camera>();
		camera->AddComponent<CameraScript>();

		Background* back = new Background();
		AddGameObject(eLayerType::UI, back);
		back->AddComponent<MeshRenderer>();
		back->GetComponent<MeshRenderer>()->SetMesh(Resources::Find<Mesh>(L"fullRectMesh"));
		back->GetComponent<MeshRenderer>()->SetMaterial(Resources::Find<Material>(L"characterSelect1"));

		back->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.f, 0.0f));
		back->GetComponent<Transform>()->SetRotation(Vector3(0.0f, 0.0, 0.0f));
		back->GetComponent<Transform>()->SetScale(Vector3(4.f, 2.6f, 1.0f));
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