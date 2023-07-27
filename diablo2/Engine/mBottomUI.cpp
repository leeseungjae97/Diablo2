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
			Inven* pocket = new Inven();
			pocket->SetState(eState::RenderUpdate);
			pocket->SetCamera(GetCamera());
			SET_SCALE_XYZ(pocket, (288.f / 10.f) * Texture::GetWidRatio()
						  , (114.f / 4.f) * Texture::GetHeiRatio(), 0.f);
			SET_POS_XYZ(pocket
				, 90.f + (288.f / 10.f * i) * Texture::GetWidRatio()
				, GET_POS(this).y - (114.f / 4.f) - 8.f * Texture::GetHeiRatio()
				, -1.f);
			curScene->AddGameObject(eLayerType::UI, pocket);
			pockets.push_back(pocket);
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