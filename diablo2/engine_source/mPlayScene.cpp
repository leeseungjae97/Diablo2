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
#include "mTile.h"

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

		float camerafX = mX;
		float camerafY = (float)(TILE_SIZE_Y * 5 + mY);

		Vector2 ccp = Camera::GetCameraCenter();

		camera->GetComponent<Transform>()->SetPosition(Vector3(camerafX, camerafY, -1.f));
		Camera* cameraComp = camera->AddComponent<Camera>();
		camera->AddComponent<CameraScript>();

		tiles.resize(5 * 5);

		float z = 5;

		for (int y = 0; y < 5; ++y)
		{
			for (int x = 0; x < 5; ++x)
			{
				float fX = (float)(TILE_SIZE_X * (x - y) + mX);
				float fY = (float)(TILE_SIZE_Y * (x + y) + mY);

				Tile* tile = new Tile(Vector3(fX, fY, z -= 0.01f), Vector2(x, y));

				AddGameObject(eLayerType::Player, tile);
				tile->GetComponent<MeshRenderer>()->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
				tile->GetComponent<MeshRenderer>()->SetMaterial(Resources::Find<Material>(L"testTile"));
				tile->GetComponent<Transform>()->SetScale(Vector3(TILE_SIZE_X * Texture::GetWidRatio(), TILE_SIZE_Y * Texture::GetHeiRatio(), 0.f));
				tiles.push_back(tile);
			}
		}

		Player* player = new Player(Vector3(camerafX, camerafY, 6.f));
		//player->SetName(L"Player");
		AddGameObject(eLayerType::Player, player);
		player->AddComponent<MeshRenderer>();
		player->GetComponent<MeshRenderer>()->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		player->GetComponent<MeshRenderer>()->SetMaterial(Resources::Find<Material>(L"testAmazon"));
		player->GetComponent<Transform>()->SetScale(Vector3(31.f * Texture::GetWidRatio(), 81.f * Texture::GetHeiRatio(), 0.f));
		//player->SetState();
	}
	void PlayScene::Update()
	{
		Scene::Update();
		if (Input::GetKeyDown(eKeyCode::N))
		{
			SceneManager::LoadScene(wsScenes[(UINT)eSceneType::MainMenuScene]);
		}
		if (Input::GetKeyDown(eKeyCode::M))
		{

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