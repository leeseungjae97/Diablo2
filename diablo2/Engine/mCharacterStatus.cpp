#include "mCharacterStatus.h"

#include "mButton.h"
#include "mPlayerManager.h"
#include "mPlayerStatus.h"
#include "../engine_source/mSceneManager.h"
#include "../engine_source/mMeshRenderer.h"
namespace m
{
	CharacterStatus::CharacterStatus(Camera* camera)
		: mTextName(nullptr)
		, mTextClass(nullptr)
		, mLevel(nullptr)
		, mExp(nullptr)
		, mNextLevelExp(nullptr)
		, mStr(nullptr)
		, mDex(nullptr)
		, mVit(nullptr)
		, mEng(nullptr)
		, mRemainPoint(nullptr)
		, mTextLife(nullptr)
		, mTextMana(nullptr)

		, mClose(nullptr)
		, mStrBtn(nullptr)
		, mDexBtn(nullptr)
		, mVitBtn(nullptr)
		, mEngBtn(nullptr)
	{
		SetCamera(camera);

		SET_MESH(this, L"RectMesh");
		SET_MATERIAL(this, L"characterStatus");

		MAKE_GET_TEX(this, tex);
		SET_SCALE_TEX_SIZE_WITH_RAT(this, tex, 1.f);
		SET_POS_XYZ(this, -(tex->GetMetaDataWidth() * Texture::GetWidRatio() / 2.f)
			, RESOL_H_HEI - tex->GetMetaDataHeight() * Texture::GetHeiRatio() / 2.f, -1.0f);

		Scene* scene = SceneManager::GetActiveScene();
		scene->AddGameObject(eLayerType::UI, this);

		mClose = new Button();
		scene->AddGameObject(eLayerType::UI, mClose);
		mClose->SetCamera(GetCamera());
		mClose->SetState(NoRenderUpdate);
		SET_MESH(mClose, L"RectMesh");
		SET_MATERIAL(mClose, L"closeBtn");
		mClose->SetClickMaterial(RESOURCE_FIND(Material, L"closeBtnClick"));
		mClose->SetNormalMaterial(RESOURCE_FIND(Material, L"closeBtn"));
		GET_TEX(mClose, tex);
		SET_SCALE_TEX_SIZE_WITH_RAT(mClose, tex, 0.0f);
		SET_POS_XYZ(mClose, -RESOL_H_WID + 224.f * Texture::GetWidRatio(),
			-RESOL_H_HEI + (84.f + 48.f) * Texture::GetHeiRatio(), -1.f);
		//SET_POS_XYZ(mClose, 0,0, -1.f);

		mStrBtn = new Button();
		mDexBtn = new Button();
		mVitBtn = new Button();
		mEngBtn = new Button();

		mStrBtn->SetCamera(camera);
		mDexBtn->SetCamera(camera);
		mVitBtn->SetCamera(camera);
		mEngBtn->SetCamera(camera);

		mStrBtn->SetClickFunction([]()
			{
				PlayerStatus::UpStrength();
			});
		mDexBtn->SetClickFunction([]()
			{
				PlayerStatus::UpDexterity();
			});
		mVitBtn->SetClickFunction([]()
			{
				PlayerStatus::UpVitality();
			});
		mEngBtn->SetClickFunction([]()
			{
				PlayerStatus::UpEnergy();
			});

		scene->AddGameObject(eLayerType::UI, mStrBtn);
		scene->AddGameObject(eLayerType::UI, mDexBtn);
		scene->AddGameObject(eLayerType::UI, mVitBtn);
		scene->AddGameObject(eLayerType::UI, mEngBtn);

		SET_MESH(mStrBtn, L"RectMesh");
		SET_MATERIAL(mStrBtn, L"levelBtn");
		mStrBtn->SetClickMaterial(RESOURCE_FIND(Material, L"levelBtnClick"));
		mStrBtn->SetNormalMaterial(RESOURCE_FIND(Material, L"levelBtn"));
		GET_TEX(mStrBtn, tex);
		SET_SCALE_TEX_SIZE_WITH_RAT(mStrBtn, tex, 0.0f);

		SET_MESH(mDexBtn, L"RectMesh");
		SET_MATERIAL(mDexBtn, L"levelBtn");
		mDexBtn->SetClickMaterial(RESOURCE_FIND(Material, L"levelBtnClick"));
		mDexBtn->SetNormalMaterial(RESOURCE_FIND(Material, L"levelBtn"));
		GET_TEX(mDexBtn, tex);
		SET_SCALE_TEX_SIZE_WITH_RAT(mDexBtn, tex, 0.0f);

		SET_MESH(mVitBtn, L"RectMesh");
		SET_MATERIAL(mVitBtn, L"levelBtn");
		mVitBtn->SetClickMaterial(RESOURCE_FIND(Material, L"levelBtnClick"));
		mVitBtn->SetNormalMaterial(RESOURCE_FIND(Material, L"levelBtn"));
		GET_TEX(mVitBtn, tex);
		SET_SCALE_TEX_SIZE_WITH_RAT(mVitBtn, tex, 0.0f);

		SET_MESH(mEngBtn, L"RectMesh");
		SET_MATERIAL(mEngBtn, L"levelBtn");
		mEngBtn->SetClickMaterial(RESOURCE_FIND(Material, L"levelBtnClick"));
		mEngBtn->SetNormalMaterial(RESOURCE_FIND(Material, L"levelBtn"));
		GET_TEX(mEngBtn, tex);
		SET_SCALE_TEX_SIZE_WITH_RAT(mEngBtn, tex, 0.0f);

		SET_POS_XYZ(mStrBtn, -RESOL_H_WID + 220.f * Texture::GetWidRatio()
			, RESOL_H_HEI - 158.f * Texture::GetHeiRatio(), -1.f);
		SET_POS_XYZ(mDexBtn, -RESOL_H_WID + 220.f * Texture::GetWidRatio()
			, RESOL_H_HEI - 217.f * Texture::GetHeiRatio(), -1.f);
		SET_POS_XYZ(mVitBtn, -RESOL_H_WID + 220.f * Texture::GetWidRatio()
			, RESOL_H_HEI - 306.f * Texture::GetHeiRatio(), -1.f);
		SET_POS_XYZ(mEngBtn, -RESOL_H_WID + 220.f * Texture::GetWidRatio()
			, RESOL_H_HEI - 365.f * Texture::GetHeiRatio(), -1.f);

		mTextRemainPoint = new UI();
		mTextStr = new UI();
		mTextDex = new UI();
		mTextVit = new UI();
		mTextEng = new UI();

		mTextRemainPoint->SetCamera(camera);
		mTextStr->SetCamera(camera);
		mTextDex->SetCamera(camera);
		mTextVit->SetCamera(camera);
		mTextEng->SetCamera(camera);


		mTextRemainPoint->SetText(L"남은 능력치");
		mTextRemainPoint->SetTextOffset(Vector2(-40.f, 0.f));
		mTextRemainPoint->SetTextSize(15.f);
		mTextRemainPoint->SetTextNormalColor(Vector4(176.f, 68.f, 52.f, 255.f));

		mTextStr->SetText(L"힘");
		mTextStr->SetTextSize(15.f);
		mTextStr->SetTextNormalColor(Vector4(255.f, 255.f, 255.f, 255.f));

		mTextDex->SetText(L"민첩성");
		mTextDex->SetTextSize(15.f);
		mTextDex->SetTextNormalColor(Vector4(255.f, 255.f, 255.f, 255.f));

		mTextVit->SetText(L"생명력");
		mTextVit->SetTextSize(15.f);
		mTextVit->SetTextNormalColor(Vector4(255.f, 255.f, 255.f, 255.f));

		mTextEng->SetText(L"에너지");
		mTextEng->SetTextSize(15.f);
		mTextEng->SetTextNormalColor(Vector4(255.f, 255.f, 255.f, 255.f));

		SET_MESH(mTextRemainPoint, L"RectMesh");
		SET_MATERIAL(mTextRemainPoint, L"statPoint");
		GET_TEX(mTextRemainPoint, tex);
		SET_SCALE_TEX_SIZE_WITH_RAT(mTextRemainPoint, tex, 0.0f);
		SET_POS_XYZ(mTextRemainPoint, -RESOL_H_WID + 82.f * Texture::GetWidRatio() + tex->GetMetaDataWidth()
			, RESOL_H_HEI - 416.f * Texture::GetHeiRatio(), -1.f);
		SET_POS_XYZ(mTextStr, -RESOL_H_WID + 125.f * Texture::GetWidRatio(), RESOL_H_HEI - 158.f * Texture::GetHeiRatio(), -1.f);
		SET_POS_XYZ(mTextDex, -RESOL_H_WID + 125.f * Texture::GetWidRatio(), RESOL_H_HEI - 217.f * Texture::GetHeiRatio(), -1.f);
		SET_POS_XYZ(mTextVit, -RESOL_H_WID + 125.f * Texture::GetWidRatio(), RESOL_H_HEI - 306.f * Texture::GetHeiRatio(), -1.f);
		SET_POS_XYZ(mTextEng, -RESOL_H_WID + 125.f * Texture::GetWidRatio(), RESOL_H_HEI - 365.f * Texture::GetHeiRatio(), -1.f);


		scene->AddGameObject(eLayerType::UI, mTextRemainPoint);
		scene->AddGameObject(eLayerType::UI, mTextStr);
		scene->AddGameObject(eLayerType::UI, mTextDex);
		scene->AddGameObject(eLayerType::UI, mTextVit);
		scene->AddGameObject(eLayerType::UI, mTextEng);



		SET_MESH(mTextStr, L"RectMesh");
		SET_MATERIAL(mTextStr, L"noneRect");
		SET_MESH(mTextDex, L"RectMesh");
		SET_MATERIAL(mTextDex, L"noneRect");
		SET_MESH(mTextVit, L"RectMesh");
		SET_MATERIAL(mTextVit, L"noneRect");
		SET_MESH(mTextEng, L"RectMesh");
		SET_MATERIAL(mTextEng, L"noneRect");

		mRemainPoint = new UI();
		mStr = new UI();
		mDex = new UI();
		mVit = new UI();
		mEng = new UI();

		mRemainPoint->SetCamera(camera);
		mStr->SetCamera(camera);
		mDex->SetCamera(camera);
		mVit->SetCamera(camera);
		mEng->SetCamera(camera);

		mRemainPoint->SetTextNormalColor(Vector4(255.f, 255.f, 255.f, 255.f));
		mStr->SetTextNormalColor(Vector4(255.f, 255.f, 255.f, 255.f));
		mDex->SetTextNormalColor(Vector4(255.f, 255.f, 255.f, 255.f));
		mVit->SetTextNormalColor(Vector4(255.f, 255.f, 255.f, 255.f));
		mEng->SetTextNormalColor(Vector4(255.f, 255.f, 255.f, 255.f));

		mRemainPoint->SetText(std::to_wstring(PlayerStatus::statusPoint));
		mStr->SetText(std::to_wstring(PlayerStatus::strength));
		mDex->SetText(std::to_wstring(PlayerStatus::dexterity));
		mVit->SetText(std::to_wstring(PlayerStatus::vitality));
		mEng->SetText(std::to_wstring(PlayerStatus::energy));

		mRemainPoint->SetTextSize(15.f);
		mStr->SetTextSize(15.f);
		mDex->SetTextSize(15.f);
		mVit->SetTextSize(15.f);
		mEng->SetTextSize(15.f);

		SET_POS_XYZ(mRemainPoint, -RESOL_H_WID + 190.f * Texture::GetWidRatio(), RESOL_H_HEI - 416.f * Texture::GetHeiRatio(), -1.f);
		SET_POS_XYZ(mStr, -RESOL_H_WID + 175.f * Texture::GetWidRatio(), RESOL_H_HEI - 158.f * Texture::GetHeiRatio(), -1.f);
		SET_POS_XYZ(mDex, -RESOL_H_WID + 175.f * Texture::GetWidRatio(), RESOL_H_HEI - 217.f * Texture::GetHeiRatio(), -1.f);
		SET_POS_XYZ(mVit, -RESOL_H_WID + 175.f * Texture::GetWidRatio(), RESOL_H_HEI - 306.f * Texture::GetHeiRatio(), -1.f);
		SET_POS_XYZ(mEng, -RESOL_H_WID + 175.f * Texture::GetWidRatio(), RESOL_H_HEI - 365.f * Texture::GetHeiRatio(), -1.f);


		scene->AddGameObject(eLayerType::UI, mRemainPoint);
		scene->AddGameObject(eLayerType::UI, mStr);
		scene->AddGameObject(eLayerType::UI, mDex);
		scene->AddGameObject(eLayerType::UI, mVit);
		scene->AddGameObject(eLayerType::UI, mEng);


		SET_MESH(mRemainPoint, L"RectMesh");
		SET_MATERIAL(mRemainPoint, L"noneRect");
		SET_MESH(mStr, L"RectMesh");
		SET_MATERIAL(mStr, L"noneRect");
		SET_MESH(mDex, L"RectMesh");
		SET_MATERIAL(mDex, L"noneRect");
		SET_MESH(mVit, L"RectMesh");
		SET_MATERIAL(mVit, L"noneRect");
		SET_MESH(mEng, L"RectMesh");
		SET_MATERIAL(mEng, L"noneRect");


		mTextName = new UI();
		mTextClass = new UI();
		mLevel = new UI();
		mExp = new UI();
		mNextLevelExp = new UI();

		SET_MESH(mTextName, L"RectMesh");
		SET_MATERIAL(mTextName, L"noneRect");
		SET_MESH(mTextClass, L"RectMesh");
		SET_MATERIAL(mTextClass, L"noneRect");
		SET_MESH(mLevel, L"RectMesh");
		SET_MATERIAL(mLevel, L"noneRect");
		SET_MESH(mExp, L"RectMesh");
		SET_MATERIAL(mExp, L"noneRect");
		SET_MESH(mNextLevelExp, L"RectMesh");
		SET_MATERIAL(mNextLevelExp, L"noneRect");

		mTextName->SetCamera(camera);
		mTextClass->SetCamera(camera);
		mLevel->SetCamera(camera);
		mExp->SetCamera(camera);
		mNextLevelExp->SetCamera(camera);

		mTextName->SetTextNormalColor(Vector4(255.f, 255.f, 255.f, 255.f));
		mTextClass->SetTextNormalColor(Vector4(255.f, 255.f, 255.f, 255.f));
		mLevel->SetTextNormalColor(Vector4(255.f, 255.f, 255.f, 255.f));
		mExp->SetTextNormalColor(Vector4(255.f, 255.f, 255.f, 255.f));
		mNextLevelExp->SetTextNormalColor(Vector4(255.f, 255.f, 255.f, 255.f));

		mTextName->SetText(PlayerStatus::playerName);
		mTextClass->SetText(PlayerStatus::className);

		std::wstring levelLegd = L"레벨\n" + std::to_wstring(PlayerStatus::level);
		mLevel->SetText(levelLegd);

		std::wstring expLegd = L"경험치\n" + std::to_wstring(PlayerStatus::experiance);
		mExp->SetText(expLegd);

		std::wstring nextExpLegd = L"다음 레벨\n" + std::to_wstring(PlayerStatus::nextLevelUpexperiance);
		mNextLevelExp->SetText(nextExpLegd);

		mTextName->SetTextSize(15.f);
		mTextClass->SetTextSize(15.f);
		mLevel->SetTextSize(15.f);
		mExp->SetTextSize(15.f);
		mNextLevelExp->SetTextSize(15.f);

		SET_POS_XYZ(mTextName, -RESOL_H_WID + 184.f * Texture::GetWidRatio(), RESOL_H_HEI - 81.f * Texture::GetHeiRatio(), -1.f);
		SET_POS_XYZ(mTextClass, -RESOL_H_WID + 337.f * Texture::GetWidRatio(), RESOL_H_HEI - 81.f * Texture::GetHeiRatio(), -1.f);
		SET_POS_XYZ(mLevel, -RESOL_H_WID + 113.f * Texture::GetWidRatio(), RESOL_H_HEI - 113.f * Texture::GetHeiRatio(), -1.f);
		SET_POS_XYZ(mExp, -RESOL_H_WID + 204.f * Texture::GetWidRatio(), RESOL_H_HEI - 113.f * Texture::GetHeiRatio(), -1.f);
		SET_POS_XYZ(mNextLevelExp, -RESOL_H_WID + 331.f * Texture::GetWidRatio(), RESOL_H_HEI - 113.f * Texture::GetHeiRatio(), -1.f);

		scene->AddGameObject(eLayerType::UI, mTextName);
		scene->AddGameObject(eLayerType::UI, mTextClass);
		scene->AddGameObject(eLayerType::UI, mLevel);
		scene->AddGameObject(eLayerType::UI, mExp);
		scene->AddGameObject(eLayerType::UI, mNextLevelExp);

		mTextDef = new UI();
		mDef = new UI();
		mTextLife = new UI();
		mLifeMax = new UI();
		mLifeCur = new UI();
		mTextMana = new UI();
		mManaMax = new UI();
		mManaCur = new UI();
		mTextDamage = new UI();
		mDamage = new UI();


		mTextDef->SetCamera(camera);
		mDef->SetCamera(camera);
		mTextLife->SetCamera(camera);
		mLifeMax->SetCamera(camera);
		mLifeCur->SetCamera(camera);
		mTextMana->SetCamera(camera);
		mManaMax->SetCamera(camera);
		mManaCur->SetCamera(camera);
		mTextDamage->SetCamera(camera);
		mDamage->SetCamera(camera);

		mTextDef->SetTextNormalColor(Vector4(255.f, 255.f, 255.f, 255.f));
		mDef->SetTextNormalColor(Vector4(255.f, 255.f, 255.f, 255.f));
		mTextLife->SetTextNormalColor(Vector4(255.f, 255.f, 255.f, 255.f));
		mLifeMax->SetTextNormalColor(Vector4(255.f, 255.f, 255.f, 255.f));
		mLifeCur->SetTextNormalColor(Vector4(255.f, 255.f, 255.f, 255.f));
		mTextMana->SetTextNormalColor(Vector4(255.f, 255.f, 255.f, 255.f));
		mManaMax->SetTextNormalColor(Vector4(255.f, 255.f, 255.f, 255.f));
		mManaCur->SetTextNormalColor(Vector4(255.f, 255.f, 255.f, 255.f));
		mTextDamage->SetTextNormalColor(Vector4(255.f, 255.f, 255.f, 255.f));
		mDamage->SetTextNormalColor(Vector4(255.f, 255.f, 255.f, 255.f));

		mTextDef->SetText(L"방어");
		mDef->SetText(std::to_wstring(PlayerStatus::defense));

		mTextLife->SetText(L"라이프");
		mLifeMax->SetText(std::to_wstring(PlayerStatus::life));
		mLifeCur->SetText(std::to_wstring(static_cast<int>(PlayerManager::hp)));

		mTextMana->SetText(L"마나");
		mManaMax->SetText(std::to_wstring(PlayerStatus::mana));
		mManaCur->SetText(std::to_wstring(static_cast<int>(PlayerManager::mp)));

		mTextDamage->SetText(L"데미지");
		mDamage->SetText(std::to_wstring(PlayerStatus::damage));

		mTextDef->SetTextSize(15.f);
		mDef->SetTextSize(15.f);
		mTextLife->SetTextSize(15.f);
		mLifeMax->SetTextSize(15.f);
		mLifeCur->SetTextSize(15.f);
		mTextMana->SetTextSize(15.f);
		mManaMax->SetTextSize(15.f);
		mManaCur->SetTextSize(15.f);
		mTextDamage->SetTextSize(15.f);
		mDamage->SetTextSize(15.f);
		// 284 157

		SET_POS_XYZ(mTextDef, -RESOL_H_WID + 300.f * Texture::GetWidRatio(), RESOL_H_HEI - 267.f * Texture::GetHeiRatio(), -1.f);
		SET_POS_XYZ(mDef, -RESOL_H_WID + 373.f * Texture::GetWidRatio(), RESOL_H_HEI - 267.f * Texture::GetHeiRatio(), -1.f);

		SET_POS_XYZ(mTextLife, -RESOL_H_WID + 285.f * Texture::GetWidRatio(), RESOL_H_HEI - 330.f * Texture::GetHeiRatio(), -1.f);
		SET_POS_XYZ(mLifeMax, -RESOL_H_WID + 331.f * Texture::GetWidRatio(), RESOL_H_HEI - 330.f * Texture::GetHeiRatio(), -1.f);
		SET_POS_XYZ(mLifeCur, -RESOL_H_WID + 375.f * Texture::GetWidRatio(), RESOL_H_HEI - 330.f * Texture::GetHeiRatio(), -1.f);

		SET_POS_XYZ(mTextMana, -RESOL_H_WID + 285.f * Texture::GetWidRatio(), RESOL_H_HEI - 367.f * Texture::GetHeiRatio(), -1.f);
		SET_POS_XYZ(mManaMax, -RESOL_H_WID + 331.f * Texture::GetWidRatio(), RESOL_H_HEI - 367.f * Texture::GetHeiRatio(), -1.f);
		SET_POS_XYZ(mManaCur, -RESOL_H_WID + 375.f * Texture::GetWidRatio(), RESOL_H_HEI - 367.f * Texture::GetHeiRatio(), -1.f);

		SET_POS_XYZ(mTextDamage, -RESOL_H_WID + 285.f * Texture::GetWidRatio(), RESOL_H_HEI - 157.f * Texture::GetHeiRatio(), -1.f);
		SET_POS_XYZ(mDamage, -RESOL_H_WID + 365.f * Texture::GetWidRatio(), RESOL_H_HEI - 157.f * Texture::GetHeiRatio(), -1.f);

		SET_MESH(mTextDef, L"RectMesh");
		SET_MATERIAL(mTextDef, L"noneRect");
		SET_MESH(mDef, L"RectMesh");
		SET_MATERIAL(mDef, L"noneRect");

		SET_MESH(mTextLife, L"RectMesh");
		SET_MATERIAL(mTextLife, L"noneRect");
		SET_MESH(mLifeMax, L"RectMesh");
		SET_MATERIAL(mLifeMax, L"noneRect");
		SET_MESH(mLifeCur, L"RectMesh");
		SET_MATERIAL(mLifeCur, L"noneRect");

		SET_MESH(mTextMana, L"RectMesh");
		SET_MATERIAL(mTextMana, L"noneRect");
		SET_MESH(mManaMax, L"RectMesh");
		SET_MATERIAL(mManaMax, L"noneRect");
		SET_MESH(mManaCur, L"RectMesh");
		SET_MATERIAL(mManaCur, L"noneRect");

		SET_MESH(mTextDamage, L"RectMesh");
		SET_MATERIAL(mTextDamage, L"noneRect");
		SET_MESH(mDamage, L"RectMesh");
		SET_MATERIAL(mDamage, L"noneRect");

		scene->AddGameObject(eLayerType::UI, mTextDef);
		scene->AddGameObject(eLayerType::UI, mDef);
		scene->AddGameObject(eLayerType::UI, mTextLife);
		scene->AddGameObject(eLayerType::UI, mLifeMax);
		scene->AddGameObject(eLayerType::UI, mLifeCur);
		scene->AddGameObject(eLayerType::UI, mTextMana);
		scene->AddGameObject(eLayerType::UI, mManaMax);
		scene->AddGameObject(eLayerType::UI, mManaCur);
		scene->AddGameObject(eLayerType::UI, mTextDamage);
		scene->AddGameObject(eLayerType::UI, mDamage);
	}

	CharacterStatus::~CharacterStatus()
	{
	}

	void CharacterStatus::Initialize()
	{
		UI::Initialize();
	}

	void CharacterStatus::Update()
	{
		UI::Update();

		std::wstring levelLegd = L"레벨\n" + std::to_wstring(PlayerStatus::level);
		mLevel->SetText(levelLegd);

		std::wstring expLegd = L"경험치\n" + std::to_wstring(PlayerStatus::experiance);
		mExp->SetText(expLegd);

		std::wstring nextExpLegd = L"다음 레벨\n" + std::to_wstring(PlayerStatus::nextLevelUpexperiance);
		mNextLevelExp->SetText(nextExpLegd);

		mTextName->SetText(PlayerStatus::playerName);
		mTextClass->SetText(PlayerStatus::className);

		mStr->SetText(std::to_wstring(PlayerStatus::strength));
		mDex->SetText(std::to_wstring(PlayerStatus::dexterity));
		mVit->SetText(std::to_wstring(PlayerStatus::vitality));
		mEng->SetText(std::to_wstring(PlayerStatus::energy));
		mRemainPoint->SetText(std::to_wstring(PlayerStatus::statusPoint));

		mDef->SetText(std::to_wstring(PlayerStatus::defense));

		mLifeMax->SetText(std::to_wstring(PlayerStatus::life));
		mLifeCur->SetText(std::to_wstring(static_cast<int>(PlayerManager::hp)));

		mManaMax->SetText(std::to_wstring(PlayerStatus::mana));
		mManaCur->SetText(std::to_wstring(static_cast<int>(PlayerManager::mp)));

		mDamage->SetText(std::to_wstring(PlayerStatus::damage));

		if (mClose->GetOneClick())
		{
			SetState(NoRenderUpdate);
		}
		if (PlayerStatus::statusPoint != 0)
		{
			mStrBtn->SetState(GetState());
			mDexBtn->SetState(GetState());
			mVitBtn->SetState(GetState());
			mEngBtn->SetState(GetState());
			mRemainPoint->SetState(GetState());
			mTextRemainPoint->SetState(GetState());
		}
		else
		{
			mStrBtn->SetState(NoRenderUpdate);
			mDexBtn->SetState(NoRenderUpdate);
			mVitBtn->SetState(NoRenderUpdate);
			mEngBtn->SetState(NoRenderUpdate);
			mRemainPoint->SetState(NoRenderUpdate);
			mTextRemainPoint->SetState(NoRenderUpdate);
		}
		mClose->SetState(GetState());
		mStr->SetState(GetState());
		mDex->SetState(GetState());
		mVit->SetState(GetState());
		mEng->SetState(GetState());

		mTextStr->SetState(GetState());
		mTextDex->SetState(GetState());
		mTextVit->SetState(GetState());
		mTextEng->SetState(GetState());

		mTextName->SetState(GetState());
		mTextClass->SetState(GetState());
		mLevel->SetState(GetState());
		mExp->SetState(GetState());
		mNextLevelExp->SetState(GetState());

		mTextDef->SetState(GetState());
		mDef->SetState(GetState());
		mTextLife->SetState(GetState());
		mLifeMax->SetState(GetState());
		mLifeCur->SetState(GetState());
		mTextMana->SetState(GetState());
		mManaMax->SetState(GetState());
		mManaCur->SetState(GetState());

		mTextDamage->SetState(GetState());
		mDamage->SetState(GetState());
	}

	void CharacterStatus::LateUpdate()
	{
		UI::LateUpdate();
	}

	void CharacterStatus::Render()
	{
		UI::Render();
	}
}
