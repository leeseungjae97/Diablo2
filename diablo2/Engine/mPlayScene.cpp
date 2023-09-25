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
#include "mNPC.h"

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
		//std::shared_ptr<PaintShader> paintShader = Resources::Find<PaintShader>(L"PaintShader");
		//std::shared_ptr<Texture> paintTexture = Resources::Find<Texture>(L"PaintTexture");
		//paintShader->SetTarget(paintTexture);
		//paintShader->OnExcute();
		//Scene::Initialize();
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
		//camera->SetName(L"Camera");
		AddGameObject(eLayerType::Camera, camera);
		SET_POS_XYZ(camera, 0.f, 0.f, -10.f);
		//ADD_COMP(camera, CameraScript);
		ADD_COMP(camera, AudioListener);
		Camera* cameraComp = ADD_COMP(camera, Camera);
		SetSceneMainCamera(cameraComp);
		cameraComp->TurnLayerMask(eLayerType::UI, false);
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

		Tile* tile5 = TileManager::pathFindingTiles[0][1];
		Vector3 pos4 = tile5->GetPos();

		//GameObject* qwe = new GameObject();
		//SET_MAIN_CAMERA(qwe);
		//AddGameObject(eLayerType::Skill, qwe);
		//ADD_COMP(qwe, MeshRenderer);
		////Animator* anim = ADD_COMP(qwe, Animator);
		//SET_POS_VEC(qwe, pos4);

		//SET_MESH(qwe, L"RectMesh");

		//SHARED_MAT mat1 = RESOURCE_FIND(Material, L"balrogAttackRH");
		//SHARED_MAT mat2 = RESOURCE_FIND(Material, L"fire2s");
		//std::shared_ptr<Texture> tex3 = RESOURCE_FIND(Texture, L"fire_3");


		//std::vector<std::shared_ptr<Texture>> texes;

		//texes.push_back(mat1->GetTexture());
		//texes.push_back(mat2->GetTexture());
		//texes.push_back(tex3);

		//GUID format = GetWICCodec(WIC_CODEC_PNG);
		//SaveToWICFile(
		//	*mat1->GetTexture()->GetScratchImage().GetImage(0, 0, 0)
		//	//*mat1->GetTexture()->GetScratchImage().GetImages()
		//	, WIC_FLAGS::WIC_FLAGS_NONE
		//	, format
		//	, L"save1.png"
		//	, nullptr
		//);

		//std::shared_ptr<Texture> mergeTexture = std::make_shared<Texture>();
		//mergeTexture->MergeTex2(texes
		//	, mat1->GetTexture()->GetMetaDataWidth()
		//	, mat1->GetTexture()->GetMetaDataHeight()
		//	, 1
		//);

		//Resources::Insert(L"mergeFireImage", mergeTexture);

		//std::shared_ptr<Material> mat5 = std::make_shared<Material>();
		//mat5->SetShader(RESOURCE_FIND(Shader, L"SpriteShader"));
		////mat5->SetRenderingMode(eRenderingMode::Transparent);
		//mat5->SetTexture(mergeTexture);

		//SET_MATERIAL_D(qwe, mat5);
		//SET_SCALE_TEX_SIZE(qwe, mergeTexture, 1.f);
		//SET_MATERIAL(qwe, L"AnimationMaterial");

		//SET_MATERIAL(qwe, L"fire3");
		//MAKE_GET_TEX(qwe, tex);
		//SET_SCALE_TEX_SIZE(qwe, tex, 1.f);


		//fire_1_s
		//fire_2_s
		//fire_3_s

		//Resources\sound\ambient\creature;


		//eSkillCrashType mCrashType = skillCrashTypes[(int)eSkillType::meteor];
		//SHARED_MAT crashMat = RESOURCE_FIND(Material, L"fireCrash2");

		//anim->Create(
		//	L"fireCrash2anim"
		//	, crashMat->GetTexture()
		//	, Vector2::Zero
		//	, crashSizes[(int)mCrashType]
		//	, crashLength[(int)mCrashType]
		//	, Vector2::Zero
		//	, 0.03f
		//);
		//anim->PlayAnimation(L"fireCrash2anim", true);

		//GameObject* particle = new GameObject();
		//SET_MAIN_CAMERA(particle);
		//particle->SetName(L"Particle");
		//AddGameObject(eLayerType::Skill, particle);
		//ParticleSystem* mr = particle->AddComponent<ParticleSystem>();
		//particle->GetComponent<Transform>()->SetPosition(Vector3(0.f, 0.f, 1.f));
		//particle->GetComponent<Transform>()->SetScale(Vector3(0.2f, 0.2f, 1.f));

		//{
		//	Monster* monster = new Monster(centerPos, MDDiablo().fSpeed);
		//	SET_MAIN_CAMERA(monster);
		//	AddGameObject(eLayerType::Monster, monster);
		//	SET_MESH(monster, L"RectMesh");
		//	SET_MATERIAL(monster, L"AnimationMaterial");
		//	ADD_COMP(monster, Animator);
		//	MonsterScript<MDDiablo>* ms = ADD_COMP(monster, MonsterScript<MDDiablo>);
		//	monster->SetMonsterClass(ms->GetMonsterClass());
		//}


		//for(int i = 0 ; i < 10; ++i)
		//{
		//	int xRand = rand() % TileManager::tileXLen;
		//	int yRand = rand() % TileManager::tileYLen;
		//	Vector3 randPos = GET_POS(TileManager::pathFindingTiles[xRand][yRand]);
		//	TileManager::pathFindingTiles[xRand][yRand]->SetOnMonster(true);
		//	{
		//		Monster* monster = new Monster(randPos, MDBalrog().fSpeed);
		//		SET_MAIN_CAMERA(monster);
		//		AddGameObject(eLayerType::Monster, monster);
		//		SET_MESH(monster, L"RectMesh");
		//		SET_MATERIAL(monster, L"AnimationMaterial");
		//		ADD_COMP(monster, Animator);
		//		MonsterScript<MDBalrog>* ms = ADD_COMP(monster, MonsterScript<MDBalrog>);
		//		monster->SetMonsterClass(ms->GetMonsterClass());
		//	}
		//}

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
		//	Tile* tile = TileManager::pathFindingTiles[80][40];
		//	Vector3 pos = tile->GetPos();
		//	Monster* monster = new Monster(pos, MDDuriel().fSpeed);
		//	SET_MAIN_CAMERA(monster);
		//	AddGameObject(eLayerType::Monster, monster);
		//	SET_MESH(monster, L"RectMesh");
		//	SET_MATERIAL(monster, L"AnimationMaterial");
		//	ADD_COMP(monster, Animator);
		//	MonsterScript<MDDuriel>* ms = ADD_COMP(monster, MonsterScript<MDDuriel>);
		//	monster->SetMonsterClass(ms->GetMonsterClass());
		//}

		{
			Tile* tile = TileManager::pathFindingTiles[50][50];
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
		/*{
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
			Tile* tile = TileManager::pathFindingTiles[50][52];
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
		}*/
		{
			Tile* tile = TileManager::pathFindingTiles[50][53];
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
		//{
		//	Tile* tile = TileManager::pathFindingTiles[50][54];
		//	Vector3 pos = tile->GetPos();
		//	Monster* monster = new Monster(pos, MDBalrog().fSpeed);
		//	SET_MAIN_CAMERA(monster);
		//	AddGameObject(eLayerType::Monster, monster);
		//	SET_MESH(monster, L"RectMesh");
		//	SET_MATERIAL(monster, L"AnimationMaterial");
		//	ADD_COMP(monster, Animator);
		//	MonsterScript<MDBalrog>* ms = ADD_COMP(monster, MonsterScript<MDBalrog>);
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
	/*	{
			Tile* tile = TileManager::pathFindingTiles[60][51];
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
			Tile* tile = TileManager::pathFindingTiles[60][52];
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
			Tile* tile = TileManager::pathFindingTiles[60][53];
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
		}*/
		{
			Tile* tile = TileManager::pathFindingTiles[60][54];
			Vector3 pos = tile->GetPos();
			Monster* monster = new Monster(pos, MDBalrog().fSpeed);
			SET_MAIN_CAMERA(monster);
			AddGameObject(eLayerType::Monster, monster);
			
			MonsterScript<MDBalrog>* ms = ADD_COMP(monster, MonsterScript<MDBalrog>);
			monster->SetMonsterClass(ms->GetMonsterClass());
			monster->SetMonsterName(ms->GetcurMonsterData().wsMonsterName);
			monster->SetHpCapacity(ms->GetcurMonsterData().hp);
		}

		FieldItem* testField = new FieldItem(eItem::hpPosion1, Vector3(10.f, 10.f, 1.f));
		SET_MAIN_CAMERA(testField);
		AddGameObject(eLayerType::FieldItem, testField);

		//for(int i = 0 ; i < 30; ++i)
		//{
		//	Monster* monster = new Monster(centerPos, MDBalrog().fSpeed);
		//	SET_MAIN_CAMERA(monster);
		//	AddGameObject(eLayerType::Monster, monster);
		//	SET_MESH(monster, L"RectMesh");
		//	SET_MATERIAL(monster, L"AnimationMaterial");
		//	ADD_COMP(monster, Animator);
		//	MonsterScript<MDBalrog>* ms = ADD_COMP(monster, MonsterScript<MDBalrog>);
		//	monster->SetMonsterClass(ms->GetMonsterClass());
		//}
		//

		//GameObject* light = new GameObject();
		//light->SetName(L"Smile");
		//AddGameObject(eLayerType::Light, light);
		//Light* lightComp = light->AddComponent<Light>();
		//lightComp->SetType(eLightType::Directional);
		//lightComp->SetColor(Vector4(0.5f, 0.5f, 0.5f,0.5f));
		//lightComp->SetAngle(45.f);
		//{
		//	GameObject* light = new GameObject();
		//	light->SetName(L"Smile");
		//	AddGameObject(eLayerType::Light, light);
		//	Light* lightComp = light->AddComponent<Light>();
		//	lightComp->SetType(eLightType::Directional);
		//	lightComp->SetColor(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
		//	lightComp->SetAngle(45.f);
		//}

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

		EnemyHpUI* eHpUI = new EnemyHpUI(Vector3(0.f, 0.f, -1.f));
		eHpUI->SetCamera(cameraComp2);
		eHpUI->SetFontSize(20.f);
		AddGameObject(eLayerType::UI, eHpUI);

		NPC* npc1 = new NPC(GET_POS(PlayerManager::player), eNPCType::ConsumNPC);
		SET_MAIN_CAMERA(npc1);
		AddGameObject(eLayerType::NPC, npc1);
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