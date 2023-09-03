#include "mBottomUI.h"

#include "../engine_source/mSceneManager.h"
#include "../engine_source/mStashManager.h"
#include "../engine_source/mMeshRenderer.h"
#include "../engine_source/mTexture.h"

#include "mEmptyRect.h"
#include "mMouseManager.h"
#include "mPlayerInfo.h"
#include "mPlayer.h"
#include "mSkillShortCutButton.h"
#include "mUVUI.h"

namespace m
{
	BottomUI::BottomUI(Camera* camera)
		: bBelt(false)
		//, mPocketUI(nullptr)
		, mExPocketUI(nullptr)
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

		UI* uiMp = new UI();
		curScene->AddGameObject(eLayerType::UI, uiMp);
		uiMp->SetCamera(camera);
		SET_MESH(uiMp, L"RectMesh");
		SET_MATERIAL(uiMp, L"mpUi");
		GET_TEX(uiMp, tex);
		SET_SCALE_TEX_SIZE_WITH_RAT(uiMp, tex, 0.f);
		SET_POS_XYZ(uiMp, RESOL_H_WID - 117.f * Texture::GetWidRatio() / 2.f
			, -RESOL_H_HEI + 104.f * Texture::GetHeiRatio() / 2.f, -1.f);


		UVUI* mp = new UVUI();
		curScene->AddGameObject(eLayerType::UI, mp);
		mp->SetCamera(camera);
		SET_MESH(mp, L"RectMesh");
		SET_MATERIAL(mp, L"mp");
		GET_TEX(mp, tex);
		SET_SCALE_TEX_SIZE_WITH_RAT(mp, tex, 0.f);
		SET_POS_XYZ(mp, RESOL_H_WID - 140.f * Texture::GetWidRatio() / 2.f
			, -RESOL_H_HEI + 105.f * Texture::GetHeiRatio() / 2.f, -1.f);


		UI* mpOverlapHands = new UI();
		curScene->AddGameObject(eLayerType::UI, mpOverlapHands);
		mpOverlapHands->SetCamera(camera);
		SET_MESH(mpOverlapHands, L"RectMesh");
		SET_MATERIAL(mpOverlapHands, L"mpOverlapHands");
		GET_TEX(mpOverlapHands, tex);
		SET_SCALE_TEX_SIZE_WITH_RAT(mpOverlapHands, tex, 0.f);
		SET_POS_XYZ(mpOverlapHands, RESOL_H_WID - 135.f * Texture::GetWidRatio() / 2.f
			, -RESOL_H_HEI + 105.f * Texture::GetHeiRatio() / 2.f, -1.f);

		UI* uiHp = new UI();
		curScene->AddGameObject(eLayerType::UI, uiHp);
		uiHp->SetCamera(camera);
		SET_MESH(uiHp, L"RectMesh");
		SET_MATERIAL(uiHp, L"hpUi");
		GET_TEX(uiHp, tex);
		SET_SCALE_TEX_SIZE_WITH_RAT(uiHp, tex, 0.f);
		SET_POS_XYZ(uiHp, -RESOL_H_WID + 117.f * Texture::GetWidRatio() / 2.f
			, -RESOL_H_HEI + 104.f * Texture::GetHeiRatio() / 2.f, -1.f);

		UVUI* hp = new UVUI();
		curScene->AddGameObject(eLayerType::UI, hp);
		hp->SetCamera(camera);
		hp->SetName(L"hp");
		SET_MESH(hp, L"RectMesh");
		SET_MATERIAL(hp, L"hp");
		GET_TEX(hp, tex);
		SET_SCALE_TEX_SIZE_WITH_RAT(hp, tex, 0.f);
		SET_POS_XYZ(hp, -RESOL_H_WID + 138.f * Texture::GetWidRatio() / 2.f
			, -RESOL_H_HEI + 105.f * Texture::GetHeiRatio() / 2.f, -1.f);

		UI* hpOverlapHands = new UI();
		curScene->AddGameObject(eLayerType::UI, hpOverlapHands);
		hpOverlapHands->SetCamera(camera);
		SET_MESH(hpOverlapHands, L"RectMesh");
		SET_MATERIAL(hpOverlapHands, L"hpOverlapHands");
		GET_TEX(hpOverlapHands, tex);
		SET_SCALE_TEX_SIZE_WITH_RAT(hpOverlapHands, tex, 0.f);
		SET_POS_XYZ(hpOverlapHands, RESOL_H_WID + 137.f * Texture::GetWidRatio() / 2.f
			, -RESOL_H_HEI + 105.f * Texture::GetHeiRatio() / 2.f, -1.f);

		SkillShortCutButton* skillShortCutLeft = new SkillShortCutButton(0);
		curScene->AddGameObject(eLayerType::UI, skillShortCutLeft);
		skillShortCutLeft->SetCamera(camera);
		SET_MESH(skillShortCutLeft, L"RectMesh");
		SET_MATERIAL(skillShortCutLeft, wsSkillIconNames[(int)PlayerInfo::GetSkill(0)]);

		GET_TEX(skillShortCutLeft, tex);
		SET_SCALE_TEX_SIZE_WITH_RAT(skillShortCutLeft, tex, 0.f);
		SET_POS_XYZ(skillShortCutLeft, -470.f - tex->GetMetaDataWidth() * Texture::GetWidRatio() / 2.f
			, -RESOL_H_HEI + tex->GetMetaDataHeight() * Texture::GetHeiRatio() / 2.f, -1.f);

		SkillShortCutButton* skillShortCutRight = new SkillShortCutButton(1);
		curScene->AddGameObject(eLayerType::UI, skillShortCutRight);
		skillShortCutRight->SetCamera(camera);
		SET_MESH(skillShortCutRight, L"RectMesh");
		SET_MATERIAL(skillShortCutRight, wsSkillIconNames[(int)PlayerInfo::GetSkill(1)]);

		GET_TEX(skillShortCutRight, tex);
		SET_SCALE_TEX_SIZE_WITH_RAT(skillShortCutRight, tex, 0.f);
		SET_POS_XYZ(skillShortCutRight, 470.f + tex->GetMetaDataWidth() * Texture::GetWidRatio() / 2.f
			, -RESOL_H_HEI + tex->GetMetaDataHeight() * Texture::GetHeiRatio() / 2.f, -1.f);

		PlayerInfo::player->SetHpUI(hp);
		PlayerInfo::player->SetMpUI(mp);

		std::vector<EmptyRect*> exPockets = StashManager::GetExPockets();

		mExPocketUI = new UI();
		mExPocketUI->SetCamera(camera);
		SET_MESH(mExPocketUI, L"RectMesh");
		SET_MATERIAL(mExPocketUI, L"exPocket");
		GET_TEX(mExPocketUI, tex);
		SET_SCALE_TEX_SIZE_WITH_RAT(mExPocketUI, tex, 1.f);
		SET_POS_XYZ(mExPocketUI
			, (exPockets[1]->GetPos().x + exPockets[1]->GetSize().x / 2.f) + 1.f
			, (exPockets[0]->GetPos().y + exPockets[0]->GetSize().y / 2.f) + 3.f
			, -1.f);
		mExPocketUI->SetState(NoRenderUpdate);
		curScene->AddGameObject(eLayerType::UI, mExPocketUI);
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
		Vector3 mousePosV3 = MouseManager::UnprojectionMousePos(-1.f, GetCamera());
		Vector2 mousePos = Vector2(mousePosV3.x, mousePosV3.y);
		bool hoverRect = false;
		EmptyRect* pocket = StashManager::GetPocketCollider();
		if (Vector2::PointIntersectRect(pocket->GetPos(), pocket->GetSize(), mousePos))
		{
			hoverRect = true;
			mExPocketUI->SetState(eState::RenderUpdate);
			StashManager::SetExPocketVisible(eState::RenderUpdate);
		}
		if (!hoverRect && !mExPocketUI->GetHover())
		{
			mExPocketUI->SetState(eState::NoRenderUpdate);
			StashManager::SetExPocketVisible(eState::NoRenderUpdate);
		}
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
