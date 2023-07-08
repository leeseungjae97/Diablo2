#include "mPlayScene.h"

#include "..\engine_source\mGameObject.h"
#include "..\engine_source\mMeshRenderer.h"
#include "..\engine_source\mTransform.h"
#include "..\engine_source\mResources.h"
#include "..\engine_source\mCamera.h"
#include "..\engine_source\mSceneManager.h"
#include "..\engine_source\mRenderer.h"
#include "..\engine_source\mApplication.h"

#include "mCameraScript.h"
#include "mBackground.h"
#include "mPlayer.h"
#include "mTile.h"
#include "mButton.h"
#include "mInventory.h"
#include "mInvenItem.h"
#include "mGridScript.h"

extern m::Application application;
namespace m
{
	PlayScene::PlayScene()
	{

	}
	PlayScene::~PlayScene()
	{}
	void PlayScene::Initialize()
	{
		Scene::Initialize();
		GameObject* camera = new GameObject();
		//camera->SetName(L"Camera");
		AddGameObject(eLayerType::Player, camera);

		float TILE_SIZE_X = 160.f;
		float TILE_SIZE_Y = 80.f;

		for (int y = 0; y < 10; ++y)
		{
			for (int x = 0; x < 10; ++x)
			{
				float fX = (float)(TILE_SIZE_X * (x - y)) / 2.f;
				float fY = (float)(TILE_SIZE_Y * (x + y)) / 2.f;

				//float fX = (float)(TILE_SIZE_X * (x - y));
				//float fY = (float)(TILE_SIZE_Y * (x + y)); 

				Tile* tile = new Tile(Vector2(x, y));

				AddGameObject(eLayerType::Player, tile);
				tile->GetComponent<MeshRenderer>()->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
				tile->GetComponent<MeshRenderer>()->SetMaterial(Resources::Find<Material>(L"testTile"));
				tile->GetComponent<Transform>()->SetScale(Vector3(TILE_SIZE_X , TILE_SIZE_Y , 0.f));
				tile->GetComponent<Transform>()->SetPosition(Vector3(fX, fY, 1.f));
				tiles.push_back(tile);
			}
		}

		Vector3 cenVec = tiles[12]->GetComponent<Transform>()->GetPosition();

		//camera->GetComponent<Transform>()->SetPosition(Vector3(cenVec.x, cenVec.y, -1.f));
		camera->GetComponent<Transform>()->SetPosition(Vector3(0.f, 0.f, -10.f));
		Camera* cameraComp = camera->AddComponent<Camera>();
		cameraComp->DisableLayerMasks();
		cameraComp->TurnLayerMask(eLayerType::Player, true);
		camera->AddComponent<CameraScript>();
		//camera->AddComponent<GridScript>();

		Player* player = new Player(Vector3(0.f, 0.f, 1.f));
		player->SetCamera(cameraComp);
		AddGameObject(eLayerType::Player, player);
		player->AddComponent<MeshRenderer>();
		player->GetComponent<MeshRenderer>()->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		player->GetComponent<MeshRenderer>()->SetMaterial(Resources::Find<Material>(L"testAmazon"));
		player->GetComponent<Transform>()->SetScale(Vector3(31.f, 80.f, 0.f));

		cameraComp->SetFollowObject(player);

		//GameObject* child = new GameObject();
		//child->SetCamera(cameraComp);
		//AddGameObject(eLayerType::Player, child);
		//child->AddComponent<MeshRenderer>();
		//child->GetComponent<MeshRenderer>()->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		//child->GetComponent<MeshRenderer>()->SetMaterial(Resources::Find<Material>(L"testAmazon"));

		//child->GetComponent<Transform>()->SetScale(Vector3(31.f, 80.f, 0.f));
		//child->GetComponent<Transform>()->SetPosition(Vector3(1.f, 0.f, -1.f));
		//child->GetComponent<Transform>()->SetParent(player->GetComponent<Transform>());

		//float radian = math::DegreeToRadian(90.f);
		//player->GetComponent<Transform>()->SetRotation(0.f, 0.f, radian);

		GameObject* uiCamera = new GameObject();
		uiCamera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -1.f));
		Camera* cameraComp2 = uiCamera->AddComponent<Camera>();
		cameraComp2->TurnLayerMask(eLayerType::Player, false);
		//cameraComp2->TurnLayerMask(eLayerType::UI, true);
		//cameraComp2->TurnLayerMask(eLayerType::Item, true);

		AddGameObject(eLayerType::UI, uiCamera);


		inven = new Inventory(cameraComp2);
		inven->SetState(GameObject::Invisible);

		UI* uiBottomBar = new UI();
		AddGameObject(eLayerType::UI, uiBottomBar);
		uiBottomBar->AddComponent<MeshRenderer>();
		uiBottomBar->GetComponent<MeshRenderer>()->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		uiBottomBar->GetComponent<MeshRenderer>()->SetMaterial(Resources::Find<Material>(L"bottomUi"));
		uiBottomBar->GetComponent<Transform>()->SetScale(Vector3(470.f * Texture::GetWidRatio()
			, 104.f * Texture::GetHeiRatio(), 0.f));
		uiBottomBar->GetComponent<Transform>()->SetPosition(Vector3(0.f
			, -450 + 104.f * Texture::GetHeiRatio() / 2.f, -1.f));

		UI* uiMp = new UI();
		AddGameObject(eLayerType::UI, uiMp);
		uiMp->AddComponent<MeshRenderer>();
		uiMp->GetComponent<MeshRenderer>()->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		uiMp->GetComponent<MeshRenderer>()->SetMaterial(Resources::Find<Material>(L"mpUi"));
		uiMp->GetComponent<Transform>()->SetScale(Vector3(117.f * Texture::GetWidRatio()
													, 104.f * Texture::GetHeiRatio(), 0.f));
		uiMp->GetComponent<Transform>()->SetPosition(Vector3(800.f - 117.f * Texture::GetWidRatio() / 2.f
			, -450.f + 104.f * Texture::GetHeiRatio() / 2.f, -1.f));

	
		UI* mp = new UI();
		AddGameObject(eLayerType::UI, mp);
		mp->AddComponent<MeshRenderer>();
		mp->GetComponent<MeshRenderer>()->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mp->GetComponent<MeshRenderer>()->SetMaterial(Resources::Find<Material>(L"mp"));
		mp->GetComponent<Transform>()->SetScale(Vector3(80.f * Texture::GetWidRatio()
			, 80.f * Texture::GetHeiRatio(), 0.f));
		mp->GetComponent<Transform>()->SetPosition(Vector3(800.f - 140.f * Texture::GetWidRatio() / 2.f
			, -450.f + 105.f * Texture::GetHeiRatio() / 2.f, -1.f));


		UI* mpOverlapHands = new UI();
		AddGameObject(eLayerType::UI, mpOverlapHands);
		mpOverlapHands->AddComponent<MeshRenderer>();
		mpOverlapHands->GetComponent<MeshRenderer>()->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mpOverlapHands->GetComponent<MeshRenderer>()->SetMaterial(Resources::Find<Material>(L"mpOverlapHands"));
		mpOverlapHands->GetComponent<Transform>()->SetScale(Vector3(82.f * Texture::GetWidRatio()
			, 88.f * Texture::GetHeiRatio(), 0.f));
		mpOverlapHands->GetComponent<Transform>()->SetPosition(Vector3(800.f - 135.f * Texture::GetWidRatio() / 2.f
			, -450.f + 105.f * Texture::GetHeiRatio() / 2.f, -1.f));


		UI* uiHp = new UI();
		AddGameObject(eLayerType::UI, uiHp);
		uiHp->AddComponent<MeshRenderer>();
		uiHp->GetComponent<MeshRenderer>()->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		uiHp->GetComponent<MeshRenderer>()->SetMaterial(Resources::Find<Material>(L"hpUi"));
		uiHp->GetComponent<Transform>()->SetScale(Vector3(117.f * Texture::GetWidRatio()
			, 104.f * Texture::GetHeiRatio(), 0.f));
		uiHp->GetComponent<Transform>()->SetPosition(Vector3(-800.f + 117.f * Texture::GetWidRatio() / 2.f
			, -450.f + 105.f * Texture::GetHeiRatio() / 2.f, -1.f));

		UI* hp = new UI();
		AddGameObject(eLayerType::UI, hp);
		hp->AddComponent<MeshRenderer>();
		hp->GetComponent<MeshRenderer>()->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		hp->GetComponent<MeshRenderer>()->SetMaterial(Resources::Find<Material>(L"hp"));
		hp->GetComponent<Transform>()->SetScale(Vector3(80.f * Texture::GetWidRatio()
			, 80.f * Texture::GetHeiRatio(), 0.f));
		hp->GetComponent<Transform>()->SetPosition(Vector3(-800.f + 138.f * Texture::GetWidRatio() / 2.f
			, -450.f + 105.f * Texture::GetHeiRatio() / 2.f, -1.f));


		UI* hpOverlapHands = new UI();
		AddGameObject(eLayerType::UI, hpOverlapHands);
		hpOverlapHands->AddComponent<MeshRenderer>();
		hpOverlapHands->GetComponent<MeshRenderer>()->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		hpOverlapHands->GetComponent<MeshRenderer>()->SetMaterial(Resources::Find<Material>(L"hpOverlapHands"));
		hpOverlapHands->GetComponent<Transform>()->SetScale(Vector3(82.f * Texture::GetWidRatio()
			, 88.f * Texture::GetHeiRatio(), 0.f));
		hpOverlapHands->GetComponent<Transform>()->SetPosition(Vector3(-800.f + 137.f * Texture::GetWidRatio() / 2.f
			, -450.f + 97.f * Texture::GetHeiRatio() / 2.f, -1.f));

		//UI* info1 = new UI();
		//AddGameObject(eLayerType::UI, info1);
		//info1->AddComponent<MeshRenderer>();
		//info1->GetComponent<MeshRenderer>()->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		//info1->GetComponent<MeshRenderer>()->SetMaterial(Resources::Find<Material>(L"tt2"));
		//info1->GetComponent<Transform>()->SetScale(Vector3(100.f * Texture::GetWidRatio()
		//	, 50.f * Texture::GetHeiRatio(), 0.f));
		//info1->GetComponent<Transform>()->SetPosition(Vector3(-400.f
		//	, -200.f, -1.f));

		Button* skillShortCut1 = new Button();
		AddGameObject(eLayerType::UI, skillShortCut1);
		skillShortCut1->AddComponent<MeshRenderer>();
		skillShortCut1->GetComponent<MeshRenderer>()->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		skillShortCut1->GetComponent<MeshRenderer>()->SetMaterial(Resources::Find<Material>(L"frozenOrbIcon"));
		skillShortCut1->SetClickMaterial(Resources::Find<Material>(L"frozenOrbClickIcon"));
		skillShortCut1->SetNormalMaterial(Resources::Find<Material>(L"frozenOrbIcon"));
		skillShortCut1->SetCamera(cameraComp2);
		skillShortCut1->GetComponent<Transform>()->SetScale(Vector3(48.f * Texture::GetWidRatio()
			, 48.f* Texture::GetHeiRatio(), 0.f));
		skillShortCut1->GetComponent<Transform>()->SetPosition(Vector3(-470.f - 48.f * Texture::GetWidRatio() / 2.f
			, -450.f + 48.f * Texture::GetHeiRatio() / 2.f, -1.f));

		Button* skillShortCut2 = new Button();
		AddGameObject(eLayerType::UI, skillShortCut2);
		skillShortCut2->AddComponent<MeshRenderer>();
		skillShortCut2->GetComponent<MeshRenderer>()->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		skillShortCut2->GetComponent<MeshRenderer>()->SetMaterial(Resources::Find<Material>(L"thunderStormIcon"));
		skillShortCut2->SetClickMaterial(Resources::Find<Material>(L"thunderStormClickicon"));
		skillShortCut2->SetNormalMaterial(Resources::Find<Material>(L"thunderStormIcon"));
		skillShortCut2->SetCamera(cameraComp2);
		skillShortCut2->GetComponent<Transform>()->SetScale(Vector3(48.f * Texture::GetWidRatio()
			, 48.f * Texture::GetHeiRatio(), 0.f));
		skillShortCut2->GetComponent<Transform>()->SetPosition(Vector3(470.f + 48.f * Texture::GetWidRatio() / 2.f
			, -450.f + 48.f * Texture::GetHeiRatio() / 2.f, -1.f));


		//GameObject* gridCamera = new GameObject();
		//gridCamera->GetComponent<Transform>()->SetPosition(Vector3(Camera::GetCameraCenter().x, Camera::GetCameraCenter().y, -1.f));
		//Camera* cameraComp3 = gridCamera->AddComponent<Camera>();
		//cameraComp3->DisableLayerMasks();
		//cameraComp3->TurnLayerMask(eLayerType::Grid, true);

		//AddGameObject(eLayerType::UI, gridCamera);

		GameObject* grid = new GameObject();
		grid->SetName(L"Grid");
		AddGameObject(eLayerType::Grid, grid);
		MeshRenderer* mr = grid->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"GridMaterial"));
		GridScript* gridSc = grid->AddComponent<GridScript>();
		gridSc->SetCamera(cameraComp);
	}
	void PlayScene::Update()
	{
		Scene::Update();
		if (Input::GetKeyDown(eKeyCode::N))
		{
			SceneManager::LoadScene(L"MainMenuScene");
		}
		if (Input::GetKeyDown(eKeyCode::I))
		{
			inven->SetState(inven->GetState() != GameObject::eState::Active ? GameObject::eState::Active : GameObject::eState::Invisible);
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