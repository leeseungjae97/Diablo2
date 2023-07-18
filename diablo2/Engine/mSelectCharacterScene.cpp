#include "mSelectCharacterScene.h"

#include "..\engine_source\mSceneManager.h"
#include "..\engine_source\mCamera.h"
#include "..\engine_source\mTransform.h"
#include "..\engine_source\mGameObject.h"
#include "..\engine_source\mMeshRenderer.h"
#include "..\engine_source\mResources.h"

#include "mBackground.h"
#include "mButton.h"
#include "mCameraScript.h"

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

		Vector2 ccp = Camera::GetCameraCenter();

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

		//Background* fire = new Background();
		//AddGameObject(eLayerType::UI, fire);
		//fire->GetComponent<MeshRenderer>()->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		//fire->GetComponent<MeshRenderer>()->SetMaterial(Resources::Find<Material>(L"characterSelect1"));
		//fire->GetComponent<Transform>()->SetPosition(Vector3(0.f, 0.f, 1.f));
		//fire->GetComponent<Transform>()->SetScale(Vector3(0.f, 0.f, 0.f));

		//Background* amazon = new Background();
		//AddGameObject(eLayerType::UI, amazon);
		//amazon->GetComponent<MeshRenderer>()->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		//amazon->GetComponent<MeshRenderer>()->SetMaterial(Resources::Find<Material>(L"characterSelect1"));
		//amazon->GetComponent<Transform>()->SetPosition(Vector3(0.f, 0.f, 1.f));
		//amazon->GetComponent<Transform>()->SetScale(Vector3(0.f, 0.f, 0.f));

		Button* exitBtn = new Button();
		AddGameObject(eLayerType::UI, exitBtn);

		SET_MAIN_CAMERA(exitBtn);
		SET_MESH(exitBtn, L"RectMesh");
		SET_MATERIAL(exitBtn, L"mWideButtonBlank");
		GET_TEX_D(exitBtn, tex);
		exitBtn->SetClickMaterial(RESOURCE_FIND(Material, L"mWideButtonBlankClick"));
		exitBtn->SetNormalMaterial(RESOURCE_FIND(Material, L"mWideButtonBlank"));
		exitBtn->SetClickFunction( []() { SceneManager::LoadScene(L"PlayScene"); });
		SET_POS_XYZ(exitBtn, 34.f + -RESOL_H_WID + 126.f * Texture::GetWidRatio() / 2.f, 27.f + -RESOL_H_HEI + 35.f * Texture::GetHeiRatio() / 2.f, 1.f);
		SET_SCALE_WIDTH_OH(exitBtn, 126.f ,tex, 0.0f);
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