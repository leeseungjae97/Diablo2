//#include "mSelectCharacterScene.h"
//#include "mSceneManager.h"
//#include "mCamera.h"
//#include "mCameraScript.h"
//#include "mTransform.h"
//#include "mGameObject.h"
//#include "mBackground.h"
//#include "mMeshRenderer.h"
//#include "mResources.h"
//
//namespace m
//{
//	SelectCharacterScene::SelectCharacterScene()
//	{}
//	SelectCharacterScene::~SelectCharacterScene()
//	{}
//	void SelectCharacterScene::Initialize()
//	{
//		Vector2 ccp = Camera::GetCameraCenter();
//
//		GameObject* camera = new GameObject();
//		//camera->SetName(L"Camera");
//		AddGameObject(eLayerType::Player, camera);
//		camera->GetComponent<Transform>()->SetPosition(Vector3(ccp.x, ccp.y, -1.0f));
//		Camera* cameraComp = camera->AddComponent<Camera>();
//
//		Background* back = new Background();
//		AddGameObject(eLayerType::UI, back);
//		back->AddComponent<MeshRenderer>();
//		back->GetComponent<MeshRenderer>()->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
//		back->GetComponent<MeshRenderer>()->SetMaterial(Resources::Find<Material>(L"charactercreationTest"));
//		back->GetComponent<Transform>()->SetScale(Vector3(1600.f, 900.f, 0.f));
//		back->GetComponent<Transform>()->SetUseRatio(false);
//	}
//	void SelectCharacterScene::Update()
//	{
//		Scene::Update();
//		if (Input::GetKeyDown(eKeyCode::N))
//		{
//			SceneManager::LoadScene(wsScenes[(UINT)eSceneType::PlayScene]);
//		}
//	}
//	void SelectCharacterScene::LateUpdate()
//	{
//		Scene::LateUpdate();
//	}
//	void SelectCharacterScene::Render()
//	{
//		Scene::Render();
//	}
//}