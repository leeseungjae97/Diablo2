#include "mMainMenuScene.h"

#include "../engine_source/mGameObject.h"
#include "../engine_source/mTransform.h"
#include "../engine_source/mMeshRenderer.h"
#include "../engine_source/mCamera.h"
#include "../engine_source/mSceneManager.h"
#include "../engine_source/mApplication.h"
#include "../engine_source/mRenderer.h"


#include "mCameraScript.h"
#include "mButton.h"
#include "mBackground.h"
#include "mBackgroundScript.h"
#include "mFontWrapper.h"

extern m::Application application;
namespace m
{
	MainMenuScene::MainMenuScene()
	{}
	MainMenuScene::~MainMenuScene()
	{}
	void MainMenuScene::Initialize()
	{
		Scene::Initialize();
		GameObject* camera = new GameObject();
		AddGameObject(eLayerType::UI, camera);

		SET_POS_XYZ(camera, 0.f, 0.f, -10.f);
		ADD_COMP(camera, CameraScript);
		SetSceneMainCamera(ADD_COMP(camera, Camera));
		GetSceneMainCamera()->TurnLayerMask(eLayerType::UI, true);

		SHARED_TEX tex;
		Background* back = new Background();
		AddGameObject(eLayerType::UI, back);
		SET_MAIN_CAMERA(back);
		SET_MESH(back, L"RectMesh");
		SET_MATERIAL(back, L"mainMenu2");
		SET_POS_XYZ(back, 0.f, 0.f, 1.0f);
		SET_SCALE_FULL(back, 0.f);

		Background* logo = new Background();
		AddGameObject(eLayerType::UI, logo);
		SET_MAIN_CAMERA(logo);
		SET_MESH(logo, L"RectMesh");
		SET_MATERIAL(logo, L"NoLightAnimationMaterial");
		ADD_COMP(logo, Animator);
		BackgroundScript* bgs = ADD_COMP(logo, BackgroundScript);
		bgs->SetAnimString(L"logos");
		tex = RESOURCE_FIND(Texture, L"test_logo");

		SET_POS_XYZ(logo, 0.f, RESOL_H_HEI - (tex->GetMetaDataHeight() * Texture::GetHeiRatio() / 2.f), 1.f);
		SET_SCALE_TEX_SIZE_WITH_RAT(logo, tex, 0.f);


		Button* btn1 = new Button();
		AddGameObject(eLayerType::UI, btn1);

		btn1->ClickMakeSound();
		btn1->HoverSoundMute();
		SET_MAIN_CAMERA(btn1);
		SET_MESH(btn1, L"RectMesh");
		SET_MATERIAL(btn1, L"btn0");
		GET_TEX(btn1, tex);
		SET_POS_XYZ(btn1, 0.f, RESOL_H_HEI - (288.f * Texture::GetHeiRatio()), 1.f);
		SET_SCALE_TEX_SIZE_WITH_RAT(btn1, tex, 0.0f);
		btn1->SetClickMaterial(RESOURCE_FIND(Material, L"btn0Click"));
		btn1->SetNormalMaterial(RESOURCE_FIND(Material, L"btn0"));
		btn1->SetClickFunction(
			[]() { SceneManager::LoadScene(L"SelectCharacterScene"); }
		);

		Button* btn2 = new Button();
		AddGameObject(eLayerType::UI, btn2);

		btn2->ClickMakeSound();
		btn2->HoverSoundMute();		
		SET_MAIN_CAMERA(btn2);
		SET_MESH(btn2, L"RectMesh");
		SET_MATERIAL(btn2, L"btn1");
		GET_TEX(btn2, tex);
		SET_POS_XYZ(btn2, 0.f, RESOL_H_HEI - ((288.f + tex->GetMetaDataHeight() )* Texture::GetHeiRatio() ), 1.f);
		SET_SCALE_TEX_SIZE_WITH_RAT(btn2, tex, 0.0f);
		btn2->SetClickMaterial(RESOURCE_FIND(Material, L"btn1Click"));
		btn2->SetNormalMaterial(RESOURCE_FIND(Material, L"btn1"));
		btn2->SetClickFunction(
			[]()
			{
				PostQuitMessage(0);
			}
		);
	}
	void MainMenuScene::Update()
	{
		Scene::Update();
		if (Input::GetKeyDown(eKeyCode::N))
		{
			SceneManager::LoadScene(L"SelectCharacterScene");
		}
	}
	void MainMenuScene::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void MainMenuScene::Render()
	{
		Scene::Render();
	}
}
