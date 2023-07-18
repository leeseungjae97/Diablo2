#include "mPlayScene.h"

#include "..\engine_source\mGameObject.h"
#include "..\engine_source\mMeshRenderer.h"
#include "..\engine_source\mTransform.h"
#include "..\engine_source\mResources.h"
#include "..\engine_source\mCamera.h"
#include "..\engine_source\mSceneManager.h"
#include "..\engine_source\mRenderer.h"
#include "..\engine_source\mApplication.h"
#include "..\engine_source\mCollisionManager.h"

#include "mCameraScript.h"
#include "mBackground.h"
#include "mPlayer.h"
#include "mMonster.h"
#include "mTile.h"
#include "mButton.h"
#include "mItemPlaced.h"
#include "mInvenItem.h"
#include "mGridScript.h"
#include "mSkillUp.h"
#include "mCollider2D.h"
#include "mPlayerScript.h"

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
		SHARED_TEX tex;

		GameObject* camera = new GameObject();
		//camera->SetName(L"Camera");
		AddGameObject(eLayerType::Player, camera);
		SET_POS_XYZ(camera, 0.f, 0.f, -10.f);
		SetSceneMainCamera(ADD_COMP(camera, Camera));

		float TILE_SIZE_X = 160.f;
		float TILE_SIZE_Y = 80.f;

		for (int y = 0; y < 50; ++y)
		{
			for (int x = 0; x < 50; ++x)
			{
				float fX = (float)(TILE_SIZE_X * (x - y)) / 2.f;
				float fY = (float)(TILE_SIZE_Y * (x + y)) / 2.f;

				//float fX = (float)(TILE_SIZE_X * (x - y));
				//float fY = (float)(TILE_SIZE_Y * (x + y)); 

				Tile* tile = new Tile(Vector2(x, y));

				AddGameObject(eLayerType::Player, tile);
				//tile->AddComponent<Collider2D>();
				SET_MAIN_CAMERA(tile);
				SET_MESH(tile, L"RectMesh");
				SET_MATERIAL(tile, L"testTile");
				SET_SCALE_XYZ(tile, TILE_SIZE_X, TILE_SIZE_Y, 0.f);
				SET_POS_XYZ(tile, fX, fY, 1.f);
				tiles.push_back(tile);
			}
		}
		//camera->GetComponent<Transform>()->SetPosition(Vector3(cenVec.x, cenVec.y, -1.f));
		

		GetSceneMainCamera()->DisableLayerMasks();
		GetSceneMainCamera()->TurnLayerMask(eLayerType::Player, true);
		camera->AddComponent<CameraScript>();
		renderer::cameras.push_back(GetSceneMainCamera());
		//camera->AddComponent<GridScript>();

		Player* player = new Player(Vector3(0.f, 0.f, 1.f));
		SET_MAIN_CAMERA(player);
		AddGameObject(eLayerType::Player, player);
		
		ADD_COMP(player, PlayerScript);
		SET_MESH(player, L"RectMesh");
		SET_MATERIAL(player, L"testAmazon");
		SET_SCALE_XYZ(player, 31.f, 80.f, 0.f);

		float rad = math::DegreeToRadian(45.f);

		SET_ROTATION_XYZ(player, 0.f, 0.f, rad);

		GetSceneMainCamera()->SetFollowObject(player);

		Monster* monster = new Monster(Vector3(10.f, 10.f, 1.f));

		SET_MAIN_CAMERA(monster);
		AddGameObject(eLayerType::Player, monster);
		ADD_COMP(monster, Collider2D);
		ADD_COMP(monster, MeshRenderer);
		SET_MESH(monster, L"RectMesh");
		SET_MATERIAL(monster, L"testAmazon");
		GET_TEX_D(monster, tex);
		SET_SCALE_OWN_SIZE(monster, tex, 0.f);


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
		SET_POS_XYZ(uiCamera, 0.0f, 0.0f, -1.f);
		Camera* cameraComp2 = ADD_COMP(uiCamera, Camera);
		cameraComp2->TurnLayerMask(eLayerType::Player, false);
		
		//cameraComp2->TurnLayerMask(eLayerType::UI, true);
		//cameraComp2->TurnLayerMask(eLayerType::Item, true);

		AddGameObject(eLayerType::UI, uiCamera);


		inven = new ItemPlaced(cameraComp2);
		inven->SetState(GameObject::Invisible);

		skillUp = new SkillUp(cameraComp2);
		skillUp->SetState(GameObject::Invisible);

		UI* uiBottomBar = new UI();
		uiBottomBar->SetName(L"uiBottom");
		uiBottomBar->SetCamera(cameraComp2);
		AddGameObject(eLayerType::UI, uiBottomBar);
		SET_MESH(uiBottomBar, L"RectMesh");
		SET_MATERIAL(uiBottomBar, L"bottomUi");
		GET_TEX_D(uiBottomBar, tex);
		SET_SCALE_OWN_SIZE(uiBottomBar, tex, 0.f);
		SET_POS_XYZ(uiBottomBar, 0.f, -RESOL_H_HEI + 104.f * Texture::GetHeiRatio() / 2.f, -1.f);
		//uiBottomBar->GetComponent<Transform>()->SetScale(Vector3(470.f * Texture::GetWidRatio()
		//	, 104.f * Texture::GetHeiRatio(), 0.f));
		//uiBottomBar->GetComponent<Transform>()->SetPosition(Vector3());

		UI* uiMp = new UI();
		AddGameObject(eLayerType::UI, uiMp);
		uiMp->SetCamera(cameraComp2);
		SET_MESH(uiMp, L"RectMesh");
		SET_MATERIAL(uiMp, L"mpUi");
		GET_TEX_D(uiMp, tex);
		SET_SCALE_OWN_SIZE(uiMp, tex, 0.f);
		SET_POS_XYZ(uiMp, RESOL_H_WID - 117.f * Texture::GetWidRatio() / 2.f
					, -RESOL_H_HEI + 104.f * Texture::GetHeiRatio() / 2.f, -1.f);
		//uiMp->GetComponent<Transform>()->SetScale(Vector3(117.f * Texture::GetWidRatio()
		//											, 104.f * Texture::GetHeiRatio(), 0.f));
		//uiMp->GetComponent<Transform>()->SetPosition(Vector3(RESOL_H_WID - 117.f * Texture::GetWidRatio() / 2.f
		//	, -RESOL_H_HEI + 104.f * Texture::GetHeiRatio() / 2.f, -1.f));

	
		UI* mp = new UI();
		AddGameObject(eLayerType::UI, mp);
		mp->SetCamera(cameraComp2);
		SET_MESH(mp, L"RectMesh");
		SET_MATERIAL(mp, L"mp");
		GET_TEX_D(mp, tex);
		SET_SCALE_OWN_SIZE(mp, tex, 0.f);
		SET_POS_XYZ(mp, RESOL_H_WID - 140.f * Texture::GetWidRatio() / 2.f
					, -RESOL_H_HEI + 105.f * Texture::GetHeiRatio() / 2.f, -1.f);
		//mp->GetComponent<Transform>()->SetScale(Vector3(80.f * Texture::GetWidRatio()
		//	, 80.f * Texture::GetHeiRatio(), 0.f));
		//mp->GetComponent<Transform>()->SetPosition(Vector3(800.f - 140.f * Texture::GetWidRatio() / 2.f
		//	, -450.f + 105.f * Texture::GetHeiRatio() / 2.f, -1.f));


		UI* mpOverlapHands = new UI();
		AddGameObject(eLayerType::UI, mpOverlapHands);
		SET_MESH(mpOverlapHands, L"RectMesh");
		SET_MATERIAL(mpOverlapHands, L"mpOverlapHands");
		GET_TEX_D(mpOverlapHands, tex);
		SET_SCALE_OWN_SIZE(mpOverlapHands, tex, 0.f);
		SET_POS_XYZ(mpOverlapHands, RESOL_H_WID - 135.f * Texture::GetWidRatio() / 2.f
					, -RESOL_H_HEI + 105.f * Texture::GetHeiRatio() / 2.f, -1.f);
		//mpOverlapHands->GetComponent<Transform>()->SetScale(Vector3(82.f * Texture::GetWidRatio()
		//	, 88.f * Texture::GetHeiRatio(), 0.f));
		//mpOverlapHands->GetComponent<Transform>()->SetPosition(Vector3(800.f - 135.f * Texture::GetWidRatio() / 2.f
		//	, -450.f + 105.f * Texture::GetHeiRatio() / 2.f, -1.f));


		UI* uiHp = new UI();
		AddGameObject(eLayerType::UI, uiHp);
		uiHp->SetCamera(cameraComp2);
		SET_MESH(uiHp, L"RectMesh");
		SET_MATERIAL(uiHp, L"hpUi");
		GET_TEX_D(uiHp, tex);
		SET_SCALE_OWN_SIZE(uiHp, tex, 0.f);
		SET_POS_XYZ(uiHp, -RESOL_H_WID + 117.f * Texture::GetWidRatio() / 2.f
					, -RESOL_H_HEI + 105.f * Texture::GetHeiRatio() / 2.f, -1.f);
		//uiHp->GetComponent<Transform>()->SetScale(Vector3(117.f * Texture::GetWidRatio()
		//	, 104.f * Texture::GetHeiRatio(), 0.f));
		//uiHp->GetComponent<Transform>()->SetPosition(Vector3(-800.f + 117.f * Texture::GetWidRatio() / 2.f
		//	, -450.f + 105.f * Texture::GetHeiRatio() / 2.f, -1.f));

		UI* hp = new UI();
		AddGameObject(eLayerType::UI, hp);
		hp->SetCamera(cameraComp2);
		hp->SetName(L"hp");
		SET_MESH(hp, L"RectMesh");
		SET_MATERIAL(hp, L"hp");
		GET_TEX_D(hp, tex);
		SET_SCALE_OWN_SIZE(hp, tex, 0.f);
		SET_POS_XYZ(hp, -RESOL_H_WID + 138.f * Texture::GetWidRatio() / 2.f
					, -RESOL_H_HEI + 105.f * Texture::GetHeiRatio() / 2.f, -1.f);
		//hp->GetComponent<Transform>()->SetPosition(Vector3(-800.f + 138.f * Texture::GetWidRatio() / 2.f
		//	, -450.f + 105.f * Texture::GetHeiRatio() / 2.f, -1.f));


		UI* hpOverlapHands = new UI();
		AddGameObject(eLayerType::UI, hpOverlapHands);
		hpOverlapHands->SetCamera(cameraComp2);
		SET_MESH(hpOverlapHands, L"RectMesh");
		SET_MATERIAL(hpOverlapHands, L"hpOverlapHands");
		GET_TEX_D(hpOverlapHands, tex);
		SET_SCALE_OWN_SIZE(hpOverlapHands, tex, 0.f);
		SET_POS_XYZ(hpOverlapHands, RESOL_H_WID + 137.f * Texture::GetWidRatio() / 2.f
					, -RESOL_H_HEI + 97.f * Texture::GetHeiRatio() / 2.f, -1.f);
		//hpOverlapHands->GetComponent<Transform>()->SetScale(Vector3(82.f * Texture::GetWidRatio()
		//	, 88.f * Texture::GetHeiRatio(), 0.f));
		//hpOverlapHands->GetComponent<Transform>()->SetPosition(Vector3(-800.f + 137.f * Texture::GetWidRatio() / 2.f
		//	, -450.f + 97.f * Texture::GetHeiRatio() / 2.f, -1.f));

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
		skillShortCut1->SetCamera(cameraComp2);

		SET_MESH(skillShortCut1, L"RectMesh");
		SET_MATERIAL(skillShortCut1, L"frozenOrbIcon");
		GET_TEX_D(skillShortCut1, tex);
		SET_SCALE_OWN_SIZE(skillShortCut1, tex, 0.f);
		SET_POS_XYZ(skillShortCut1, -470.f - tex->GetWidth() * Texture::GetWidRatio() / 2.f
					, -RESOL_H_HEI + tex->GetHeight() * Texture::GetHeiRatio() / 2.f, -1.f);
		skillShortCut1->SetClickMaterial(RESOURCE_FIND(Material, L"frozenOrbClickIcon"));
		skillShortCut1->SetNormalMaterial(RESOURCE_FIND(Material, L"frozenOrbIcon"));
		
		//skillShortCut1->GetComponent<Transform>()->SetScale(Vector3(48.f * Texture::GetWidRatio()
		//	, 48.f* Texture::GetHeiRatio(), 0.f));
		//skillShortCut1->GetComponent<Transform>()->SetPosition(Vector3(-470.f - 48.f * Texture::GetWidRatio() / 2.f
		//	, -450.f + 48.f * Texture::GetHeiRatio() / 2.f, -1.f));

		Button* skillShortCut2 = new Button();
		AddGameObject(eLayerType::UI, skillShortCut2);
		skillShortCut2->SetCamera(cameraComp2);

		SET_MESH(skillShortCut2, L"RectMesh");
		SET_MATERIAL(skillShortCut2, L"thunderStormIcon");
		GET_TEX_D(skillShortCut2, tex);
		SET_SCALE_OWN_SIZE(skillShortCut2, tex, 0.f);
		SET_POS_XYZ(skillShortCut2, 470.f + tex->GetWidth() * Texture::GetWidRatio() / 2.f
					, -RESOL_H_HEI + tex->GetHeight() * Texture::GetHeiRatio() / 2.f, -1.f);
		skillShortCut2->SetClickMaterial(RESOURCE_FIND(Material, L"thunderStormClickIcon"));
		skillShortCut2->SetNormalMaterial(RESOURCE_FIND(Material, L"thunderStormIcon"));
		//skillShortCut2->GetComponent<Transform>()->SetPosition(Vector3(470.f + 48.f * Texture::GetWidRatio() / 2.f
		//	, -450.f + 48.f * Texture::GetHeiRatio() / 2.f, -1.f));


		//GameObject* gridCamera = new GameObject();
		//gridCamera->GetComponent<Transform>()->SetPosition(Vector3(Camera::GetCameraCenter().x, Camera::GetCameraCenter().y, -1.f));
		//Camera* cameraComp3 = gridCamera->AddComponent<Camera>();
		//cameraComp3->DisableLayerMasks();
		//cameraComp3->TurnLayerMask(eLayerType::Grid, true);

		//AddGameObject(eLayerType::UI, gridCamera);

		//GameObject* grid = new GameObject();
		//grid->SetName(L"Grid");
		//AddGameObject(eLayerType::Grid, grid);
		//MeshRenderer* mr = grid->AddComponent<MeshRenderer>();
		//mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		//mr->SetMaterial(Resources::Find<Material>(L"GridMaterial"));
		//GridScript* gridSc = grid->AddComponent<GridScript>();
		//gridSc->SetCamera(cameraComp);

		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Player, true);
		CollisionManager::SetLayer(eLayerType::Item, eLayerType::Item, true);
	}
	void PlayScene::Update()
	{
		Scene::Update();
		
		if (Input::GetKeyDown(eKeyCode::N))
		{
			SceneManager::LoadScene(L"MainMenuScene");
		}
		if (Input::GetKeyDown(eKeyCode::I) && nullptr != inven)
		{
			inven->SetState(inven->GetState() != GameObject::eState::Active ? GameObject::eState::Active : GameObject::eState::Invisible);
		}
		if (Input::GetKeyDown(eKeyCode::T) && nullptr != skillUp)
		{
			skillUp->SetState(skillUp->GetState() != GameObject::eState::Active ? GameObject::eState::Active : GameObject::eState::Invisible);
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