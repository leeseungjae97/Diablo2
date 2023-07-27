#include "mBottomUI.h"

#include "../engine_source/mSceneManager.h"
#include "../engine_source/mMeshRenderer.h"
#include "../engine_source/mTexture.h"
#include "mInven.h"
namespace m
{
	BottomUI::BottomUI(Camera* camera)
	{
		SetCamera(camera);

		SetState(RenderUpdate);

		SET_MESH(this, L"RectMesh");
		SET_MATERIAL(this, L"bottomUi");

		MAKE_GET_TEX(this, tex);
		SET_SCALE_TEX_SIZE_WITH_RAT(this, tex, 1.f);
		SET_POS_XYZ(this, 0.f, -RESOL_H_HEI + 104.f * Texture::GetHeiRatio() / 2.f, -1.f);

		Scene* curScene = SceneManager::GetActiveScene();
		curScene->AddGameObject(eLayerType::UI, this);

		for (int i = 0; i < 4; ++i)
		{
			Inven* inventory = new Inven();
			inventory->SetState(eState::RenderUpdate);
			inventory->SetCamera(GetCamera());
			SET_SCALE_XYZ(inventory, (288.f / 10.f) * Texture::GetWidRatio()
						  , (114.f / 4.f) * Texture::GetHeiRatio(), 0.f);
			SET_POS_XYZ(inventory, 10.f * Texture::GetWidRatio(), GET_POS(this).y, -1.f);
			curScene->AddGameObject(eLayerType::UI, inventory);
			pockets.push_back(inventory);
		}
	}
	BottomUI::~BottomUI()
	{
	}
	void BottomUI::Initialize()
	{
		UI::Initialize();
	}
	void BottomUI::Update()
	{
		UI::Update();
	}
	void BottomUI::LateUpdate()
	{
		UI::LateUpdate();
	}
	void BottomUI::Render()
	{
		UI::Render();
	}
}