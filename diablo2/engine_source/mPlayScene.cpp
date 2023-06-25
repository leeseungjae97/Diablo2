#include "mPlayScene.h"
#include "mGameObject.h"
#include "mMeshRenderer.h"
#include "mTransform.h"
#include "mResources.h"
#include "mCameraScript.h"
#include "mCamera.h"
#include "mSceneManager.h"
#include "mBackground.h"
#include "mRenderer.h"
#include "mPlayer.h"

namespace m
{
	PlayScene::PlayScene()
	{}
	PlayScene::~PlayScene()
	{}
	void PlayScene::Initialize()
	{
		GameObject* camera = new GameObject();
		//camera->SetName(L"Camera");
		AddGameObject(eLayerType::Player, camera);

		float TILE_SIZE_X = 160.f;
		float TILE_SIZE_Y = 80.f;


		float mX = (10.f * (TILE_SIZE_X / 2.f));
		float mY = TILE_SIZE_Y / 4.f;

		float camerafX = (float)(mX);
		float camerafY = (float)(TILE_SIZE_Y * 4 + mY);

		camera->GetComponent<Transform>()->SetPosition(Vector3(camerafX, camerafY, -1.f));
		Camera* cameraComp = camera->AddComponent<Camera>();
		camera->AddComponent<CameraScript>();

		for (int y = 4; y >= 0; y--)
		{
			for (int x = 4; x >= 0; x--)
			{
				
				Background* tile = new Background();
				AddGameObject(eLayerType::Tile, tile);
				tile->AddComponent<MeshRenderer>();
				tile->GetComponent<MeshRenderer>()->SetMesh(Resources::Find<Mesh>(L"fullRectMesh"));
				tile->GetComponent<MeshRenderer>()->SetMaterial(Resources::Find<Material>(L"testTile"));
				tile->GetComponent<Transform>()->SetScale(Vector3(160.f, 80.f, 0.f));

				float fX = (float)((TILE_SIZE_X) * (x - y) + mX);
				float fY = (float)((TILE_SIZE_Y) * (x + y) + mY);

				tile->GetComponent<Transform>()->SetPosition(Vector3(fX, fY, 0.f));
			}
		}


		Player* player = new Player();
		//player->SetName(L"Player");
		AddGameObject(eLayerType::Player, player);
		MeshRenderer* mr = player->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"testAmazon"));
		player->GetComponent<Transform>()->SetPosition(Vector3(camerafX, camerafY, 0.f));
		player->GetComponent<Transform>()->SetScale(Vector3(31.f * 2, 81.f * 2, 0.f));

		

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