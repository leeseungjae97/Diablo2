#include "mPlayScene.h"

#include "../engine_source/MoveAbleObjectAnimLookUpTables.h"
#include "../engine_source/mAudioListener.h"
#include "../engine_source/mAudioSource.h"
#include "../engine_source/mGameObject.h"
#include "../engine_source/mMeshRenderer.h"
#include "../engine_source/mTransform.h"
#include "../engine_source/mResources.h"
#include "../engine_source/mCamera.h"
#include "../engine_source/mSceneManager.h"
#include "../engine_source/mRenderer.h"
#include "../engine_source/mApplication.h"
#include "../engine_source/mCollisionManager.h"
#include "../engine_source/mFontWrapper.h"
#include "../engine_source/mComputeShader.h"
#include "../engine_source/mTileManager.h"

#include "../engine_source/mSkillManager.h"
#include "../engine_source/mSoundManager.h"
#include "../engine_source/mStageManager.h"
#include "../engine_source/mScreenEffectManager.h"
#include "../engine_source/mFieldItemManager.h"

#include "mPlayer.h"
#include "mMonster.h"
#include "mTile.h"
#include "mButton.h"
#include "mInventory.h"
#include "mSkillStatus.h"
#include "mPlayerScript.h"
#include "mMonsterScript.h"
#include "mBottomUI.h"
#include "mPlayerManager.h"
#include "mCharacterStatus.h"
#include "mEnemyHpUI.h"
#include "mFloor.h"
#include "mNPC.h"
#include "mPortal.h"
#include "mShop.h"
#include "mTorch.h"
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
		, bPlaySceneFireUpdate(true)
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

		CollisionManager::SetLayer(eLayerType::PlayerSkill, eLayerType::Wall, true);
		CollisionManager::SetLayer(eLayerType::MonsterSkill, eLayerType::Wall, true);

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
		PlayerManager::Initialize();

		SET_MAIN_CAMERA(PlayerManager::player);
		AddGameObject(eLayerType::Player, PlayerManager::player);
		ADD_COMP(PlayerManager::player, PlayerScript);
		GetSceneMainCamera()->SetFollowObject(PlayerManager::player);

		//AudioSource* as = ADD_COMP(PlayerManager::player, AudioSource);
		//as->SetClip(RESOURCE_LOAD(AudioClip, L"test1", L"..\\Resources\\sound\\ambient\\creature\\bat1.wav"));
		//as->SetLoop(true);
		//as->Play();

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
				Stage1();
			});


		Monster* initMonster = new Monster(Vector3(-9999.f, -9999.f, 0.f), 0.f);
		SET_MAIN_CAMERA(initMonster);
		SET_SCALE_XYZ(initMonster, 0.1f, 0.1f, 1.f);
		SET_POS_XYZ(initMonster, 0.f, 0.f, 1.f);
		AddGameObject(eLayerType::Monster, initMonster);

		SystemUI();

		mNpc1 = new NPC(Vector3(0.f, 0.f, 1.f), eNPCType::ConsumNPC);
		mNpc1->SetShop(shop);
		mNpc1->SetState(GameObject::NoRenderNoUpdate);
		SET_MAIN_CAMERA(mNpc1);
		AddGameObject(eLayerType::NPC, mNpc1);

		mNpc2 = new NPC(Vector3(0.f, 0.f, 1.f), eNPCType::EquimentNPC);
		mNpc2->SetShop(shop);
		mNpc2->SetState(GameObject::NoRenderNoUpdate);
		SET_MAIN_CAMERA(mNpc2);
		AddGameObject(eLayerType::NPC, mNpc2);


		{
			curMap = new GameObject();
			SET_MAIN_CAMERA(curMap);
			ADD_COMP(curMap, MeshRenderer);
			AddGameObject(eLayerType::Background, curMap);
			SET_MESH(curMap, L"RectMesh");
			SET_MATERIAL(curMap, L"stage1");
			MAKE_GET_TEX(curMap, tex);
			SET_SCALE_TEX_SIZE(curMap, tex, 1.f);
			Vector3 scale = GET_SCALE(curMap);
			Tile* tile = TileManager::pathFindingTiles[0][0];
			Vector3 tilePos = tile->GetPos();
			Vector3 tileScale = tile->GetScale();
			tilePos.y += scale.y / 2.f;
			tilePos.y -= tileScale.y / 2.f;
			SET_POS_XYZ(curMap, tilePos.x, tilePos.y, 2.f);
		}
		Stage0();
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
				//Vector3 pos = GET_POS(PlayerManager::player);
				//pos.y += 30.f;

				//SET_POS_VEC(mPortal, pos);
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

		//if (Input::GetKeyDown(eKeyCode::N))
		//{
		//	SceneManager::LoadScene(L"MainMenuScene");
		//}
		if (bPlaySceneFireUpdate)
		{
			bPlaySceneFireUpdate = false;
			//Stage0();
		}
		if (Input::GetKeyDown(eKeyCode::I) && nullptr != inventory)
		{
			inventory->SetState(inventory->GetState() != GameObject::eState::RenderUpdate ? GameObject::eState::RenderUpdate : GameObject::eState::NoRenderUpdate);
			skillUp->SetState(GameObject::NoRenderUpdate);
		}
		if (Input::GetKeyDown(eKeyCode::T) && nullptr != skillUp)
		{
			skillUp->SetState(skillUp->GetState() != GameObject::eState::RenderUpdate ? GameObject::eState::RenderUpdate : GameObject::eState::NoRenderUpdate);
			inventory->SetState(GameObject::NoRenderUpdate);
		}
		if (Input::GetKeyDown(eKeyCode::A) && nullptr != skillUp)
		{
			status->SetState(status->GetState() != GameObject::eState::RenderUpdate ? GameObject::eState::RenderUpdate : GameObject::eState::NoRenderUpdate);
		}

		if (skillUp->GetState() == GameObject::eState::RenderUpdate)
		{
			inventory->SetState(GameObject::NoRenderUpdate);
		}
		if (inventory->GetState() == GameObject::eState::RenderUpdate)
		{
			skillUp->SetState(GameObject::NoRenderUpdate);
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
		{
			dayLight = new GameObject();

			Light* lightComp = dayLight->AddComponent<Light>();
			dayLight->SetState(GameObject::NoRenderNoUpdate);
			lightComp->SetType(eLightType::Directional);
			lightComp->SetColor(Vector4(0.7f, 0.7f, 0.7f, 1.0f));
			AddGameObject(eLayerType::Light, dayLight);
		}

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

		status = new CharacterStatus(cameraComp2);
		status->SetState(GameObject::NoRenderUpdate);

		uiBottomBar = new BottomUI(cameraComp2);

		shop = new Shop(cameraComp2);
		EnemyHpUI* eHpUI = new EnemyHpUI(Vector3(0.f, 0.f, -1.f));
		eHpUI->SetCamera(cameraComp2);
		eHpUI->SetFontSize(20.f);
		AddGameObject(eLayerType::UI, eHpUI);
	}

	void PlayScene::MakeStage4Wall()
	{
		Camera* cameraComp = GetSceneMainCamera();
		TileManager::TileIsWallReset();

		if (nullptr == cameraComp) return;
		{
			{
				Tile* tile = TileManager::pathFindingTiles[54][40];
				Vector3 pos = tile->GetPos();

				Wall* wall = new Wall(eWallType::Stage4Wall2, cameraComp, tile->GetCoord());
				SET_POS_VEC(wall, pos);
			}
			{
				Tile* tile = TileManager::pathFindingTiles[54][37];
				Vector3 pos = tile->GetPos();

				Wall* wall = new Wall(eWallType::Stage4Wall2, cameraComp, tile->GetCoord());
				SET_POS_VEC(wall, pos);
			}
			{
				Tile* tile = TileManager::pathFindingTiles[47][37];
				Vector3 pos = tile->GetPos();

				Wall* wall = new Wall(eWallType::Stage4Wall2, cameraComp, tile->GetCoord());
				SET_POS_VEC(wall, pos);
			}
			{
				Tile* tile = TileManager::pathFindingTiles[47][40];
				Vector3 pos = tile->GetPos();

				Wall* wall = new Wall(eWallType::Stage4Wall2, cameraComp, tile->GetCoord());
				SET_POS_VEC(wall, pos);
			}
			{
				Tile* tile = TileManager::pathFindingTiles[49][35];
				Vector3 pos = tile->GetPos();

				Wall* wall = new Wall(eWallType::Stage4Wall1, cameraComp, tile->GetCoord());
				SET_POS_VEC(wall, pos);
			}
			{
				Tile* tile = TileManager::pathFindingTiles[52][35];
				Vector3 pos = tile->GetPos();

				Wall* wall = new Wall(eWallType::Stage4Wall1, cameraComp, tile->GetCoord());
				SET_POS_VEC(wall, pos);
			}
			{
				Tile* tile = TileManager::pathFindingTiles[49][42];
				Vector3 pos = tile->GetPos();

				Wall* wall = new Wall(eWallType::Stage4Wall1, cameraComp, tile->GetCoord());
				SET_POS_VEC(wall, pos);
			}
			{
				Tile* tile = TileManager::pathFindingTiles[52][42];
				Vector3 pos = tile->GetPos();

				Wall* wall = new Wall(eWallType::Stage4Wall1, cameraComp, tile->GetCoord());
				SET_POS_VEC(wall, pos);
			}
		}

		{
			{
				Tile* tile = TileManager::pathFindingTiles[42][49];
				Vector3 pos = tile->GetPos();

				Wall* wall = new Wall(eWallType::Stage4Wall2, cameraComp, tile->GetCoord());
				SET_POS_VEC(wall, pos);
			}
			{
				Tile* tile = TileManager::pathFindingTiles[42][52];
				Vector3 pos = tile->GetPos();

				Wall* wall = new Wall(eWallType::Stage4Wall2, cameraComp, tile->GetCoord());
				SET_POS_VEC(wall, pos);
			}
			{
				Tile* tile = TileManager::pathFindingTiles[35][49];
				Vector3 pos = tile->GetPos();

				Wall* wall = new Wall(eWallType::Stage4Wall2, cameraComp, tile->GetCoord());
				SET_POS_VEC(wall, pos);
			}
			{
				Tile* tile = TileManager::pathFindingTiles[35][52];
				Vector3 pos = tile->GetPos();

				Wall* wall = new Wall(eWallType::Stage4Wall2, cameraComp, tile->GetCoord());
				SET_POS_VEC(wall, pos);
			}
			{
				Tile* tile = TileManager::pathFindingTiles[37][54];
				Vector3 pos = tile->GetPos();

				Wall* wall = new Wall(eWallType::Stage4Wall1, cameraComp, tile->GetCoord());
				SET_POS_VEC(wall, pos);
			}
			{
				Tile* tile = TileManager::pathFindingTiles[40][54];
				Vector3 pos = tile->GetPos();

				Wall* wall = new Wall(eWallType::Stage4Wall1, cameraComp, tile->GetCoord());
				SET_POS_VEC(wall, pos);
			}
			{
				Tile* tile = TileManager::pathFindingTiles[37][47];
				Vector3 pos = tile->GetPos();

				Wall* wall = new Wall(eWallType::Stage4Wall1, cameraComp, tile->GetCoord());
				SET_POS_VEC(wall, pos);
			}
			{
				Tile* tile = TileManager::pathFindingTiles[40][47];
				Vector3 pos = tile->GetPos();

				Wall* wall = new Wall(eWallType::Stage4Wall1, cameraComp, tile->GetCoord());
				SET_POS_VEC(wall, pos);
			}
		}

		TileManager::MakeStageWall(3);

		TileManager::TileIsWallChange();
	}

	void PlayScene::MakeStage3Wall()
	{
		Camera* cameraComp = GetSceneMainCamera();
		TileManager::TileIsWallReset();

		if (nullptr == cameraComp) return;

		{
			{
				Tile* tile = TileManager::pathFindingTiles[38][53];
				Vector3 pos = tile->GetPos();
				Torch* torch = new Torch(pos, tile->GetCoord(), cameraComp, eTorchType::Stage1Torch1);
			}
			{
				Tile* tile = TileManager::pathFindingTiles[38][56];
				Vector3 pos = tile->GetPos();
				Torch* torch = new Torch(pos, tile->GetCoord(), cameraComp, eTorchType::Stage1Torch1);
			}
			{
				Tile* tile = TileManager::pathFindingTiles[47][62];
				Vector3 pos = tile->GetPos();
				Torch* torch = new Torch(pos, tile->GetCoord(), cameraComp, eTorchType::Stage1Torch1);
			}
			{
				Tile* tile = TileManager::pathFindingTiles[47][50];
				Vector3 pos = tile->GetPos();
				Torch* torch = new Torch(pos, tile->GetCoord(), cameraComp, eTorchType::Stage1Torch1);
			}

			{
				Tile* tile = TileManager::pathFindingTiles[59][43];
				Vector3 pos = tile->GetPos();
				Torch* torch = new Torch(pos, tile->GetCoord(), cameraComp, eTorchType::Stage1Torch1);
			}
			{
				Tile* tile = TileManager::pathFindingTiles[59][67];
				Vector3 pos = tile->GetPos();
				Torch* torch = new Torch(pos, tile->GetCoord(), cameraComp, eTorchType::Stage1Torch1);
			}
			{
				Tile* tile = TileManager::pathFindingTiles[62][52];
				Vector3 pos = tile->GetPos();
				Torch* torch = new Torch(pos, tile->GetCoord(), cameraComp, eTorchType::Stage1Torch1);
			}
			{
				Tile* tile = TileManager::pathFindingTiles[62][60];
				Vector3 pos = tile->GetPos();
				Torch* torch = new Torch(pos, tile->GetCoord(), cameraComp, eTorchType::Stage1Torch1);
			}

			{
				Tile* tile = TileManager::pathFindingTiles[52][60];
				Vector3 pos = tile->GetPos();
				Torch* torch = new Torch(pos, tile->GetCoord(), cameraComp, eTorchType::Stage1Torch1);
			}
			{
				Tile* tile = TileManager::pathFindingTiles[52][52];
				Vector3 pos = tile->GetPos();
				Torch* torch = new Torch(pos, tile->GetCoord(), cameraComp, eTorchType::Stage1Torch1);
			}
		}

		TileManager::MakeStageWall(2);

		TileManager::TileIsWallChange();
	}

	void PlayScene::MakeStage2Wall()
	{
		Camera* cameraComp = GetSceneMainCamera();
		TileManager::TileIsWallReset();

		if (nullptr == cameraComp) return;

		{
			Tile* tile = TileManager::pathFindingTiles[60][49];
			Vector3 pos = tile->GetPos();

			Wall* wall = new Wall(eWallType::Stage2Wall1, cameraComp, tile->GetCoord());
			SET_POS_VEC(wall, pos);
		}

		TileManager::MakeStageWall(1);

		TileManager::TileIsWallChange();
	}

	void PlayScene::MakeStage1Wall()
	{
		Camera* cameraComp = GetSceneMainCamera();
		TileManager::TileIsWallReset();

		if (nullptr == cameraComp) return;

		{
			{
				Tile* tile = TileManager::pathFindingTiles[56][60];
				Vector3 pos = tile->GetPos();

				Wall* wall = new Wall(eWallType::Stage1Wall1, cameraComp, tile->GetCoord());
				SET_POS_VEC(wall, pos);
			}
			{
				Tile* tile = TileManager::pathFindingTiles[56][64];
				Vector3 pos = tile->GetPos();

				Wall* wall = new Wall(eWallType::Stage1Wall1, cameraComp, tile->GetCoord());
				SET_POS_VEC(wall, pos);
			}
			{
				Tile* tile = TileManager::pathFindingTiles[56][69];
				Vector3 pos = tile->GetPos();

				Wall* wall = new Wall(eWallType::Stage1Wall1, cameraComp, tile->GetCoord());
				SET_POS_VEC(wall, pos);
			}
			{
				Tile* tile = TileManager::pathFindingTiles[49][60];
				Vector3 pos = tile->GetPos();

				Wall* wall = new Wall(eWallType::Stage1Wall1, cameraComp, tile->GetCoord());
				SET_POS_VEC(wall, pos);
			}
			{
				Tile* tile = TileManager::pathFindingTiles[49][64];
				Vector3 pos = tile->GetPos();

				Wall* wall = new Wall(eWallType::Stage1Wall1, cameraComp, tile->GetCoord());
				SET_POS_VEC(wall, pos);
			}
			{
				Tile* tile = TileManager::pathFindingTiles[49][69];
				Vector3 pos = tile->GetPos();

				Wall* wall = new Wall(eWallType::Stage1Wall1, cameraComp, tile->GetCoord());
				SET_POS_VEC(wall, pos);
			}
		}

		{
			{
				Tile* tile = TileManager::pathFindingTiles[40][81];
				Vector3 pos = tile->GetPos();

				Wall* wall = new Wall(eWallType::Stage1Wall3, cameraComp, tile->GetCoord());
				SET_POS_VEC(wall, pos);
			}
			{
				Tile* tile = TileManager::pathFindingTiles[40][79];
				Vector3 pos = tile->GetPos();

				Wall* wall = new Wall(eWallType::Stage1Wall3, cameraComp, tile->GetCoord());
				SET_POS_VEC(wall, pos);
			}
			{
				Tile* tile = TileManager::pathFindingTiles[40][77];
				Vector3 pos = tile->GetPos();

				Wall* wall = new Wall(eWallType::Stage1Wall3, cameraComp, tile->GetCoord());
				SET_POS_VEC(wall, pos);
			}
			{
				Tile* tile = TileManager::pathFindingTiles[40][75];
				Vector3 pos = tile->GetPos();

				Wall* wall = new Wall(eWallType::Stage1Wall3, cameraComp, tile->GetCoord());
				SET_POS_VEC(wall, pos);
			}
			{
				Tile* tile = TileManager::pathFindingTiles[40][73];
				Vector3 pos = tile->GetPos();

				Wall* wall = new Wall(eWallType::Stage1Wall3, cameraComp, tile->GetCoord());
				SET_POS_VEC(wall, pos);
			}
			{
				Tile* tile = TileManager::pathFindingTiles[40][71];
				Vector3 pos = tile->GetPos();

				Wall* wall = new Wall(eWallType::Stage1Wall3, cameraComp, tile->GetCoord());
				SET_POS_VEC(wall, pos);
			}
			{
				Tile* tile = TileManager::pathFindingTiles[40][69];
				Vector3 pos = tile->GetPos();

				Wall* wall = new Wall(eWallType::Stage1Wall3, cameraComp, tile->GetCoord());
				SET_POS_VEC(wall, pos);
			}
			{
				Tile* tile = TileManager::pathFindingTiles[40][67];
				Vector3 pos = tile->GetPos();

				Wall* wall = new Wall(eWallType::Stage1Wall3, cameraComp, tile->GetCoord());
				SET_POS_VEC(wall, pos);
			}
			{
				Tile* tile = TileManager::pathFindingTiles[40][65];
				Vector3 pos = tile->GetPos();

				Wall* wall = new Wall(eWallType::Stage1Wall3, cameraComp, tile->GetCoord());
				SET_POS_VEC(wall, pos);
			}
			{
				Tile* tile = TileManager::pathFindingTiles[40][63];
				Vector3 pos = tile->GetPos();

				Wall* wall = new Wall(eWallType::Stage1Wall3, cameraComp, tile->GetCoord());
				SET_POS_VEC(wall, pos);
			}
			{
				Tile* tile = TileManager::pathFindingTiles[40][61];
				Vector3 pos = tile->GetPos();

				Wall* wall = new Wall(eWallType::Stage1Wall3, cameraComp, tile->GetCoord());
				SET_POS_VEC(wall, pos);
			}
			{
				Tile* tile = TileManager::pathFindingTiles[40][59];
				Vector3 pos = tile->GetPos();

				Wall* wall = new Wall(eWallType::Stage1Wall3, cameraComp, tile->GetCoord());
				SET_POS_VEC(wall, pos);
			}

			{
				Tile* tile = TileManager::pathFindingTiles[56][57];
				Vector3 pos = tile->GetPos();

				Wall* wall = new Wall(eWallType::Stage1Wall3, cameraComp, tile->GetCoord());
				SET_POS_VEC(wall, pos);
			}
			{
				Tile* tile = TileManager::pathFindingTiles[50][57];
				Vector3 pos = tile->GetPos();

				Wall* wall = new Wall(eWallType::Stage1Wall3, cameraComp, tile->GetCoord());
				SET_POS_VEC(wall, pos);
			}

			{
				Tile* tile = TileManager::pathFindingTiles[66][81];
				Vector3 pos = tile->GetPos();

				Wall* wall = new Wall(eWallType::Stage1Wall3, cameraComp, tile->GetCoord());
				SET_POS_VEC(wall, pos);
			}
			{
				Tile* tile = TileManager::pathFindingTiles[66][79];
				Vector3 pos = tile->GetPos();

				Wall* wall = new Wall(eWallType::Stage1Wall3, cameraComp, tile->GetCoord());
				SET_POS_VEC(wall, pos);
			}
			{
				Tile* tile = TileManager::pathFindingTiles[66][77];
				Vector3 pos = tile->GetPos();

				Wall* wall = new Wall(eWallType::Stage1Wall3, cameraComp, tile->GetCoord());
				SET_POS_VEC(wall, pos);
			}
			{
				Tile* tile = TileManager::pathFindingTiles[66][75];
				Vector3 pos = tile->GetPos();

				Wall* wall = new Wall(eWallType::Stage1Wall3, cameraComp, tile->GetCoord());
				SET_POS_VEC(wall, pos);
			}
			{
				Tile* tile = TileManager::pathFindingTiles[66][73];
				Vector3 pos = tile->GetPos();

				Wall* wall = new Wall(eWallType::Stage1Wall3, cameraComp, tile->GetCoord());
				SET_POS_VEC(wall, pos);
			}
			{
				Tile* tile = TileManager::pathFindingTiles[66][71];
				Vector3 pos = tile->GetPos();

				Wall* wall = new Wall(eWallType::Stage1Wall3, cameraComp, tile->GetCoord());
				SET_POS_VEC(wall, pos);
			}
			{
				Tile* tile = TileManager::pathFindingTiles[66][69];
				Vector3 pos = tile->GetPos();

				Wall* wall = new Wall(eWallType::Stage1Wall3, cameraComp, tile->GetCoord());
				SET_POS_VEC(wall, pos);
			}
			{
				Tile* tile = TileManager::pathFindingTiles[66][67];
				Vector3 pos = tile->GetPos();

				Wall* wall = new Wall(eWallType::Stage1Wall3, cameraComp, tile->GetCoord());
				SET_POS_VEC(wall, pos);
			}
			{
				Tile* tile = TileManager::pathFindingTiles[66][65];
				Vector3 pos = tile->GetPos();

				Wall* wall = new Wall(eWallType::Stage1Wall3, cameraComp, tile->GetCoord());
				SET_POS_VEC(wall, pos);
			}
			{
				Tile* tile = TileManager::pathFindingTiles[66][63];
				Vector3 pos = tile->GetPos();

				Wall* wall = new Wall(eWallType::Stage1Wall3, cameraComp, tile->GetCoord());
				SET_POS_VEC(wall, pos);
			}
			{
				Tile* tile = TileManager::pathFindingTiles[66][61];
				Vector3 pos = tile->GetPos();

				Wall* wall = new Wall(eWallType::Stage1Wall3, cameraComp, tile->GetCoord());
				SET_POS_VEC(wall, pos);
			}
			{
				Tile* tile = TileManager::pathFindingTiles[66][59];
				Vector3 pos = tile->GetPos();

				Wall* wall = new Wall(eWallType::Stage1Wall3, cameraComp, tile->GetCoord());
				SET_POS_VEC(wall, pos);
			}

			{
				Tile* tile = TileManager::pathFindingTiles[44][55];
				Vector3 pos = tile->GetPos();

				Wall* wall = new Wall(eWallType::Stage1Wall3, cameraComp, tile->GetCoord());
				SET_POS_VEC(wall, pos);
			}
			{
				Tile* tile = TileManager::pathFindingTiles[44][53];
				Vector3 pos = tile->GetPos();

				Wall* wall = new Wall(eWallType::Stage1Wall3, cameraComp, tile->GetCoord());
				SET_POS_VEC(wall, pos);
			}
			{
				Tile* tile = TileManager::pathFindingTiles[44][51];
				Vector3 pos = tile->GetPos();

				Wall* wall = new Wall(eWallType::Stage1Wall3, cameraComp, tile->GetCoord());
				SET_POS_VEC(wall, pos);
			}
			{
				Tile* tile = TileManager::pathFindingTiles[44][49];
				Vector3 pos = tile->GetPos();

				Wall* wall = new Wall(eWallType::Stage1Wall3, cameraComp, tile->GetCoord());
				SET_POS_VEC(wall, pos);
			}
			{
				Tile* tile = TileManager::pathFindingTiles[44][47];
				Vector3 pos = tile->GetPos();

				Wall* wall = new Wall(eWallType::Stage1Wall3, cameraComp, tile->GetCoord());
				SET_POS_VEC(wall, pos);
			}
			{
				Tile* tile = TileManager::pathFindingTiles[44][45];
				Vector3 pos = tile->GetPos();

				Wall* wall = new Wall(eWallType::Stage1Wall3, cameraComp, tile->GetCoord());
				SET_POS_VEC(wall, pos);
			}

			{
				Tile* tile = TileManager::pathFindingTiles[60][45];
				Vector3 pos = tile->GetPos();

				Wall* wall = new Wall(eWallType::Stage1Wall3, cameraComp, tile->GetCoord());
				SET_POS_VEC(wall, pos);
			}
			{
				Tile* tile = TileManager::pathFindingTiles[60][47];
				Vector3 pos = tile->GetPos();

				Wall* wall = new Wall(eWallType::Stage1Wall3, cameraComp, tile->GetCoord());
				SET_POS_VEC(wall, pos);
			}
			{
				Tile* tile = TileManager::pathFindingTiles[60][49];
				Vector3 pos = tile->GetPos();

				Wall* wall = new Wall(eWallType::Stage1Wall3, cameraComp, tile->GetCoord());
				SET_POS_VEC(wall, pos);
			}
			{
				Tile* tile = TileManager::pathFindingTiles[60][51];
				Vector3 pos = tile->GetPos();

				Wall* wall = new Wall(eWallType::Stage1Wall3, cameraComp, tile->GetCoord());
				SET_POS_VEC(wall, pos);
			}
			{
				Tile* tile = TileManager::pathFindingTiles[60][53];
				Vector3 pos = tile->GetPos();

				Wall* wall = new Wall(eWallType::Stage1Wall3, cameraComp, tile->GetCoord());
				SET_POS_VEC(wall, pos);
			}
			{
				Tile* tile = TileManager::pathFindingTiles[60][55];
				Vector3 pos = tile->GetPos();

				Wall* wall = new Wall(eWallType::Stage1Wall3, cameraComp, tile->GetCoord());
				SET_POS_VEC(wall, pos);
			}
		}

		{}

		{
			{
				Tile* tile = TileManager::pathFindingTiles[65][82];
				Vector3 pos = tile->GetPos();

				Wall* wall = new Wall(eWallType::Stage1Wall2, cameraComp, tile->GetCoord());
				SET_POS_VEC(wall, pos);
			}
			{
				Tile* tile = TileManager::pathFindingTiles[63][82];
				Vector3 pos = tile->GetPos();

				Wall* wall = new Wall(eWallType::Stage1Wall2, cameraComp, tile->GetCoord());
				SET_POS_VEC(wall, pos);
			}
			{
				Tile* tile = TileManager::pathFindingTiles[61][82];
				Vector3 pos = tile->GetPos();

				Wall* wall = new Wall(eWallType::Stage1Wall2, cameraComp, tile->GetCoord());
				SET_POS_VEC(wall, pos);
			}
			{
				Tile* tile = TileManager::pathFindingTiles[59][82];
				Vector3 pos = tile->GetPos();

				Wall* wall = new Wall(eWallType::Stage1Wall2, cameraComp, tile->GetCoord());
				SET_POS_VEC(wall, pos);
			}
			{
				Tile* tile = TileManager::pathFindingTiles[57][82];
				Vector3 pos = tile->GetPos();

				Wall* wall = new Wall(eWallType::Stage1Wall2, cameraComp, tile->GetCoord());
				SET_POS_VEC(wall, pos);
			}
			{
				Tile* tile = TileManager::pathFindingTiles[55][82];
				Vector3 pos = tile->GetPos();

				Wall* wall = new Wall(eWallType::Stage1Wall2, cameraComp, tile->GetCoord());
				SET_POS_VEC(wall, pos);
			}
			{
				Tile* tile = TileManager::pathFindingTiles[53][82];
				Vector3 pos = tile->GetPos();

				Wall* wall = new Wall(eWallType::Stage1Wall2, cameraComp, tile->GetCoord());
				SET_POS_VEC(wall, pos);
			}
			{
				Tile* tile = TileManager::pathFindingTiles[51][82];
				Vector3 pos = tile->GetPos();

				Wall* wall = new Wall(eWallType::Stage1Wall2, cameraComp, tile->GetCoord());
				SET_POS_VEC(wall, pos);
			}
			{
				Tile* tile = TileManager::pathFindingTiles[49][82];
				Vector3 pos = tile->GetPos();

				Wall* wall = new Wall(eWallType::Stage1Wall2, cameraComp, tile->GetCoord());
				SET_POS_VEC(wall, pos);
			}
			{
				Tile* tile = TileManager::pathFindingTiles[47][82];
				Vector3 pos = tile->GetPos();

				Wall* wall = new Wall(eWallType::Stage1Wall2, cameraComp, tile->GetCoord());
				SET_POS_VEC(wall, pos);
			}
			{
				Tile* tile = TileManager::pathFindingTiles[45][82];
				Vector3 pos = tile->GetPos();

				Wall* wall = new Wall(eWallType::Stage1Wall2, cameraComp, tile->GetCoord());
				SET_POS_VEC(wall, pos);
			}
			{
				Tile* tile = TileManager::pathFindingTiles[43][82];
				Vector3 pos = tile->GetPos();

				Wall* wall = new Wall(eWallType::Stage1Wall2, cameraComp, tile->GetCoord());
				SET_POS_VEC(wall, pos);
			}
			{
				Tile* tile = TileManager::pathFindingTiles[41][82];
				Vector3 pos = tile->GetPos();

				Wall* wall = new Wall(eWallType::Stage1Wall2, cameraComp, tile->GetCoord());
				SET_POS_VEC(wall, pos);
			}

			{
				Tile* tile = TileManager::pathFindingTiles[45][58];
				Vector3 pos = tile->GetPos();

				Wall* wall = new Wall(eWallType::Stage1Wall2, cameraComp, tile->GetCoord());
				SET_POS_VEC(wall, pos);
			}
			{
				Tile* tile = TileManager::pathFindingTiles[43][58];
				Vector3 pos = tile->GetPos();

				Wall* wall = new Wall(eWallType::Stage1Wall2, cameraComp, tile->GetCoord());
				SET_POS_VEC(wall, pos);
			}
			{
				Tile* tile = TileManager::pathFindingTiles[41][58];
				Vector3 pos = tile->GetPos();

				Wall* wall = new Wall(eWallType::Stage1Wall2, cameraComp, tile->GetCoord());
				SET_POS_VEC(wall, pos);
			}
		}

		{

			{
				Tile* tile = TileManager::pathFindingTiles[47][58];
				Vector3 pos = tile->GetPos();

				Wall* wall = new Wall(eWallType::Stage1Wall2, cameraComp, tile->GetCoord());
				SET_POS_VEC(wall, pos);
			}
			{
				Tile* tile = TileManager::pathFindingTiles[49][58];
				Vector3 pos = tile->GetPos();

				Wall* wall = new Wall(eWallType::Stage1Wall2, cameraComp, tile->GetCoord());
				SET_POS_VEC(wall, pos);
			}
			{
				Tile* tile = TileManager::pathFindingTiles[57][56];
				Vector3 pos = tile->GetPos();

				Wall* wall = new Wall(eWallType::Stage1Wall2, cameraComp, tile->GetCoord());
				SET_POS_VEC(wall, pos);
			}
			{
				Tile* tile = TileManager::pathFindingTiles[65][58];
				Vector3 pos = tile->GetPos();

				Wall* wall = new Wall(eWallType::Stage1Wall2, cameraComp, tile->GetCoord());
				SET_POS_VEC(wall, pos);
			}
			{
				Tile* tile = TileManager::pathFindingTiles[63][58];
				Vector3 pos = tile->GetPos();

				Wall* wall = new Wall(eWallType::Stage1Wall2, cameraComp, tile->GetCoord());
				SET_POS_VEC(wall, pos);
			}
			{
				Tile* tile = TileManager::pathFindingTiles[61][58];
				Vector3 pos = tile->GetPos();

				Wall* wall = new Wall(eWallType::Stage1Wall2, cameraComp, tile->GetCoord());
				SET_POS_VEC(wall, pos);
			}
			{
				Tile* tile = TileManager::pathFindingTiles[59][58];
				Vector3 pos = tile->GetPos();

				Wall* wall = new Wall(eWallType::Stage1Wall2, cameraComp, tile->GetCoord());
				SET_POS_VEC(wall, pos);
			}
			{
				Tile* tile = TileManager::pathFindingTiles[57][58];
				Vector3 pos = tile->GetPos();

				Wall* wall = new Wall(eWallType::Stage1Wall2, cameraComp, tile->GetCoord());
				SET_POS_VEC(wall, pos);
			}
			{
				Tile* tile = TileManager::pathFindingTiles[51][56];
				Vector3 pos = tile->GetPos();

				Wall* wall = new Wall(eWallType::Stage1Wall2, cameraComp, tile->GetCoord());
				SET_POS_VEC(wall, pos);
			}
			{
				Tile* tile = TileManager::pathFindingTiles[49][56];
				Vector3 pos = tile->GetPos();

				Wall* wall = new Wall(eWallType::Stage1Wall2, cameraComp, tile->GetCoord());
				SET_POS_VEC(wall, pos);
			}
			{
				Tile* tile = TileManager::pathFindingTiles[47][56];
				Vector3 pos = tile->GetPos();

				Wall* wall = new Wall(eWallType::Stage1Wall2, cameraComp, tile->GetCoord());
				SET_POS_VEC(wall, pos);
			}
			{
				Tile* tile = TileManager::pathFindingTiles[45][56];
				Vector3 pos = tile->GetPos();

				Wall* wall = new Wall(eWallType::Stage1Wall2, cameraComp, tile->GetCoord());
				SET_POS_VEC(wall, pos);
			}
			{
				Tile* tile = TileManager::pathFindingTiles[59][44];
				Vector3 pos = tile->GetPos();

				Wall* wall = new Wall(eWallType::Stage1Wall2, cameraComp, tile->GetCoord());
				SET_POS_VEC(wall, pos);
			}
			{
				Tile* tile = TileManager::pathFindingTiles[57][44];
				Vector3 pos = tile->GetPos();

				Wall* wall = new Wall(eWallType::Stage1Wall2, cameraComp, tile->GetCoord());
				SET_POS_VEC(wall, pos);
			}
			{
				Tile* tile = TileManager::pathFindingTiles[55][44];
				Vector3 pos = tile->GetPos();

				Wall* wall = new Wall(eWallType::Stage1Wall2, cameraComp, tile->GetCoord());
				SET_POS_VEC(wall, pos);
			}
			{
				Tile* tile = TileManager::pathFindingTiles[53][44];
				Vector3 pos = tile->GetPos();

				Wall* wall = new Wall(eWallType::Stage1Wall2, cameraComp, tile->GetCoord());
				SET_POS_VEC(wall, pos);
			}
			{
				Tile* tile = TileManager::pathFindingTiles[51][44];
				Vector3 pos = tile->GetPos();

				Wall* wall = new Wall(eWallType::Stage1Wall2, cameraComp, tile->GetCoord());
				SET_POS_VEC(wall, pos);
			}
			{
				Tile* tile = TileManager::pathFindingTiles[49][44];
				Vector3 pos = tile->GetPos();

				Wall* wall = new Wall(eWallType::Stage1Wall2, cameraComp, tile->GetCoord());
				SET_POS_VEC(wall, pos);
			}
			{
				Tile* tile = TileManager::pathFindingTiles[47][44];
				Vector3 pos = tile->GetPos();

				Wall* wall = new Wall(eWallType::Stage1Wall2, cameraComp, tile->GetCoord());
				SET_POS_VEC(wall, pos);
			}
			{
				Tile* tile = TileManager::pathFindingTiles[45][44];
				Vector3 pos = tile->GetPos();

				Wall* wall = new Wall(eWallType::Stage1Wall2, cameraComp, tile->GetCoord());
				SET_POS_VEC(wall, pos);
			}


			{
				Tile* tile = TileManager::pathFindingTiles[59][56];
				Vector3 pos = tile->GetPos();

				Wall* wall = new Wall(eWallType::Stage1Wall2, cameraComp, tile->GetCoord());
				SET_POS_VEC(wall, pos);
			}

			{
				Tile* tile = TileManager::pathFindingTiles[51][56];
				Vector3 pos = tile->GetPos();

				Wall* wall = new Wall(eWallType::Stage1Wall2, cameraComp, tile->GetCoord());
				SET_POS_VEC(wall, pos);
			}
		}

		{
			Tile* tile = TileManager::pathFindingTiles[54][56];
			Vector3 pos = tile->GetPos();

			Wall* wall = new Wall(eWallType::Stage1Door, cameraComp, tile->GetCoord());
			SET_POS_VEC(wall, pos);
		}

		{
			Tile* tile = TileManager::pathFindingTiles[55][54];
			Vector3 pos = tile->GetPos();

			Wall* wall = new Wall(eWallType::Stage1Flag, cameraComp, tile->GetCoord());
			SET_POS_VEC(wall, pos);
		}

		{
			Tile* tile = TileManager::pathFindingTiles[52][54];
			Vector3 pos = tile->GetPos();

			Wall* wall = new Wall(eWallType::Stage1Flag, cameraComp, tile->GetCoord());
			SET_POS_VEC(wall, pos);
		}
		{
			Tile* tile = TileManager::pathFindingTiles[52][78];
			Vector3 pos = tile->GetPos();

			Wall* chair = new Wall(eWallType::Stage1Chair, cameraComp, tile->GetCoord());
			SET_POS_VEC(chair, pos);
		}
		{
			Tile* tile = TileManager::pathFindingTiles[53][54];
			Vector3 pos = tile->GetPos();
			Torch* torch = new Torch(pos, tile->GetCoord(), cameraComp, eTorchType::Stage1Torch1);
		}
		{
			Tile* tile = TileManager::pathFindingTiles[56][74];
			Vector3 pos = tile->GetPos();
			Torch* torch = new Torch(pos, tile->GetCoord(), cameraComp, eTorchType::Stage1Torch1);
		}
		{
			Tile* tile = TileManager::pathFindingTiles[49][74];
			Vector3 pos = tile->GetPos();
			Torch* torch = new Torch(pos, tile->GetCoord(), cameraComp, eTorchType::Stage1Torch1);
		}

		TileManager::MakeStageWall(0);

		TileManager::TileIsWallChange();
	}

	void PlayScene::MakeStage0Wall()
	{
		Camera* cameraComp = GetSceneMainCamera();
		TileManager::TileIsWallReset();
		{
			{
				Tile* tile = TileManager::pathFindingTiles[20][22];
				Vector3 pos = tile->GetPos();

				Wall* wall = new Wall(eWallType::Stage0Wall1, cameraComp, tile->GetCoord());
				SET_POS_VEC(wall, pos);
			}
		}
		TileManager::MakeStageWall(-1);
		TileManager::TileIsWallChange();
	}

	void PlayScene::Stage0()
	{
		SoundManager::ResetAllPlayed();
		SkillManager::AllSkillCrash();
		MonsterManager::EraseAll();
		FieldItemManager::EraseAll();
		ScreenEffectManager::FadeIn();
		MakeStage0Wall();
		dayLight->SetState(GameObject::RenderUpdate);
		StageManager::stageNum = (int)eBGMType::Stage0;
		if (curMap)
		{
			SET_MATERIAL(curMap, L"stage0");
		}

		fAcc = 0.f;
		bStageInit = false;
		bStageStart = true;

		mPortal->SetClickPortal(
			[=]()
			{
				Stage1();
			}
		);
		{
			Tile* tile = TileManager::pathFindingTiles[55][73];
			Vector3 pos = tile->GetPos();
			SET_POS_VEC(mNpc2, pos);
		}
		{
			Tile* tile = TileManager::pathFindingTiles[54][74];
			Vector3 pos = tile->GetPos();
			SET_POS_VEC(mNpc1, pos);
		}
		{
			Tile* tile = TileManager::pathFindingTiles[53][76];
			Vector3 pos = tile->GetPos();
			SET_POS_VEC(mPortal, pos);
		}
		{
			Tile* tile = TileManager::pathFindingTiles[25][27];
			TileManager::playerStandTile = tile;
			Vector3 pos = tile->GetPos();
			SET_POS_VEC(PlayerManager::player, pos);
		}

		for(int i = 0 ; i < 20; ++i )
		{
			{
				Tile* tile = TileManager::pathFindingTiles[30 + i][30];
				Vector3 pos = tile->GetPos();
				Monster* monster = new Monster(pos, MDFallen().fSpeed);
				SET_MAIN_CAMERA(monster);
				monster->SetCoord(tile->GetCoord());
				AddGameObject(eLayerType::Monster, monster);
				MonsterScript<MDFallen>* ms = ADD_COMP(monster, MonsterScript<MDFallen>);
			}
		}
		//{
		//	Tile* tile = TileManager::pathFindingTiles[30][30];
		//	Vector3 pos = tile->GetPos();
		//	Monster* monster = new Monster(pos, MDFallen().fSpeed);
		//	SET_MAIN_CAMERA(monster);
		//	monster->SetCoord(tile->GetCoord());
		//	AddGameObject(eLayerType::Monster, monster);
		//	MonsterScript<MDFallen>* ms = ADD_COMP(monster, MonsterScript<MDFallen>);
		//}
		
	}

	void PlayScene::Stage1()
	{
		SoundManager::ResetAllPlayed();
		SkillManager::AllSkillCrash();
		MonsterManager::EraseAll();
		FieldItemManager::EraseAll();
		ScreenEffectManager::FadeIn();
		MakeStage1Wall();
		dayLight->SetState(GameObject::NoRenderNoUpdate);
		StageManager::stageNum = (int)eBGMType::Stage1;

		if (curMap)
		{
			SET_MATERIAL(curMap, L"stage1");
		}

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
			Tile* tile = TileManager::pathFindingTiles[55][73];
			Vector3 pos = tile->GetPos();
			SET_POS_VEC(mNpc2, pos);
		}
		{
			Tile* tile = TileManager::pathFindingTiles[54][74];
			Vector3 pos = tile->GetPos();
			SET_POS_VEC(mNpc1, pos);
		}
		{
			Tile* tile = TileManager::pathFindingTiles[53][76];
			Vector3 pos = tile->GetPos();
			SET_POS_VEC(mPortal, pos);
		}

		{
			//Tile* tile = TileManager::pathFindingTiles[53][67];
			Tile* tile = TileManager::pathFindingTiles[52][47];
			TileManager::playerStandTile = tile;
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
		//}
		//{
		//	Tile* tile = TileManager::pathFindingTiles[50][51];
		//	Vector3 pos = tile->GetPos();
		//	Monster* monster = new Monster(pos, MDBalrog().fSpeed);
		//	SET_MAIN_CAMERA(monster);
		//	AddGameObject(eLayerType::Monster, monster);
		//	MonsterScript<MDBalrog>* ms = ADD_COMP(monster, MonsterScript<MDBalrog>);
		//}
		//{
		//	Tile* tile = TileManager::pathFindingTiles[53][77];
		//	Vector3 pos = tile->GetPos();
		//	Monster* monster = new Monster(pos, MDBalrog().fSpeed);
		//	SET_MAIN_CAMERA(monster);
		//	monster->SetCoord(tile->GetCoord());
		//	AddGameObject(eLayerType::Monster, monster);
		//	MonsterScript<MDBalrog>* ms = ADD_COMP(monster, MonsterScript<MDBalrog>);
		//}
		{
			Tile* tile = TileManager::pathFindingTiles[53][77];
			Vector3 pos = tile->GetPos();
			Monster* monster = new Monster(pos, MDAndariel().fSpeed);
			monster->SetCoord(tile->GetCoord());
			SET_MAIN_CAMERA(monster);
			AddGameObject(eLayerType::Monster, monster);
			MonsterScript<MDAndariel>* ms = ADD_COMP(monster, MonsterScript<MDAndariel>);

			mBossMonster = monster;
		}
		SoundManager::ExternVoiceSound((int)mBossMonster->GetMonsterType(), false);
	}

	void PlayScene::Stage2()
	{
		SoundManager::ResetAllPlayed();
		SkillManager::AllSkillCrash();
		StageManager::stageNum = (int)eBGMType::Stage2;
		dayLight->SetState(GameObject::NoRenderNoUpdate);
		MonsterManager::EraseAll();
		FieldItemManager::EraseAll();
		ScreenEffectManager::FadeIn();
		MakeStage2Wall();
		if (curMap)
		{
			SET_MATERIAL(curMap, L"stage2");
		}

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
			Tile* tile = TileManager::pathFindingTiles[52][54];
			Vector3 pos = tile->GetPos();
			SET_POS_VEC(mNpc2, pos);
		}
		{
			Tile* tile = TileManager::pathFindingTiles[52][52];
			Vector3 pos = tile->GetPos();
			SET_POS_VEC(mNpc1, pos);
		}
		{
			Tile* tile = TileManager::pathFindingTiles[50][56];
			Vector3 pos = tile->GetPos();
			SET_POS_VEC(mPortal, pos);
		}
		{
			Tile* tile = TileManager::pathFindingTiles[77][52];
			//Tile* tile = TileManager::pathFindingTiles[48][57];
			Vector3 pos = tile->GetPos();
			TileManager::playerStandTile = tile;
			SET_POS_VEC(PlayerManager::player, pos);
		}
		{
			Tile* tile = TileManager::pathFindingTiles[49][57];
			Vector3 pos = tile->GetPos();
			Monster* monster = new Monster(pos, MDDuriel().fSpeed);
			monster->SetCoord(tile->GetCoord());
			SET_MAIN_CAMERA(monster);
			AddGameObject(eLayerType::Monster, monster);
			MonsterScript<MDDuriel>* ms = monster->AddComponent<MonsterScript<MDDuriel>>();


			mBossMonster = monster;
		}
	}

	void PlayScene::Stage3()
	{
		SoundManager::ResetAllPlayed();
		StageManager::stageNum = (int)eBGMType::Stage3;
		MonsterManager::EraseAll();
		SkillManager::AllSkillCrash();
		dayLight->SetState(GameObject::NoRenderNoUpdate);
		FieldItemManager::EraseAll();
		ScreenEffectManager::FadeIn();
		MakeStage3Wall();

		mEnterNameUI->SetText(L"증오의 군주");
		fAcc = 0.f;
		bStageInit = false;
		bStageStart = true;
		if (curMap)
		{
			SET_MATERIAL(curMap, L"stage3");
		}
		mPortal->SetClickPortal(
			[=]()
			{
				Stage4();
			}
		);
		{
			Tile* tile = TileManager::pathFindingTiles[70][61];
			Vector3 pos = tile->GetPos();
			SET_POS_VEC(mNpc2, pos);
		}
		{
			Tile* tile = TileManager::pathFindingTiles[68][61];
			Vector3 pos = tile->GetPos();
			SET_POS_VEC(mNpc1, pos);
		}
		{
			Tile* tile = TileManager::pathFindingTiles[69][56];
			Vector3 pos = tile->GetPos();
			SET_POS_VEC(mPortal, pos);
		}
		{
			Tile* tile = TileManager::pathFindingTiles[26][54];
			TileManager::playerStandTile = tile;
			//Tile* tile = TileManager::pathFindingTiles[60][56];
			Vector3 pos = tile->GetPos();
			SET_POS_VEC(PlayerManager::player, pos);
		}
		//{
		//	Tile* tile = TileManager::pathFindingTiles[69][56];
		//	Vector3 pos = tile->GetPos();
		//	Monster* monster = new Monster(pos, MDBalrog().fSpeed);
		//	SET_MAIN_CAMERA(monster);
		//	monster->SetCoord(tile->GetCoord());
		//	AddGameObject(eLayerType::Monster, monster);
		//	MonsterScript<MDBalrog>* ms = ADD_COMP(monster, MonsterScript<MDBalrog>);
		//}
		{
			Tile* tile = TileManager::pathFindingTiles[69][56];
			Vector3 pos = tile->GetPos();
			Monster* monster = new Monster(pos, MDMephisto().fSpeed);
			monster->SetCoord(tile->GetCoord());
			SET_MAIN_CAMERA(monster);
			AddGameObject(eLayerType::Monster, monster);
			MonsterScript<MDMephisto>* ms = ADD_COMP(monster, MonsterScript<MDMephisto>);

			mBossMonster = monster;
		}
		SoundManager::ExternVoiceSound((int)mBossMonster->GetMonsterType(), false);
	}

	void PlayScene::Stage4()
	{
		SoundManager::ResetAllPlayed();
		SkillManager::AllSkillCrash();
		//StageManager::stageNum = (int)eBGMType::Stage4;
		StageManager::stageNum = 4 ;
		dayLight->SetState(GameObject::RenderUpdate);
		MonsterManager::EraseAll();
		FieldItemManager::EraseAll();
		ScreenEffectManager::FadeIn();
		MakeStage4Wall();
		if (curMap)
		{
			SET_MATERIAL(curMap, L"stage4");
		}

		ScreenEffectManager::Shake(3.f);
		{
			Tile* tile = TileManager::pathFindingTiles[23][23];
			TileManager::playerStandTile = tile;
			Vector3 pos = tile->GetPos();
			SET_POS_VEC(mPortal, pos);
		}



		mEnterNameUI->SetText(L"공포의 군주");
		fAcc = 0.f;
		bStageInit = false;
		bStageStart = true;
		//{
		//	GameObject* lavaLight = new GameObject();

		//	Light* lightComp = lavaLight->AddComponent<Light>();
		//	lightComp->SetType(eLightType::Directional);
		//	lightComp->SetColor(Vector4(0.7f, 0.7f, 0.7f, 1.0f));
		//	AddGameObject(eLayerType::Light, lavaLight);
		//	//lightComp->SetRadiusX(300.0f);
		//	//lightComp->SetRadiusY(150.0f);
		//}
		{
			//Tile* tile = TileManager::pathFindingTiles[24][24];
			Tile* tile = TileManager::pathFindingTiles[60][60];
			Vector3 pos = tile->GetPos();
			SET_POS_VEC(PlayerManager::player, pos);
		}
		{
			Floor* floor = new Floor(Vector3(0.f, 0.f, 0.f));
			Vector3 scale = GET_SCALE(floor);
			Tile* tile = TileManager::pathFindingTiles[0][0];
			Vector3 tilePos = tile->GetPos();
			Vector3 tileScale = tile->GetScale();
			tilePos.y += scale.y / 2.f;
			tilePos.y -= tileScale.y / 2.f;
			SET_POS_XYZ(floor, tilePos.x, tilePos.y, 2.1f);
			SET_MAIN_CAMERA(floor);
			AddGameObject(eLayerType::Floor, floor);
		}
		{
			Tile* tile = TileManager::pathFindingTiles[62][62];
			Vector3 pos = tile->GetPos();
			Monster* monster = new Monster(pos, MDDiablo().fSpeed);
			monster->SetCoord(tile->GetCoord());
			SET_MAIN_CAMERA(monster);
			AddGameObject(eLayerType::Monster, monster);
			MonsterScript<MDDiablo>* ms = ADD_COMP(monster, MonsterScript<MDDiablo>);

			mBossMonster = monster;
		}
		SoundManager::ExternVoiceSound((int)mBossMonster->GetMonsterType(), false);
		SoundManager::ExternAmbientSound(eAmbientType::Lava, true, 10.f);
	}

	void PlayScene::NPCRender()
	{
		//Vector3 nPos = GET_POS(PlayerManager::player);
		//SET_POS_VEC(mNpc1, nPos);
		//SET_POS_VEC(mNpc2, nPos);

		mNpc1->SetState(GameObject::RenderUpdate);
		mNpc2->SetState(GameObject::RenderUpdate);
	}

	void PlayScene::NPCNoRender()
	{
		mNpc1->SetState(GameObject::NoRenderUpdate);
		mNpc2->SetState(GameObject::NoRenderUpdate);
	}
}
