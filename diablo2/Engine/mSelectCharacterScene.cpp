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

namespace m
{
	SelectCharacterScene::SelectCharacterScene()
	{}
	SelectCharacterScene::~SelectCharacterScene()
	{}
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
		exitBtn->SetClickFunction( []() { SceneManager::LoadScene(L"PlayScene"); });
		SET_POS_XYZ(exitBtn, 34.f + -RESOL_H_WID + 126.f * Texture::GetWidRatio() / 2.f, 27.f + -RESOL_H_HEI + 35.f * Texture::GetHeiRatio() / 2.f, 1.f);
		SET_SCALE_TEX_SIZE_WITH_RAT(exitBtn, tex, 1.f);

		UI* mTextcharacterChoose = new UI();
		mTextcharacterChoose->HoverSoundMute();
		mTextcharacterChoose->Mute(true);
		mTextcharacterChoose->SetText(L"캐릭터 클래스 선택");
		mTextcharacterChoose->SetTextSize(50.f);
		Vector2 size =FontWrapper::GetTextSize(L"캐릭터 클래스 선택", 50.f);
		mTextcharacterChoose->SetTextNormalColor(Vector4(255.f, 255.f, 255.f, 255.f));

		SET_MAIN_CAMERA(mTextcharacterChoose);
		SET_MESH(mTextcharacterChoose, L"RectMesh");
		SET_MATERIAL(mTextcharacterChoose, L"noneRect");
		SET_POS_XYZ(mTextcharacterChoose, 0.f, RESOL_H_HEI - size.y, 1.f);
		//SET_POS_XYZ(mTextcharacterChoose, 34.f + -RESOL_H_WID + 126.f * Texture::GetWidRatio() / 2.f, 27.f + -RESOL_H_HEI + 35.f * Texture::GetHeiRatio() / 2.f, 1.f);
		SET_SCALE_XYZ(mTextcharacterChoose, size.x, size.y, 1.f);
		AddGameObject(eLayerType::UI, mTextcharacterChoose);


	}
	void SelectCharacterScene::Update()
	{
		Scene::Update();
		if (Input::GetKeyDown(eKeyCode::N))
		{
			SceneManager::LoadScene(L"PlayScene");
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
}
