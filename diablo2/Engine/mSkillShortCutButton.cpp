#include "mSkillShortCutButton.h"

#include "mFontWrapper.h"
#include "mMouseManager.h"
#include "../engine_source/mMeshRenderer.h"
#include "../engine_source/mSceneManager.h"
#include "../engine_source/mTexture.h"

#include "mPlayerManager.h"
#include "mTileManager.h"

namespace m
{
	SkillShortCutButton::SkillShortCutButton(int skillIndex)
		: mSkillType(eSkillType::normalAttack)
		, mSkillIndex(skillIndex)
		, skillImages(nullptr)
		, prevSkillPoint(0)
	{
		//SetClickMaterial(RESOURCE_FIND(Material, L"normalAttackClickIcon"));
		//SetNormalMaterial(RESOURCE_FIND(Material, L"normalAttackIcon"));
		saveShortCutSkillTypes.resize(5);

		for(int i = 0; i < 10; ++i)
		{
			if (skillFunctionTypes[i] == eSkillFunctionType::Passive) continue;
			std::shared_ptr<Material> mat = RESOURCE_FIND(Material, wsColdSkillNames[i]);
			skillTexs.push_back(mat->GetTexture());
			skillTypes.push_back((eSkillType)i);
		}
		for (int i = 0; i < 10; ++i)
		{
			if (skillFunctionTypes[i + 10] == eSkillFunctionType::Passive) continue;
			std::shared_ptr<Material> mat = RESOURCE_FIND(Material, wsLightningSkillNames[i]);
			skillTexs.push_back(mat->GetTexture());
			skillTypes.push_back((eSkillType)(i + 10));
		}
		for (int i = 0; i < 10; ++i)
		{
			if (skillFunctionTypes[i + 20] == eSkillFunctionType::Passive) continue;
			std::shared_ptr<Material> mat = RESOURCE_FIND(Material, wsFireSkillNames[i]);
			skillTexs.push_back(mat->GetTexture());
			skillTypes.push_back((eSkillType)(i + 20));
		}
		bool right = false;
		if (skillIndex == 1) right = true;

		SetSkillBtnPos(right);

		skillImages = new UI();
		SceneManager::GetActiveScene()->AddGameObject(eLayerType::UI, skillImages);

		SET_MESH(skillImages, L"RectMesh");

		SHARED_MAT mat = std::make_shared<Material>();
		mat->SetShader(RESOURCE_FIND(Shader, L"NoLightShader"));

		std::shared_ptr<Texture> texture = std::make_shared<Texture>();
		texture->MergeTex(skillTexs, skillMatPos, 48, 48, 9, 1, L"skillsClick");

		mat->SetTexture(texture);
		SET_MATERIAL_D(skillImages, mat);

		SET_SCALE_TEX_SIZE(skillImages, texture, -1.f);

		skillImages->SetState(NoRenderUpdate);

		makeMa();
	}
	SkillShortCutButton::~SkillShortCutButton()
	{
	}
	void SkillShortCutButton::Initialize()
	{
		Button::Initialize();
	}
	void SkillShortCutButton::Update()
	{
		Button::Update();

		MakeSkillShortCutImage();

		if(nullptr == skillImages->GetCamera())
			skillImages->SetCamera(GetCamera());
		setMaCamera();

		if(GetOneClick())
		{
			skillImages->SetState(skillImages->GetState() == NoRenderUpdate ? RenderUpdate : NoRenderUpdate);
		}
		if (skillImages->GetState() == RenderUpdate)
		{
			GetHoverClickSkill();
			specifyShortcut();
		}else
		{
			skillChangeShortCut();
		}

		if(!GetHover())
		{
			if(Input::GetKeyDown(eKeyCode::LBUTTON)) skillImages->SetState(NoRenderUpdate);
		}

		if (PlayerManager::GetSkill(mSkillIndex) != mSkillType)
		{
			mSkillType = PlayerManager::GetSkill(mSkillIndex);
			SET_MATERIAL(this, wsSkillIconNames[(int)mSkillType]);
		}
		int i = 0;
		for (UI* ui : macroButtons)
		{
			if(bOverlaps[i])
			{
				ui->SetState(NoRenderUpdate);
			}else
			{
				ui->SetState(skillImages->GetState());
			}
			++i;
		}
	}
	void SkillShortCutButton::LateUpdate()
	{
		Button::LateUpdate();
	}
	void SkillShortCutButton::Render()
	{
		Button::Render();
	}
	eSkillType SkillShortCutButton::GetHoverClickSkill()
	{
		Vector3 posV3 = GET_POS(skillImages);
		Vector3 imageScale = GET_SCALE(skillImages);

		Vector2 scale = Vector2(48.f, 48.f);

		Vector3 mouseV3 = MouseManager::UnprojectionMousePos(-1, GetCamera());
		MAKE_VEC2_F_VEC3(posV2, posV3);
		MAKE_VEC2_F_VEC3(mouseV2, mouseV3);

		for(int i = 0 ; i < skillMatPos.size(); ++i)
		{
			if (skillMatPos[i] == Vector2(-1.f, -1.f)) continue;

			Vector2 skillPos;
			skillPos.x = (posV2.x - (imageScale.x / 2.f)) + (((skillMatPos[i].x + 1) * scale.x) - scale.x / 2.f);
			skillPos.y = (posV2.y + (imageScale.y / 2.f)) - (((skillMatPos[i].y + 1) * scale.y) - scale.y / 2.f);

			if (Vector2::PointIntersectRect(skillPos, scale, mouseV2))
			{
				if(Input::GetKeyDown(eKeyCode::LBUTTON))
				{
					PlayerManager::SetSkill(mSkillIndex, skillTypes[i]);
					//return ;
				}
			}
		}
		return eSkillType::END;
	}

    void SkillShortCutButton::skillChangeShortCut()
    {
		if(mSkillIndex == 1)
		{
			if (Input::GetKeyDown(eKeyCode::F1))
			{
				if(eSkillType::END == saveShortCutSkillTypes[0])
					return;

				PlayerManager::SetSkill(mSkillIndex, saveShortCutSkillTypes[0]);
			}
			if (Input::GetKeyDown(eKeyCode::F2))
			{
				if (eSkillType::END == saveShortCutSkillTypes[1])
					return;
				PlayerManager::SetSkill(mSkillIndex, saveShortCutSkillTypes[1]);
			}
			if (Input::GetKeyDown(eKeyCode::F3))
			{
				if (eSkillType::END == saveShortCutSkillTypes[2])
					return;
				PlayerManager::SetSkill(mSkillIndex, saveShortCutSkillTypes[2]);
			}
			if (Input::GetKeyDown(eKeyCode::F4))
			{
				if (eSkillType::END == saveShortCutSkillTypes[3])
					return;
				PlayerManager::SetSkill(mSkillIndex, saveShortCutSkillTypes[3]);
			}
			if (Input::GetKeyDown(eKeyCode::F5))
			{
				if (eSkillType::END == saveShortCutSkillTypes[4])
					return;
				PlayerManager::SetSkill(mSkillIndex, saveShortCutSkillTypes[4]);
			}
		}
    }

	void SkillShortCutButton::setMaCamera()
	{
		if (mF5 && nullptr == mF5->GetCamera()) mF5->SetCamera(GetCamera());
		if (mF4 && nullptr == mF4->GetCamera()) mF4->SetCamera(GetCamera());
		if (mF3 && nullptr == mF3->GetCamera()) mF3->SetCamera(GetCamera());
		if (mF2 && nullptr == mF2->GetCamera()) mF2->SetCamera(GetCamera());
		if (mF1 && nullptr == mF1->GetCamera()) mF1->SetCamera(GetCamera());
	}
    void SkillShortCutButton::makeMa()
    {
		Vector3 pos = GET_POS(this);
		Vector3 imageScale = GET_SCALE(skillImages);

	    mF5 = new UI();
	    mF4 = new UI();
	    mF3 = new UI();
	    mF2 = new UI();
	    mF1 = new UI();

		mF5->HoverSoundMute();
		mF4->HoverSoundMute();
		mF3->HoverSoundMute();
		mF2->HoverSoundMute();
		mF1->HoverSoundMute();

		mF5->SetState(GameObject::eState::NoRenderUpdate);
		mF4->SetState(GameObject::eState::NoRenderUpdate);
		mF3->SetState(GameObject::eState::NoRenderUpdate);
		mF2->SetState(GameObject::eState::NoRenderUpdate);
		mF1->SetState(GameObject::eState::NoRenderUpdate);

		mF5->SetText(L"F5");
		mF4->SetText(L"F4");
		mF3->SetText(L"F3");
		mF2->SetText(L"F2");
		mF1->SetText(L"F1");

		mF5->SetTextNormalColor(Vector4(255.f, 255.f, 255.f, 255.f));
		mF4->SetTextNormalColor(Vector4(255.f, 255.f, 255.f, 255.f));
		mF3->SetTextNormalColor(Vector4(255.f, 255.f, 255.f, 255.f));
		mF2->SetTextNormalColor(Vector4(255.f, 255.f, 255.f, 255.f));
		mF1->SetTextNormalColor(Vector4(255.f, 255.f, 255.f, 255.f));

		mF5->SetTextSize(15.f);
		mF4->SetTextSize(15.f);
		mF3->SetTextSize(15.f);
		mF2->SetTextSize(15.f);
		mF1->SetTextSize(15.f);

		Vector2 size =FontWrapper::GetTextSize(L"F5", 15.f);

		mF5->SetTextOffset(Vector2(-size.x / 2.f, size.y / 2.f));
		mF4->SetTextOffset(Vector2(-size.x / 2.f, size.y / 2.f));
		mF3->SetTextOffset(Vector2(-size.x / 2.f, size.y / 2.f));
		mF2->SetTextOffset(Vector2(-size.x / 2.f, size.y / 2.f));
		mF1->SetTextOffset(Vector2(-size.x / 2.f, size.y / 2.f));

	    SET_MESH(mF5, L"RectMesh");
	    SET_MESH(mF4, L"RectMesh");
	    SET_MESH(mF3, L"RectMesh");
	    SET_MESH(mF2, L"RectMesh");
	    SET_MESH(mF1, L"RectMesh");

		SET_MATERIAL(mF5, L"noneRect");
		SET_MATERIAL(mF4, L"noneRect");
		SET_MATERIAL(mF3, L"noneRect");
		SET_MATERIAL(mF2, L"noneRect");
		SET_MATERIAL(mF1, L"noneRect");
		
		SET_POS_XYZ(mF5, 0.f, 0.f, -1.f);
		SET_POS_XYZ(mF4, 0.f, 0.f, -1.f);
		SET_POS_XYZ(mF3, 0.f, 0.f, -1.f);
		SET_POS_XYZ(mF2, 0.f, 0.f, -1.f);
		SET_POS_XYZ(mF1, 0.f, 0.f, -1.f);

		SET_SCALE_XYZ(mF5, 48, 48, 1.f);
		SET_SCALE_XYZ(mF4, 48, 48, 1.f);
		SET_SCALE_XYZ(mF3, 48, 48, 1.f);
		SET_SCALE_XYZ(mF2, 48, 48, 1.f);
		SET_SCALE_XYZ(mF1, 48, 48, 1.f);

	    SceneManager::GetActiveScene()->AddGameObject(eLayerType::UI, mF5);
	    SceneManager::GetActiveScene()->AddGameObject(eLayerType::UI, mF4);
	    SceneManager::GetActiveScene()->AddGameObject(eLayerType::UI, mF3);
	    SceneManager::GetActiveScene()->AddGameObject(eLayerType::UI, mF2);
	    SceneManager::GetActiveScene()->AddGameObject(eLayerType::UI, mF1);

		macroButtons.push_back(mF1);
		macroButtons.push_back(mF2);
		macroButtons.push_back(mF3);
		macroButtons.push_back(mF4);
		macroButtons.push_back(mF5);

		bOverlaps.resize(macroButtons.size(), false);
    }
	void SkillShortCutButton::specifyShortcut()
	{

		Vector3 posV3 = GET_POS(skillImages);
		Vector3 imageScale = GET_SCALE(skillImages);

		Vector2 scale = Vector2(48.f, 48.f);

		Vector3 mouseV3 = MouseManager::UnprojectionMousePos(-1, GetCamera());
		MAKE_VEC2_F_VEC3(posV2, posV3);
		MAKE_VEC2_F_VEC3(mouseV2, mouseV3);

		for (int i = 0; i < skillMatPos.size(); ++i)
		{
			if (skillMatPos[i] == Vector2(-1.f, -1.f)) continue;

			Vector2 skillPos;
			skillPos.x = (posV2.x - (imageScale.x / 2.f)) + (((skillMatPos[i].x + 1) * scale.x) - scale.x / 2.f);
			skillPos.y = (posV2.y + (imageScale.y / 2.f)) - (((skillMatPos[i].y + 1) * scale.y) - scale.y / 2.f);

			if (Vector2::PointIntersectRect(skillPos, scale, mouseV2))
			{
				if (Input::GetKeyDown(eKeyCode::F1))
				{
					saveShortCutSkillTypes[0] = skillTypes[i];
					SET_POS_XYZ(macroButtons[0], skillPos.x + (scale.x / 2.f)
						, skillPos.y + (scale.y / 2.f), -1.f);
					eraseSkillOverlap(0);
					return;
				}
				if (Input::GetKeyDown(eKeyCode::F2))
				{
					saveShortCutSkillTypes[1] = skillTypes[i];
					SET_POS_XYZ(macroButtons[1], skillPos.x + (scale.x / 2.f)
						, skillPos.y + (scale.y / 2.f), -1.f);
					eraseSkillOverlap(1);
					return;
				}
				if (Input::GetKeyDown(eKeyCode::F3))
				{
					saveShortCutSkillTypes[2] = skillTypes[i];
					SET_POS_XYZ(macroButtons[2], skillPos.x + (scale.x / 2.f)
						, skillPos.y + (scale.y / 2.f), -1.f);
					eraseSkillOverlap(2);
					return;
				}
				if (Input::GetKeyDown(eKeyCode::F4))
				{
					saveShortCutSkillTypes[3] = skillTypes[i];
					SET_POS_XYZ(macroButtons[3], skillPos.x + (scale.x / 2.f)
						, skillPos.y + (scale.y / 2.f), -1.f);
					eraseSkillOverlap(3);
					return;
				}
				if (Input::GetKeyDown(eKeyCode::F5))
				{
					saveShortCutSkillTypes[4] = skillTypes[i];
					SET_POS_XYZ(macroButtons[4], skillPos.x + (scale.x / 2.f)
						, skillPos.y + (scale.y / 2.f), -1.f);
					eraseSkillOverlap(4);
					return ;
				}
			}
		}
	}
	void SkillShortCutButton::eraseSkillOverlap(int index)
	{
		bOverlaps[index] = false;
		eSkillType type =saveShortCutSkillTypes[index];

	    for(int i =0 ; i < 5; ++i)
	    {
			if (i == index) continue;

			eSkillType onType = saveShortCutSkillTypes[i];
			if(type == onType)
			{
				saveShortCutSkillTypes[i] = eSkillType::END;
				bOverlaps[i] = true;
				macroButtons[i]->SetState(NoRenderUpdate);
			}
	    }
	}

    void SkillShortCutButton::MakeSkillShortCutImage()
	{
		bool right = false;
		if (mSkillIndex == 1) right = true;

		if(GET_POS(skillImages) == Vector3(0.f, 0.f, 0.f))
		{
			Vector3 mSkillPos = GET_POS(this);
			Vector3 mScale = GET_SCALE(this);
			Vector3 skillScale = GET_SCALE(skillImages);
			mSkillPos.y += (mScale.y / 2.f) + (skillScale.y / 2.f) + 10.f;
			if(right)
			{
				mSkillPos.x -= skillScale.x / 2.f;
			}
			else mSkillPos.x += skillScale.x / 2.f;
			if(mSkillIndex == 0 )
			{
			    mSkillPos.x -= mScale.x / 2.f;
			}else mSkillPos.x += mScale.x / 2.f;
			SET_POS_XYZ(skillImages, mSkillPos.x, mSkillPos.y, -1.f);
		}
		if (prevSkillPoint == PlayerManager::skillPoint) return;

		prevSkillPoint = PlayerManager::skillPoint;
		
		SetSkillBtnPos(right);

		MeshRenderer* mr = GET_COMP(skillImages, MeshRenderer);
		SHARED_MAT mat = mr->GetMaterial();

		std::shared_ptr<Texture> texture = std::make_shared<Texture>();
		texture->MergeTex(skillTexs, skillMatPos, 48, 48, 9, 1, L"skillsClick");
		mat->GetTexture()->Clear();
		mat->SetTexture(texture);

		//SET_MATERIAL_D(skillImages, mat);
		SET_SCALE_TEX_SIZE(skillImages, texture, -1.f);
	}
	void SkillShortCutButton::SetSkillBtnPos(bool right)
	{
		skillMatPos.clear();
		float yPos = 0.0f;
		float xPos = 0.0f;
		float xInitValue = 0.f;
		float posIncValue = 1;

		if(right)
		{
			xPos = 8.f;
			xInitValue = xPos;
			posIncValue *= -1.f;
		}
		// cold 0, light 1, fire 2
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 10; ++j)
			{
				if (skillFunctionTypes[i * 10 + j] == eSkillFunctionType::Passive)
					continue;

				if (PlayerManager::learnedSkill[i][j] > 0)
				{
					skillMatPos.push_back(Vector2(xPos, yPos));
					xPos += posIncValue;
				}
				else
				{
					skillMatPos.push_back(Vector2(-99.f, -99.f));
				}
			}
			xPos = xInitValue;
			++yPos;
		}
	}
}
