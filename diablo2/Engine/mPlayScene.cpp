#include "mPlayScene.h"

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
#include "mSkillUp.h"
#include "mCollider2D.h"
#include "mPlayerScript.h"
#include "mMonsterScript.h"
#include "mBottomUI.h"
#include "mUVUI.h"
#include "mPlayerInfo.h"
#include "mSkillShortCutButton.h"
#include "mParticleSystem.h"
#include "mOverlayEffectSkillScript.h"
#include "mFallScript.h"
#include "mTileSystem.h"
#include "mCameraScript.h"

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
		//std::shared_ptr<PaintShader> paintShader = Resources::Find<PaintShader>(L"PaintShader");
		//std::shared_ptr<Texture> paintTexture = Resources::Find<Texture>(L"PaintTexture");
		//paintShader->SetTarget(paintTexture);
		//paintShader->OnExcute();
		//Scene::Initialize();
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Monster, true);

		CollisionManager::SetLayer(eLayerType::Skill, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::Skill, eLayerType::Player, true);

		CollisionManager::SetLayer(eLayerType::PlayerSkill, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::MonsterSkill, eLayerType::Player, true);
		CollisionManager::SetLayer(eLayerType::Item, eLayerType::Item, true);

		SHARED_TEX tex;

		camera = new GameObject();
		//camera->SetName(L"Camera");
		AddGameObject(eLayerType::Camera, camera);
		SET_POS_XYZ(camera, 0.f, 0.f, -10.f);
		ADD_COMP(camera, CameraScript);
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
		Vector3 centerPos = GET_POS(centerTile);

		SET_POS_XYZ(map, centerPos.x, centerPos.y , 1.f);

		PlayerInfo::Initialize();

		SET_MAIN_CAMERA(PlayerInfo::player);
		AddGameObject(eLayerType::Player, PlayerInfo::player);
		ADD_COMP(PlayerInfo::player, PlayerScript);
		GetSceneMainCamera()->SetFollowObject(PlayerInfo::player);

		//GameObject* qwe = new GameObject();
		//SET_MAIN_CAMERA(qwe);
		//AddGameObject(eLayerType::Skill, qwe);
		//ADD_COMP(qwe, MeshRenderer);
		//ADD_COMP(qwe, Animator);
		//SET_MESH(qwe, L"RectMesh");
		//SET_MATERIAL(qwe, L"AnimationMaterial");
		//SET_SCALE_XYZ(qwe, 100.f, 100.f, 1.f);
		//FallScript * fs = qwe->AddComponent<FallScript>(eAccessorySkillType::Blizzard1);
		//fs->SkillFire();

		//GameObject* particle = new GameObject();
		//SET_MAIN_CAMERA(particle);
		//particle->SetName(L"Particle");
		//AddGameObject(eLayerType::Skill, particle);
		//ParticleSystem* mr = particle->AddComponent<ParticleSystem>();
		//particle->GetComponent<Transform>()->SetPosition(Vector3(0.f, 0.f, 1.f));
		//particle->GetComponent<Transform>()->SetScale(Vector3(0.2f, 0.2f, 1.f));

		{
			Monster* monster = new Monster(centerPos, MDDiablo().fSpeed);
			SET_MAIN_CAMERA(monster);
			AddGameObject(eLayerType::Monster, monster);
			SET_MESH(monster, L"RectMesh");
			SET_MATERIAL(monster, L"AnimationMaterial");
			ADD_COMP(monster, Animator);
			MonsterScript<MDDiablo>* ms = ADD_COMP(monster, MonsterScript<MDDiablo>);
			monster->SetMonsterClass(ms->GetMonsterClass());
		}
	

		//for(int i = 0 ; i < 30; ++i)
		//{
		//	
		//}
		

		GameObject* light = new GameObject();
		light->SetName(L"Smile");
		AddGameObject(eLayerType::Light, light);
		Light* lightComp = light->AddComponent<Light>();
		lightComp->SetType(eLightType::Directional);
		lightComp->SetColor(Vector4(0.5f, 0.5f, 0.5f,0.5f));
		lightComp->SetAngle(45.f);
		{
			GameObject* light = new GameObject();
			light->SetName(L"Smile");
			AddGameObject(eLayerType::Light, light);
			Light* lightComp = light->AddComponent<Light>();
			lightComp->SetType(eLightType::Directional);
			lightComp->SetColor(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
			lightComp->SetAngle(45.f);
		}

		GameObject* uiCamera = new GameObject();
		SET_POS_XYZ(uiCamera, 0.0f, 0.0f, -1.f);
		Camera* cameraComp2 = ADD_COMP(uiCamera, Camera);
		cameraComp2->TurnLayerMask(eLayerType::Player, false);
		AddGameObject(eLayerType::Camera, uiCamera);

		//inventory = new Inventory(cameraComp2);
		//inventory->SetState(GameObject::NoRenderUpdate);

		//skillUp = new SkillUp(cameraComp2);
		//skillUp->SetState(GameObject::NoRenderUpdate);

		//uiBottomBar = new BottomUI(cameraComp2);

		UI* uiMp = new UI();
		AddGameObject(eLayerType::UI, uiMp);
		uiMp->SetCamera(cameraComp2);
		SET_MESH(uiMp, L"RectMesh");
		SET_MATERIAL(uiMp, L"mpUi");
		GET_TEX(uiMp, tex);
		SET_SCALE_TEX_SIZE_WITH_RAT(uiMp, tex, 0.f);
		SET_POS_XYZ(uiMp, RESOL_H_WID - 117.f * Texture::GetWidRatio() / 2.f
					, -RESOL_H_HEI + 104.f * Texture::GetHeiRatio() / 2.f, -1.f);

	
		UVUI* mp = new UVUI();
		AddGameObject(eLayerType::UI, mp);
		mp->SetCamera(cameraComp2);
		SET_MESH(mp, L"RectMesh");
		SET_MATERIAL(mp, L"mp");
		GET_TEX(mp, tex);
		SET_SCALE_TEX_SIZE_WITH_RAT(mp, tex, 0.f);
		SET_POS_XYZ(mp, RESOL_H_WID - 140.f * Texture::GetWidRatio() / 2.f
					, -RESOL_H_HEI + 105.f * Texture::GetHeiRatio() / 2.f, -1.f);


		UI* mpOverlapHands = new UI();
		AddGameObject(eLayerType::UI, mpOverlapHands);
		mpOverlapHands->SetCamera(cameraComp2);
		SET_MESH(mpOverlapHands, L"RectMesh");
		SET_MATERIAL(mpOverlapHands, L"mpOverlapHands");
		GET_TEX(mpOverlapHands, tex);
		SET_SCALE_TEX_SIZE_WITH_RAT(mpOverlapHands, tex, 0.f);
		SET_POS_XYZ(mpOverlapHands, RESOL_H_WID - 135.f * Texture::GetWidRatio() / 2.f
					, -RESOL_H_HEI + 105.f * Texture::GetHeiRatio() / 2.f, -1.f);
		
		UI* uiHp = new UI();
		AddGameObject(eLayerType::UI, uiHp);
		uiHp->SetCamera(cameraComp2);
		SET_MESH(uiHp, L"RectMesh");
		SET_MATERIAL(uiHp, L"hpUi");
		GET_TEX(uiHp, tex);
		SET_SCALE_TEX_SIZE_WITH_RAT(uiHp, tex, 0.f);
		SET_POS_XYZ(uiHp, -RESOL_H_WID + 117.f * Texture::GetWidRatio() / 2.f
					, -RESOL_H_HEI + 105.f * Texture::GetHeiRatio() / 2.f, -1.f);

		UVUI* hp = new UVUI();
		AddGameObject(eLayerType::UI, hp);
		hp->SetCamera(cameraComp2);
		hp->SetName(L"hp");
		SET_MESH(hp, L"RectMesh");
		SET_MATERIAL(hp, L"hp");
		GET_TEX(hp, tex);
		SET_SCALE_TEX_SIZE_WITH_RAT(hp, tex, 0.f);
		SET_POS_XYZ(hp, -RESOL_H_WID + 138.f * Texture::GetWidRatio() / 2.f
					, -RESOL_H_HEI + 105.f * Texture::GetHeiRatio() / 2.f, -1.f);

		PlayerInfo::player->SetHpUI(hp);

		UI* hpOverlapHands = new UI();
		AddGameObject(eLayerType::UI, hpOverlapHands);
		hpOverlapHands->SetCamera(cameraComp2);
		SET_MESH(hpOverlapHands, L"RectMesh");
		SET_MATERIAL(hpOverlapHands, L"hpOverlapHands");
		GET_TEX(hpOverlapHands, tex);
		SET_SCALE_TEX_SIZE_WITH_RAT(hpOverlapHands, tex, 0.f);
		SET_POS_XYZ(hpOverlapHands, RESOL_H_WID + 137.f * Texture::GetWidRatio() / 2.f
					, -RESOL_H_HEI + 97.f * Texture::GetHeiRatio() / 2.f, -1.f);

		SkillShortCutButton* skillShortCutLeft = new SkillShortCutButton(0);
		AddGameObject(eLayerType::UI, skillShortCutLeft);
		skillShortCutLeft->SetCamera(cameraComp2);
		SET_MESH(skillShortCutLeft, L"RectMesh");
		SET_MATERIAL(skillShortCutLeft, L"normalAttackIcon");

		GET_TEX(skillShortCutLeft, tex);
		SET_SCALE_TEX_SIZE_WITH_RAT(skillShortCutLeft, tex, 0.f);
		SET_POS_XYZ(skillShortCutLeft, -470.f - tex->GetMetaDataWidth() * Texture::GetWidRatio() / 2.f
					, -RESOL_H_HEI + tex->GetMetaDataHeight() * Texture::GetHeiRatio() / 2.f, -1.f);

		SkillShortCutButton* skillShortCutRight = new SkillShortCutButton(1);
		AddGameObject(eLayerType::UI, skillShortCutRight);
		skillShortCutRight->SetCamera(cameraComp2);
		SET_MESH(skillShortCutRight, L"RectMesh");
		SET_MATERIAL(skillShortCutRight, L"normalAttackIcon");

		GET_TEX(skillShortCutRight, tex);
		SET_SCALE_TEX_SIZE_WITH_RAT(skillShortCutRight, tex, 0.f);
		SET_POS_XYZ(skillShortCutRight, 470.f + tex->GetMetaDataWidth() * Texture::GetWidRatio() / 2.f
					, -RESOL_H_HEI + tex->GetMetaDataHeight() * Texture::GetHeiRatio() / 2.f, -1.f);
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