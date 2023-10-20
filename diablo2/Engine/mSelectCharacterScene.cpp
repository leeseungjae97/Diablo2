#include "mSelectCharacterScene.h"

#include "../engine_source/mSceneManager.h"
#include "../engine_source/mCamera.h"
#include "../engine_source/mTransform.h"
#include "../engine_source/mGameObject.h"
#include "../engine_source/mMeshRenderer.h"
#include "../engine_source/mResources.h"
#include "../engine_source/mFontWrapper.h"

#include "mBackground.h"
#include "mButton.h"
#include "mLight.h"
#include "mLightObject.h"
#include "mPlayerStatus.h"
#include "mTextInputUI.h"

namespace m
{
	SelectCharacterScene::SelectCharacterScene()
	{
	}
	SelectCharacterScene::~SelectCharacterScene()
	{
	}
	void SelectCharacterScene::Initialize()
	{
		Scene::Initialize();

		SHARED_TEX tex;

		GameObject* camera = new GameObject();
		//camera->SetName(L"Camera");
		AddGameObject(eLayerType::UI, camera);
		SET_POS_XYZ(camera, 0.f, 0.f, -10.0f);
		SetSceneMainCamera(camera->AddComponent<Camera>());

		Background* back = new Background();
		AddGameObject(eLayerType::UI, back);
		SET_MAIN_CAMERA(back);
		SET_MESH(back, L"RectMesh");
		SET_MATERIAL(back, L"characterSelect1");
		SET_POS_XYZ(back, 0.f, 0.f, 1.f);
		SET_SCALE_FULL(back, 0.f);

		Button* exitBtn = new Button();
		AddGameObject(eLayerType::UI, exitBtn);
		exitBtn->ClickMakeSound();
		exitBtn->HoverSoundMute();
		SET_MAIN_CAMERA(exitBtn);
		SET_MESH(exitBtn, L"RectMesh");
		SET_MATERIAL(exitBtn, L"btn2");
		GET_TEX(exitBtn, tex);
		exitBtn->SetClickMaterial(RESOURCE_FIND(Material, L"btn2Click"));
		exitBtn->SetNormalMaterial(RESOURCE_FIND(Material, L"btn2"));
		exitBtn->SetClickFunction(
			[]()
			{
			    SceneManager::LoadScene(L"MainMenuScene");
			});
		SET_POS_XYZ(exitBtn, 34.f + -RESOL_H_WID + 126.f * Texture::GetWidRatio() / 2.f, 27.f + -RESOL_H_HEI + 35.f * Texture::GetHeiRatio() / 2.f, 1.f);
		SET_SCALE_TEX_SIZE_WITH_RAT(exitBtn, tex, 1.f);

		mGameStart = new Button();
		mGameStart->HoverSoundMute();
		mGameStart->ClickMakeSound();
		mGameStart->ClickDisable();
		SET_MAIN_CAMERA(mGameStart);
		SET_MESH(mGameStart, L"RectMesh");
		SET_MATERIAL(mGameStart, L"btn3Disable");
		mGameStart->SetClickMaterial(RESOURCE_FIND(Material, L"btn3Click"));
		mGameStart->SetNormalMaterial(RESOURCE_FIND(Material, L"btn3Disable"));
		mGameStart->SetClickFunction(
			[]()
			{
				SceneManager::LoadScene(L"PlayScene");
			});
		GET_TEX(mGameStart, tex);
		SET_POS_XYZ(mGameStart, RESOL_H_WID - 110.f * Texture::GetWidRatio(), 27.f + -RESOL_H_HEI + 35.f * Texture::GetHeiRatio() / 2.f, 1.f);
		SET_SCALE_TEX_SIZE_WITH_RAT(mGameStart, tex, 0.0f);
		AddGameObject(eLayerType::UI, mGameStart);

		makeUI();
	}
	void SelectCharacterScene::Update()
	{
		Scene::Update();
		if (Input::GetKeyDown(eKeyCode::N))
		{
			SceneManager::LoadScene(L"PlayScene");
		}
		if(mTIU->GetTextLen() >= 2)
		{
			PlayerStatus::playerName = mTIU->GetText();
			mGameStart->Clickable();
			//SET_MATERIAL(mGameStart, L"btn3");
			mGameStart->SetNormalMaterial(RESOURCE_FIND(Material, L"btn3"));
		}else
		{
			mGameStart->ClickDisable();
			//SET_MATERIAL(mGameStart, L"btn3Disable");
			mGameStart->SetNormalMaterial(RESOURCE_FIND(Material, L"btn3Disable"));
		}
	}
	void SelectCharacterScene::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void SelectCharacterScene::Render()
	{
		Scene::Render();
	}

	void SelectCharacterScene::makeUI()
	{
		mTextClass = new UI();
		mTextClass->HoverSoundMute();
		mTextClass->SetText(L"소서리스");
		mTextClass->SetTextSize(50.f);
		mTextClass->SetTextNormalColor(Vector4(255.f, 255.f, 255.f, 255.f));

		mTextClassEx = new UI();
		mTextClassEx->HoverSoundMute();
		mTextClassEx->SetText(L"그녀는 자연 친화적 삶을 통해 불과 물, 그리고\n번개등의 마법을 터득했습니다.");
		mTextClassEx->SetTextNormalColor(Vector4(255.f, 255.f, 255.f, 255.f));
		mTextClassEx->SetTextSize(35.f);

		SET_MAIN_CAMERA(mTextClassEx);
		SET_MAIN_CAMERA(mTextClass);

		SET_MESH(mTextClassEx, L"RectMesh");
		SET_MESH(mTextClass, L"RectMesh");

		SET_MATERIAL(mTextClassEx, L"noneRect");
		SET_MATERIAL(mTextClass, L"noneRect");

		Vector2 size = FontWrapper::GetTextSize(L"소서리스", 50.f);
		SET_POS_XYZ(mTextClass, 0.f, RESOL_H_HEI - size.y - (80.f * Texture::GetHeiRatio()), 1.f);
		SET_SCALE_XYZ(mTextClass, size.x, size.y, 1.f);

		size = FontWrapper::GetTextSize(L"그녀는 자연 친화적 삶을 통해 불과 물, 그리고\n번개등의 마법을 터득했습니다.", 25.f);
		SET_POS_XYZ(mTextClassEx, 0.f, RESOL_H_HEI - size.y - (115.f * Texture::GetHeiRatio()), 1.f);
		SET_SCALE_XYZ(mTextClassEx, size.x, size.y, 1.f);

		AddGameObject(eLayerType::UI, mTextClass);
		AddGameObject(eLayerType::UI, mTextClassEx);

		GameObject* sorceressloop = new GameObject();
		ADD_COMP(sorceressloop, MeshRenderer);
		Animator* animator = ADD_COMP(sorceressloop, Animator);
		SET_MAIN_CAMERA(sorceressloop);
		SET_MESH(sorceressloop, L"RectMesh");
		SET_MATERIAL(sorceressloop, L"AnimationMaterial");
		SET_POS_XYZ(sorceressloop, 0.f, 0.f, 1.f);
		SET_SCALE_XYZ(sorceressloop, 120.f * Texture::GetWidRatio(), 260.f * Texture::GetHeiRatio(), 1.f);

		AddGameObject(eLayerType::UI, sorceressloop);

		SHARED_MAT mat = RESOURCE_FIND(Material, L"sorceressPickLoop");
		animator->Create(
			L"sorceressPickLoopAnim",
			mat->GetTexture(),
			Vector2::Zero,
			Vector2(120, 260),
			12,
			Vector2::Zero,
			Vector2::Zero,
			0.05f
		);

		animator->PlayAnimation(L"sorceressPickLoopAnim", true);


		GameObject* fireloop = new GameObject();
		ADD_COMP(fireloop, MeshRenderer);
		animator = ADD_COMP(fireloop, Animator);
		SET_MAIN_CAMERA(fireloop);
		SET_MESH(fireloop, L"RectMesh");
		SET_MATERIAL(fireloop, L"AnimationMaterial");
		SET_POS_XYZ(fireloop, 10.f, RESOL_H_HEI - 370.f * Texture::GetHeiRatio(), 1.f);
		SET_SCALE_XYZ(fireloop, 110.f * Texture::GetWidRatio(), 176.f * Texture::GetHeiRatio(), 1.f);

		AddGameObject(eLayerType::UI, fireloop);

		mat = RESOURCE_FIND(Material, L"characterSelectFire");
		animator->Create(
			L"characterSelectFireAnim",
			mat->GetTexture(),
			Vector2::Zero,
			Vector2(110, 176),
			30,
			Vector2::Zero,
			Vector2::Zero,
			0.03f
		);

		animator->PlayAnimation(L"characterSelectFireAnim", true);

		{
			GameObject* light = new GameObject();
			light->SetName(L"Smile");
			AddGameObject(eLayerType::Light, light);
			Light* lightComp = light->AddComponent<Light>();
			lightComp->SetType(eLightType::Directional);
			lightComp->SetColor(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
			lightComp->SetAngle(45.f);
		}

		mTIU = new TextInputUI();
		SET_MAIN_CAMERA(mTIU);
		SET_POS_XYZ(mTIU, 0.f, RESOL_H_HEI - 500.f * Texture::GetHeiRatio(), 1.f);
		AddGameObject(eLayerType::UI, mTIU);
	}
}
