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
#include "mPortal.h"
#include "mScreenEffectManager.h"
#include "mShop.h"
#include "mWall.h"

extern m::Application application;
namespace m
{
	PlayScene::PlayScene()
		: inventory(nullptr)
		, skillUp(nullptr)
		, uiBottomBar(nullptr)
		, shop(nullptr)
		, curMap(nullptr)
		, mBossMonster(nullptr)
		, bStageInit(true)
		, bStageStart(false)
		, mEnterNameUI(nullptr)
		, fAcc(0.f)
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

		CollisionManager::SetLayer(eLayerType::MonsterAura, eLayerType::Player, true);
		CollisionManager::SetLayer(eLayerType::PlayerAura, eLayerType::Monster, true);

		CollisionManager::SetLayer(eLayerType::PlayerOverlay, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::MonsterOverlay, eLayerType::Player, true);

		CollisionManager::SetLayer(eLayerType::Summons, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::PlayerSkill, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::MonsterSkill, eLayerType::Player, true);

		CollisionManager::SetLayer(eLayerType::Item, eLayerType::Item, true);

		GameObject* camera = new GameObject();
		AddGameObject(eLayerType::Camera, camera);
		SET_POS_XYZ(camera, 0.f, 0.f, -10.f);
		ADD_COMP(camera, AudioListener);
		Camera* cameraComp = ADD_COMP(camera, Camera);
		SetSceneMainCamera(cameraComp);
		//cameraComp->TurnLayerMask(eLayerType::UI, false);
		//renderer::cameras.push_back(GetSceneMainCamera());

		TileManager::MakeTile(100, 100, cameraComp);

		{
			Tile* tile = TileManager::pathFindingTiles[5][10];
			Vector3 pos = tile->GetPos();

			Wall* wall = new Wall(cameraComp, tile->GetCoord());
			SET_POS_VEC(wall, pos);
		}
		{
			Tile* tile = TileManager::pathFindingTiles[10][10];
			Vector3 pos = tile->GetPos();

			Wall* wall = new Wall(cameraComp, tile->GetCoord());
			SET_POS_VEC(wall, pos);
		}

		PlayerManager::Initialize();

		SET_MAIN_CAMERA(PlayerManager::player);
		AddGameObject(eLayerType::Player, PlayerManager::player);
		ADD_COMP(PlayerManager::player, PlayerScript);
		GetSceneMainCamera()->SetFollowObject(PlayerManager::player);

		//AudioSource* as = ADD_COMP(PlayerManager::player, AudioSource);
		//as->SetClip(RESOURCE_LOAD(AudioClip, L"test1", L"..\\Resources\\sound\\ambient\\creature\\bat1.wav"));
		//as->SetLoop(true);
		//as->Play();

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

		//FieldItem* testField = new FieldItem(eItem::hpPosion1, Vector3(10.f, 10.f, 1.f));
		//SET_MAIN_CAMERA(testField);
		//AddGameObject(eLayerType::FieldItem, testField);

		Tile* tile = TileManager::pathFindingTiles[10][10];
		Vector3 pos = tile->GetPos();
		mPortal = new Portal();
		SET_POS_VEC(mPortal, pos);
		SET_MAIN_CAMERA(mPortal);
		AddGameObject(eLayerType::Object, mPortal);
		mPortal->SetState(GameObject::RenderUpdate);
		mPortal->ActivePortal();
		mPortal->SetClickPortal([=]()
		{
			TileManager::curTileSystem->WallChange();
		    Stage1();
		});

		Monster* initMonster = new Monster(Vector3(0.f, 0.f, 0.f), 0.f);
		SET_MAIN_CAMERA(initMonster);
		SET_SCALE_XYZ(initMonster, 0.1f, 0.1f, 1.f);
		SET_POS_XYZ(initMonster, 0.f, 0.f, 1.f);
		AddGameObject(eLayerType::Monster, initMonster);


		Vector3 nPos = GET_POS(PlayerManager::player);
		mNpc1 = new NPC(nPos, eNPCType::ConsumNPC);
		mNpc1->SetShop(shop);
		mNpc1->SetState(GameObject::NoRenderNoUpdate);
		SET_MAIN_CAMERA(mNpc1);
		AddGameObject(eLayerType::NPC, mNpc1);

		nPos.x += 100.f;
		mNpc2 = new NPC(nPos, eNPCType::EquimentNPC);
		mNpc2->SetShop(shop);
		mNpc2->SetState(GameObject::NoRenderNoUpdate);
		SET_MAIN_CAMERA(mNpc2);
		AddGameObject(eLayerType::NPC, mNpc2);

		SystemUI();


		{
			curMap = new GameObject();
			SET_MAIN_CAMERA(curMap);
			ADD_COMP(curMap, MeshRenderer);
			AddGameObject(eLayerType::Background, curMap);
			SET_MESH(curMap, L"RectMesh");
			SET_MATERIAL(curMap, L"stage4");
			MAKE_GET_TEX(curMap, tex);
			SET_SCALE_TEX_SIZE(curMap, tex, 1.f);
			Vector3 scale = GET_SCALE(curMap);
			Tile* tile = TileManager::pathFindingTiles[0][0];
			Vector3 tilePos = tile->GetPos();
			Vector3 tileScale = tile->GetScale();
			tilePos.y += scale.y / 2.f;
			tilePos.y -= tileScale.y / 2.f;
			//Tile* centerTile = TileManager::pathFindingTiles[TileManager::tileXLen / 2][TileManager::tileYLen / 2];
			//Vector3 centerPos = centerTile->GetPos();
			SET_POS_XYZ(curMap, tilePos.x, tilePos.y, 1.f);
		}

	}
	void PlayScene::Update()
	{
		if (mEnterNameUI->GetState() == GameObject::RenderUpdate)
		{
			fAcc += Time::fDeltaTime();
			if (fAcc >= 5.f)
			{
				mEnterNameUI->SetState(GameObject::NoRenderNoUpdate);
			}
		}
		if (mBossMonster && mBossMonster->GetBattleState() == GameObject::Dead)
		{
			if (bStageStart)
			{
				Vector3 pos = GET_POS(PlayerManager::player);
				pos.y += 30.f;

				SET_POS_VEC(mPortal, pos);
				mPortal->ActivePortal();
				NPCRender();
				mPortal->SetState(GameObject::RenderUpdate);
				bStageStart = false;
			}
		}
		else
		{
			if (!bStageInit)
			{
				Vector2 size = FontWrapper::GetTextSize(mEnterNameUI->GetText().c_str(), 40.f);
				SET_SCALE_XYZ(mEnterNameUI, size.x, size.y, 1.f);
				mEnterNameUI->SetState(GameObject::RenderUpdate);

				NPCNoRender();
				mPortal->ResetPortal();
				mPortal->SetState(GameObject::NoRenderNoUpdate);
				bStageInit = true;
			}
		}

		Scene::Update();

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

	void PlayScene::SystemUI()
	{
		GameObject* uiCamera = new GameObject();
		SET_POS_XYZ(uiCamera, 0.0f, 0.0f, -1.f);
		Camera* cameraComp2 = ADD_COMP(uiCamera, Camera);
		cameraComp2->TurnLayerMask(eLayerType::Player, false);
		AddGameObject(eLayerType::Camera, uiCamera);
		SetSceneUICamera(cameraComp2);

		ScreenEffectManager::Initialize();

		mEnterNameUI = new UI();
		mEnterNameUI->SetTextNormalColor(Vector4(255.f, 0.f, 0.f, 255.f));
		mEnterNameUI->SetTextSize(40.f);
		mEnterNameUI->SetText(L"고난의 시작");
		mEnterNameUI->SetCamera(cameraComp2);
		Vector2 size = FontWrapper::GetTextSize(mEnterNameUI->GetText().c_str(), 40.f);
		SET_POS_XYZ(mEnterNameUI, 0.f, 100.f + size.y, -1.f);
		SET_MESH(mEnterNameUI, L"RectMesh");
		SET_MATERIAL(mEnterNameUI, L"noneRect");
		mEnterNameUI->SetState(GameObject::RenderUpdate);

		AddGameObject(eLayerType::CanMoveUI, mEnterNameUI);

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
	}

	void PlayScene::Stage1()
	{
		MonsterManager::EraseAll();
		ScreenEffectManager::FadeIn();

		mEnterNameUI->SetText(L"고뇌의 여제");

		fAcc = 0.f;
		bStageInit = false;
		bStageStart = true;

		mPortal->SetClickPortal(
			[=]()
			{
				Stage2();
			}
		);


		{
			Tile* tile = TileManager::pathFindingTiles[1][3];
			Vector3 pos = tile->GetPos();
			SET_POS_VEC(PlayerManager::player, pos);
		}

		//{
		//	Tile* tile = TileManager::pathFindingTiles[60][50];
		//	Vector3 pos = tile->GetPos();
		//	Monster* monster = new Monster(pos, MDBalrog().fSpeed);
		//	SET_MAIN_CAMERA(monster);
		//	AddGameObject(eLayerType::Monster, monster);
		//	MonsterScript<MDBalrog>* ms = ADD_COMP(monster, MonsterScript<MDBalrog>);
		//	monster->SetMonsterClass(ms->GetMonsterClass());
		//	monster->SetMonsterName(ms->GetcurMonsterData().wsMonsterName);
		//	monster->SetHpCapacity(ms->GetcurMonsterData().hp);
		//}
		//{
		//	Tile* tile = TileManager::pathFindingTiles[50][51];
		//	Vector3 pos = tile->GetPos();
		//	Monster* monster = new Monster(pos, MDBalrog().fSpeed);
		//	SET_MAIN_CAMERA(monster);
		//	AddGameObject(eLayerType::Monster, monster);
		//	MonsterScript<MDBalrog>* ms = ADD_COMP(monster, MonsterScript<MDBalrog>);
		//	monster->SetMonsterClass(ms->GetMonsterClass());
		//	monster->SetMonsterName(ms->GetcurMonsterData().wsMonsterName);
		//	monster->SetHpCapacity(ms->GetcurMonsterData().hp);
		//}
		{
			Tile* tile = TileManager::pathFindingTiles[55][60];
			Vector3 pos = tile->GetPos();
			Monster* monster = new Monster(pos, MDBalrog().fSpeed);
			SET_MAIN_CAMERA(monster);
			monster->SetCoord(tile->GetCoord());
			AddGameObject(eLayerType::Monster, monster);
			MonsterScript<MDBalrog>* ms = ADD_COMP(monster, MonsterScript<MDBalrog>);
			monster->SetMonsterClass(ms->GetMonsterClass());
			monster->SetMonsterName(ms->GetcurMonsterData().wsMonsterName);
			monster->SetHpCapacity(ms->GetcurMonsterData().hp);
		}
		{
			Tile* tile = TileManager::pathFindingTiles[40][30];
			Vector3 pos = tile->GetPos();
			Monster* monster = new Monster(pos, MDAndariel().fSpeed);
			monster->SetCoord(tile->GetCoord());
			SET_MAIN_CAMERA(monster);
			AddGameObject(eLayerType::Monster, monster);
			MonsterScript<MDAndariel>* ms = ADD_COMP(monster, MonsterScript<MDAndariel>);
			monster->SetMonsterClass(ms->GetMonsterClass());
			monster->SetMonsterName(ms->GetcurMonsterData().wsMonsterName);
			monster->SetHpCapacity(ms->GetcurMonsterData().hp);

			mBossMonster = monster;
		}
	}

	void PlayScene::Stage2()
	{
		MonsterManager::EraseAll();
		ScreenEffectManager::FadeIn();

		mEnterNameUI->SetText(L"고통의 군주");
		fAcc = 0.f;
		bStageInit = false;
		bStageStart = true;

		mPortal->SetClickPortal(
			[=]()
			{
				Stage3();
			}
		);

		{
			Tile* tile = TileManager::pathFindingTiles[1][1];
			Vector3 pos = tile->GetPos();
			SET_POS_VEC(PlayerManager::player, pos);
		}

		{
			Tile* tile = TileManager::pathFindingTiles[60][20];
			Vector3 pos = tile->GetPos();
			Monster* monster = new Monster(pos, MDDuriel().fSpeed);
			monster->SetCoord(tile->GetCoord());
			SET_MAIN_CAMERA(monster);
			AddGameObject(eLayerType::Monster, monster);
			MonsterScript<MDDuriel>* ms = ADD_COMP(monster, MonsterScript<MDDuriel>);
			monster->SetMonsterClass(ms->GetMonsterClass());
			monster->SetMonsterName(ms->GetcurMonsterData().wsMonsterName);
			monster->SetHpCapacity(ms->GetcurMonsterData().hp);

			mBossMonster = monster;
		}
	}

	void PlayScene::Stage3()
	{
		MonsterManager::EraseAll();
		ScreenEffectManager::FadeIn();

		mEnterNameUI->SetText(L"증오의 군주");
		fAcc = 0.f;
		bStageInit = false;
		bStageStart = true;

		mPortal->SetClickPortal(
			[=]()
			{
				Stage4();
			}
		);

		{
			Tile* tile = TileManager::pathFindingTiles[2][2];
			Vector3 pos = tile->GetPos();
			SET_POS_VEC(PlayerManager::player, pos);
		}

		{
			Tile* tile = TileManager::pathFindingTiles[40][30];
			Vector3 pos = tile->GetPos();
			Monster* monster = new Monster(pos, MDMephisto().fSpeed);
			monster->SetCoord(tile->GetCoord());
			SET_MAIN_CAMERA(monster);
			AddGameObject(eLayerType::Monster, monster);
			MonsterScript<MDMephisto>* ms = ADD_COMP(monster, MonsterScript<MDMephisto>);
			monster->SetMonsterClass(ms->GetMonsterClass());
			monster->SetMonsterName(ms->GetcurMonsterData().wsMonsterName);
			monster->SetHpCapacity(ms->GetcurMonsterData().hp);

			mBossMonster = monster;
		}
	}

	void PlayScene::Stage4()
	{
		MonsterManager::EraseAll();
		ScreenEffectManager::FadeIn();

		ScreenEffectManager::Shake(3.f);

		mEnterNameUI->SetText(L"공포의 군주");
		fAcc = 0.f;
		bStageInit = false;
		bStageStart = true;

		{
			Tile* tile = TileManager::pathFindingTiles[4][4];
			Vector3 pos = tile->GetPos();
			SET_POS_VEC(PlayerManager::player, pos);
		}

		{
			Tile* tile = TileManager::pathFindingTiles[78][53];
			Vector3 pos = tile->GetPos();
			Monster* monster = new Monster(pos, MDDiablo().fSpeed);
			monster->SetCoord(tile->GetCoord());
			SET_MAIN_CAMERA(monster);
			AddGameObject(eLayerType::Monster, monster);
			MonsterScript<MDDiablo>* ms = ADD_COMP(monster, MonsterScript<MDDiablo>);
			monster->SetMonsterClass(ms->GetMonsterClass());
			monster->SetMonsterName(ms->GetcurMonsterData().wsMonsterName);
			monster->SetHpCapacity(ms->GetcurMonsterData().hp);

			mBossMonster = monster;
		}
	}

	void PlayScene::NPCRender()
	{
		Vector3 nPos = GET_POS(PlayerManager::player);
		SET_POS_VEC(mNpc1, nPos);
		SET_POS_VEC(mNpc2, nPos);

		mNpc1->SetState(GameObject::RenderUpdate);
		mNpc2->SetState(GameObject::RenderUpdate);
	}

	void PlayScene::NPCNoRender()
	{
		mNpc1->SetState(GameObject::NoRenderUpdate);
		mNpc2->SetState(GameObject::NoRenderUpdate);
	}
}
