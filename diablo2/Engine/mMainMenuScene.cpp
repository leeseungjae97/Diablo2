#include "mMainMenuScene.h"

#include "../engine_source/mGameObject.h"
#include "../engine_source/mTransform.h"
#include "../engine_source/mMeshRenderer.h"
#include "../engine_source/mCamera.h"
#include "../engine_source/mSceneManager.h"
//#include "../engine_source/mFontWrapper.h"
#include "../engine_source/mRenderer.h"


#include "mCameraScript.h"
#include "mButton.h"
#include "mBackground.h"
#include "mBackgroundScript.h"
#include "mFontWrapper.h"

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
		//camera->SetName(L"Camera");
		AddGameObject(eLayerType::UI, camera);

		SET_POS_XYZ(camera, 0.f, 0.f, -10.f);
		ADD_COMP(camera, CameraScript);
		SetSceneMainCamera(ADD_COMP(camera, Camera));
		GetSceneMainCamera()->TurnLayerMask(eLayerType::UI, true);

		//GameObject* grid = new GameObject();
		//grid->SetName(L"Grid");
		//AddGameObject(eLayerType::Grid, grid);
		//MeshRenderer* mr = grid->AddComponent<MeshRenderer>();
		//grid->GetComponent<Transform>()->SetPosition(Vector3(-800.f, -450.f, 0.999f));
		//mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		//mr->SetMaterial(Resources::Find<Material>(L"GridMaterial"));
		//GridScript* gridSc = grid->AddComponent<GridScript>();
		//gridSc->SetCamera(cameraComp);

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
		SET_MATERIAL(logo, L"AnimationMaterial");
		ADD_COMP(logo, Animator);
		BackgroundScript* bgs = ADD_COMP(logo, BackgroundScript);
		bgs->SetAnimString(L"logos");
		tex = RESOURCE_FIND(Texture, L"test_logo");

		SET_POS_XYZ(logo, 0.f, RESOL_H_HEI - (tex->GetMetaDataHeight() * Texture::GetHeiRatio() / 2.f), 1.f);
		SET_SCALE_TEX_SIZE_WITH_RAT(logo, tex, 0.f);


		Button* btn1 = new Button();
		AddGameObject(eLayerType::UI, btn1);

		btn1->SetText(L"게임시작");
		btn1->SetTextSize(30.f);
		btn1->SetTextColor(Vector4(255.f, 1.f, 255.f, 255.f));
		SET_MAIN_CAMERA(btn1);
		SET_MESH(btn1, L"RectMesh");
		SET_MATERIAL(btn1, L"mWideButtonBlank");
		GET_TEX(btn1, tex);
		SET_POS_XYZ(btn1, 0.f, RESOL_H_HEI - (288.f * Texture::GetHeiRatio()), 1.f);
		SET_SCALE_TEX_SIZE_WITH_RAT(btn1, tex, 0.0f);
		btn1->SetClickMaterial(RESOURCE_FIND(Material, L"mWideButtonBlankClick"));
		btn1->SetNormalMaterial(RESOURCE_FIND(Material, L"mWideButtonBlank"));
		btn1->SetClickFunction(
			[]() { SceneManager::LoadScene(L"SelectCharacterScene"); }
		);

		//FontWrapper::DrawFont(L"TEST", 10, 10, 100, FONT_RGBA(255, 0, 255, 255));
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
