#include "mPlayScene.h"

#include "mAudioListener.h"
#include "mAudioSource.h"
#include "../engine_source/mGameObject.h"
#include "../engine_source/mMeshRenderer.h"
#include "../engine_source/mTransform.h"
#include "../engine_source/mResources.h"
#include "../engine_source/mCamera.h"
#include "../engine_source/mSceneManager.h"
#include "../engine_source/mRenderer.h"
#include "../engine_source/mApplication.h"
#include "../engine_source/mCollisionManager.h"
#include "../engine_source/mAnimator.h"
#include "../engine_source/MoveAbleObjectAnimLookUpTables.h"
#include "../engine_source/mFontWrapper.h"
#include "../engine_source/mComputeShader.h"
#include "../engine_source/mTileManager.h"

#include "mPlayer.h"
#include "mMonster.h"
#include "mTile.h"
#include "mButton.h"
#include "mInventory.h"
#include "mInvenItem.h"
#include "mGridScript.h"
#include "mSkillStatus.h"
#include "mCollider2D.h"
#include "mPlayerScript.h"
#include "mMonsterScript.h"
#include "mBottomUI.h"
#include "mUVUI.h"
#include "mPlayerManager.h"
#include "mSkillShortCutButton.h"
#include "mParticleSystem.h"
#include "mOverlayEffectSkillScript.h"
#include "mFallScript.h"
#include "mTileSystem.h"
#include "mCameraScript.h"
#include "mEnemyHpUI.h"
#include "mFieldItem.h"
#include "mLightObject.h"
#include "mNPC.h"
#include "mShop.h"

extern m::Application application;
namespace m
{
	PlayScene::PlayScene()
	{

	}
	PlayScene::~PlayScene()
	{
	}
	void PlayScene::Initialize()
	{
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Monster, true);

		CollisionManager::SetLayer(eLayerType::Skill, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::Skill, eLayerType::Player, true);

		CollisionManager::SetLayer(eLayerType::Aura, eLayerType::Player, true);
		CollisionManager::SetLayer(eLayerType::Aura, eLayerType::Monster, true);

		CollisionManager::SetLayer(eLayerType::PlayerOverlay, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::MonsterOverlay, eLayerType::Player, true);

		CollisionManager::SetLayer(eLayerType::Summons, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::PlayerSkill, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::MonsterSkill, eLayerType::Player, true);

		CollisionManager::SetLayer(eLayerType::Item, eLayerType::Item, true);

		SHARED_TEX tex;

		GameObject* camera = new GameObject();
		AddGameObject(eLayerType::Camera, camera);
		SET_POS_XYZ(camera, 0.f, 0.f, -10.f);
		ADD_COMP(camera, AudioListener);
		Camera* cameraComp = ADD_COMP(camera, Camera);
		SetSceneMainCamera(cameraComp);
		//cameraComp->TurnLayerMask(eLayerType::UI, false);
		//renderer::cameras.push_back(GetSceneMainCamera());

		TileManager::MakeTile(100, 100, cameraComp);

		GameObject* map = new GameObject();
		SET_MAIN_CAMERA(map);
		ADD_COMP(map, MeshRenderer);
		AddGameObject(eLayerType::Background, map);
		SET_MESH(map, L"RectMesh");
		SET_MATERIAL(map, L"chaosSanctuary1");
		GET_TEX(map, tex);
		SET_SCALE_TEX_SIZE(map, tex, 1.f);
		Tile* centerTile = TileManager::pathFindingTiles[TileManager::tileXLen / 2][TileManager::tileYLen / 2];
		Vector3 centerPos = centerTile->GetPos();

		SET_POS_XYZ(map, centerPos.x, centerPos.y, 1.f);

		PlayerManager::Initialize();

		//AudioSource* as = ADD_COMP(PlayerManager::player, AudioSource);
		//as->SetClip(RESOURCE_LOAD(AudioClip, L"test1", L"..\\Resources\\sound\\ambient\\creature\\bat1.wav"));
		//as->SetLoop(true);
		//as->Play();

		SET_MAIN_CAMERA(PlayerManager::player);
		AddGameObject(eLayerType::Player, PlayerManager::player);
		ADD_COMP(PlayerManager::player, PlayerScript);
		GetSceneMainCamera()->SetFollowObject(PlayerManager::player);

		Tile* tile5 = TileManager::pathFindingTiles[60][10];
		Vector3 pos4 = tile5->GetPos();

		//GameObject* qwe = new GameObject();
		//SET_MAIN_CAMERA(qwe);
		//AddGameObject(eLayerType::Skill, qwe);
		//ADD_COMP(qwe, MeshRenderer);
		//ADD_COMP(qwe, Collider2D);
		//SET_SCALE_XYZ(qwe, 100.f, 100.f, 1.f);
		//SET_MESH(qwe, L"RectMesh");
		//SET_MATERIAL(qwe, L"testSc");
		//Animator* anim = ADD_COMP(qwe, Animator);
		//SET_POS_VEC(qwe, pos4);

		//{
		//	Tile* tile = TileManager::pathFindingTiles[78][53];
		//	Vector3 pos = tile->GetPos();
		//	Monster* monster = new Monster(pos, MDDiablo().fSpeed);
		//	SET_MAIN_CAMERA(monster);
		//	AddGameObject(eLayerType::Monster, monster);
		//	MonsterScript<MDDiablo>* ms = ADD_COMP(monster, MonsterScript<MDDiablo>);
		//	monster->SetMonsterClass(ms->GetMonsterClass());
		//	monster->SetMonsterName(ms->GetcurMonsterData().wsMonsterName);
		//	monster->SetHpCapacity(ms->GetcurMonsterData().hp);
		//}
		//{
		//	Tile* tile = TileManager::pathFindingTiles[40][30];
		//	Vector3 pos = tile->GetPos();
		//	Monster* monster = new Monster(pos, MDAndariel().fSpeed);
		//	SET_MAIN_CAMERA(monster);
		//	AddGameObject(eLayerType::Monster, monster);
		//	SET_MESH(monster, L"RectMesh");
		//	SET_MATERIAL(monster, L"AnimationMaterial");
		//	ADD_COMP(monster, Animator);
		//	MonsterScript<MDAndariel>* ms = ADD_COMP(monster, MonsterScript<MDAndariel>);
		//	monster->SetMonsterClass(ms->GetMonsterClass());
		//	monster->SetMonsterName(ms->GetcurMonsterData().wsMonsterName);
		//	monster->SetHpCapacity(ms->GetcurMonsterData().hp);
		//}
		//{
		//	Tile* tile = TileManager::pathFindingTiles[40][30];
		//	Vector3 pos = tile->GetPos();
		//	Monster* monster = new Monster(pos, MDMephisto().fSpeed);
		//	SET_MAIN_CAMERA(monster);
		//	AddGameObject(eLayerType::Monster, monster);
		//	SET_MESH(monster, L"RectMesh");
		//	SET_MATERIAL(monster, L"AnimationMaterial");
		//	ADD_COMP(monster, Animator);
		//	MonsterScript<MDMephisto>* ms = ADD_COMP(monster, MonsterScript<MDMephisto>);
		//	monster->SetMonsterClass(ms->GetMonsterClass());
		//	monster->SetMonsterName(ms->GetcurMonsterData().wsMonsterName);
		//	monster->SetHpCapacity(ms->GetcurMonsterData().hp);
		//}
		//{
		//	Tile* tile = TileManager::pathFindingTiles[60][20];
		//	Vector3 pos = tile->GetPos();
		//	Monster* monster = new Monster(pos, MDDuriel().fSpeed);
		//	SET_MAIN_CAMERA(monster);
		//	AddGameObject(eLayerType::Monster, monster);
		//	SET_MESH(monster, L"RectMesh");
		//	SET_MATERIAL(monster, L"AnimationMaterial");
		//	ADD_COMP(monster, Animator);
		//	MonsterScript<MDDuriel>* ms = ADD_COMP(monster, MonsterScript<MDDuriel>);
		//	monster->SetMonsterClass(ms->GetMonsterClass());
		//	monster->SetMonsterName(ms->GetcurMonsterData().wsMonsterName);
		//	monster->SetHpCapacity(ms->GetcurMonsterData().hp);
		//}

		{
			Tile* tile = TileManager::pathFindingTiles[60][50];
			Vector3 pos = tile->GetPos();
			Monster* monster = new Monster(pos, MDBalrog().fSpeed);
			SET_MAIN_CAMERA(monster);
			AddGameObject(eLayerType::Monster, monster);
			SET_MESH(monster, L"RectMesh");
			SET_MATERIAL(monster, L"AnimationMaterial");
			ADD_COMP(monster, Animator);
			MonsterScript<MDBalrog>* ms = ADD_COMP(monster, MonsterScript<MDBalrog>);
			monster->SetMonsterClass(ms->GetMonsterClass());
			monster->SetMonsterName(ms->GetcurMonsterData().wsMonsterName);
			monster->SetHpCapacity(ms->GetcurMonsterData().hp);
		}
		{
			Tile* tile = TileManager::pathFindingTiles[50][51];
			Vector3 pos = tile->GetPos();
			Monster* monster = new Monster(pos, MDBalrog().fSpeed);
			SET_MAIN_CAMERA(monster);
			AddGameObject(eLayerType::Monster, monster);
			SET_MESH(monster, L"RectMesh");
			SET_MATERIAL(monster, L"AnimationMaterial");
			ADD_COMP(monster, Animator);
			MonsterScript<MDBalrog>* ms = ADD_COMP(monster, MonsterScript<MDBalrog>);
			monster->SetMonsterClass(ms->GetMonsterClass());
			monster->SetMonsterName(ms->GetcurMonsterData().wsMonsterName);
			monster->SetHpCapacity(ms->GetcurMonsterData().hp);
		}
		{
			Tile* tile = TileManager::pathFindingTiles[55][60];
			Vector3 pos = tile->GetPos();
			Monster* monster = new Monster(pos, MDBalrog().fSpeed);
			SET_MAIN_CAMERA(monster);
			AddGameObject(eLayerType::Monster, monster);
			SET_MESH(monster, L"RectMesh");
			SET_MATERIAL(monster, L"AnimationMaterial");
			ADD_COMP(monster, Animator);
			MonsterScript<MDBalrog>* ms = ADD_COMP(monster, MonsterScript<MDBalrog>);
			monster->SetMonsterClass(ms->GetMonsterClass());
			monster->SetMonsterName(ms->GetcurMonsterData().wsMonsterName);
			monster->SetHpCapacity(ms->GetcurMonsterData().hp);
		}

		FieldItem* testField = new FieldItem(eItem::hpPosion1, Vector3(10.f, 10.f, 1.f));
		SET_MAIN_CAMERA(testField);
		AddGameObject(eLayerType::FieldItem, testField);

		GameObject* uiCamera = new GameObject();
		SET_POS_XYZ(uiCamera, 0.0f, 0.0f, -1.f);
		Camera* cameraComp2 = ADD_COMP(uiCamera, Camera);
		cameraComp2->TurnLayerMask(eLayerType::Player, false);
		AddGameObject(eLayerType::Camera, uiCamera);
		SetSceneUICamera(cameraComp2);

		//GameObject* qwe = new GameObject();
		//qwe->SetCamera(cameraComp2);
		//AddGameObject(eLayerType::UI, qwe);
		//ADD_COMP(qwe, MeshRenderer);
		//SET_MESH(qwe, L"RectMesh");
		//SET_MATERIAL(qwe, L"skillImageTest");
		//SET_SCALE_XYZ(qwe, 100.f, 100.f, 1.f);

		inventory = new Inventory(cameraComp2);
		inventory->SetState(GameObject::NoRenderUpdate);

		skillUp = new SkillStatus(cameraComp2);
		skillUp->SetState(GameObject::NoRenderUpdate);

		uiBottomBar = new BottomUI(cameraComp2);

		shop = new Shop(cameraComp2);

		EnemyHpUI* eHpUI = new EnemyHpUI(Vector3(0.f, 0.f, -1.f));
		eHpUI->SetCamera(cameraComp2);
		eHpUI->SetFontSize(20.f);
		AddGameObject(eLayerType::UI, eHpUI);

		//Vector3 nPos = GET_POS(PlayerManager::player);
		//NPC* npc1 = new NPC(nPos, eNPCType::ConsumNPC);
		//npc1->SetShop(shop);
		//SET_MAIN_CAMERA(npc1);
		//AddGameObject(eLayerType::NPC, npc1);

		//nPos.x += 100.f;
		//NPC* npc2 = new NPC(nPos, eNPCType::EquimentNPC);
		//npc2->SetShop(shop);
		//SET_MAIN_CAMERA(npc2);
		//AddGameObject(eLayerType::NPC, npc2);
	}
	void PlayScene::Update()
	{
		Scene::Update();
		//TileManager::TilesUpdate();
		if (Input::GetKeyDown(eKeyCode::N))
		{
			SceneManager::LoadScene(L"MainMenuScene");
		}
		if (Input::GetKeyDown(eKeyCode::I) && nullptr != inventory)
		{
			inventory->SetState(inventory->GetState() != GameObject::eState::RenderUpdate ? GameObject::eState::RenderUpdate : GameObject::eState::NoRenderUpdate);
		}
		if (Input::GetKeyDown(eKeyCode::T) && nullptr != skillUp)
		{
			skillUp->SetState(skillUp->GetState() != GameObject::eState::RenderUpdate ? GameObject::eState::RenderUpdate : GameObject::eState::NoRenderUpdate);
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