#include "mSkillShortCutButton.h"

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

		if(GetOneClick())
		{
			skillImages->SetState(skillImages->GetState() == NoRenderUpdate ? RenderUpdate : NoRenderUpdate);
		}
		if (skillImages->GetState() == RenderUpdate)
		{
			GetHoverClickSkill();
		}

		if(!GetHover())
		{
			if(Input::GetKeyDown(eKeyCode::LBUTTON)) skillImages->SetState(NoRenderUpdate);
		}

		if (PlayerManager::GetSkill(mSkillIndex) != mSkillType)
		{
			mSkillType = PlayerManager::GetSkill(mSkillIndex);
			SET_MATERIAL(this, wsSkillIconNames[(int)mSkillType]);
			//SetNormalMaterial(RESOURCE_FIND(Material, wsSkillClickIconNames[(int)mSkillType]));
			//SetClickMaterial(RESOURCE_FIND(Material, wsSkillClickIconNames[(int)mSkillType]));
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

    void SkillShortCutButton::makeMa()
    {
		//mF5 = new UI();
		//mF4 = new UI();
		//mF3 = new UI();
		//mF2 = new UI();
		//mF1 = new UI();
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
