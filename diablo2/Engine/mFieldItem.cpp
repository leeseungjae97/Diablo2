#include "mFieldItem.h"

#include "../engine_source/mAudioSource.h"
#include "../engine_source/mMeshRenderer.h"
#include "../engine_source/mFontWrapper.h"
#include "../engine_source/mSceneManager.h"
#include "../engine_source/mTrappingColor.h"
#include "mUI.h"

namespace m
{
	FieldItem::FieldItem(eItem item, Vector3 initPos)
		: Item(item)
	    , bDownAlt(false)
	    , bDropFirst(true)
	    , moneyAmount(0)
	{
		MeshRenderer* mr = ADD_COMP(this, MeshRenderer);
		mr->AddTrappingColorBuffer();

		ADD_COMP(this, AudioSource);

		Animator* animator = ADD_COMP(this, Animator);

		SET_MESH(this, L"RectMesh");
		SET_MATERIAL(this, L"AnimationMaterial");
		SHARED_MAT mat = RESOURCE_FIND(Material, fieldItemAnimTable[(int)item]);

		animator->Create(
			fieldItemAnimTable[(int)item] + L"drop"
			, mat->GetTexture()
			, Vector2::Zero
			, itemFieldAnimSpaceTable[(int)item]
			, fieldItemAnimLenght[(int)item]
			, Vector2::Zero
			, Vector2(0.f, itemFieldAnimSpaceTable[(int)item].y / 2.f)
			, 0.03f
		);

		SET_SCALE_XYZ(this
			, itemFieldAnimSpaceTable[(int)item].x
			, itemFieldAnimSpaceTable[(int)item].y
			, 1.f
		);

		SET_POS_VEC(this, initPos);

		animator->PlayAnimation(fieldItemAnimTable[(int)item] + L"drop", false);
		animator->EndEvent(fieldItemAnimTable[(int)item] + L"drop") = std::make_shared<std::function<void()>>([this]()
		{
			SET_MATERIAL(this, fieldItemTable[(int)mItem]);

		    MAKE_GET_TEX(this, tex);
		    SET_SCALE_TEX_SIZE(this, tex, 1.f);

		    //ADD_COMP(this, Collider2D);
		});

		mNameUI = new UI();

		SET_MESH(mNameUI, L"RectMesh");
		SET_MATERIAL(mNameUI, L"itemExBack");
		mNameUI->SetTextNormalColor(Vector4(255.f, 255.f, 255.f, 255.f));
		mNameUI->SetTextSize(15.f);
		Vector2 size = Vector2::Zero;
		if (item == eItem::gold)
		{
			moneyAmount += rand() % 250;
			moneyAmount += 100;
			std::wstring text = std::to_wstring(moneyAmount) + L"°ñµå";
			mNameUI->SetText(text);
			size = FontWrapper::GetTextSize(text.c_str(), 15.f);
		}
		else
		{
			mNameUI->SetText(itemCostFunctionNames[(int)item][0]);
			size = FontWrapper::GetTextSize(itemCostFunctionNames[(int)item][0].c_str(), 15.f);
		}

		SET_SCALE_XYZ(mNameUI, size.x, size.y, 1.f);
		initPos.z -= 0.1;
		initPos.y += size.y;
		SET_POS_XYZ(mNameUI, initPos.x, initPos.y, initPos.z);
		mNameUI->SetState(eState::NoRenderNoUpdate);

		SceneManager::GetActiveScene()->AddGameObject(eLayerType::CanMoveUI, mNameUI);
	}
	FieldItem::~FieldItem()
	{
		if (mNameUI)
			mNameUI->SetState(eState::Delete);
	}
	void FieldItem::Initialize()
	{
		Item::Initialize();
	}
	void FieldItem::Update()
	{
		Item::Update();
		AudioSource* as = GET_COMP(this, AudioSource);
		if(bDropFirst)
		{
			as->Play(5, itemDropSoundPaths[(int)eItem::END], false, false);
			bDropFirst = false;
		}
		as->PlayOnce(5, itemDropSoundPaths[(int)mItem], false, false, false);

		if (mNameUI && nullptr == mNameUI->GetCamera()) mNameUI->SetCamera(GetCamera());

		if (GetHover() && !bDownAlt)
			mNameUI->SetState(RenderUpdate);
		if (!GetHover() || !bDownAlt)
			mNameUI->SetState(NoRenderNoUpdate);
		
		if (GetHover()
			|| mNameUI->GetHover())
		{
			if (Input::GetKeyDown(eKeyCode::LBUTTON))
			{
				StashManager::ChangeFieldItemToInvenItem(this);
			}

			MeshRenderer* mr = GET_COMP(this, MeshRenderer);
			mr->SetTrappingColor(Vector4(0.8f, 0.8f, 0.8f, 0.8f));
		}else
		{
			MeshRenderer* mr = GET_COMP(this, MeshRenderer);
			mr->SetTrappingColor(Vector4(0.f, 0.f, 0.f, 0.f));
		}
		if (Input::GetKeyUp(eKeyCode::L_ALT))
		{
			mNameUI->SetState(NoRenderNoUpdate);
			bDownAlt = false;
		}

		if (Input::GetKeyDown(eKeyCode::L_ALT)
			|| Input::GetKey(eKeyCode::L_ALT))
		{
			mNameUI->SetState(RenderUpdate);
			bDownAlt = true;
		}
	}
	void FieldItem::LateUpdate()
	{
		Item::LateUpdate();
	}
	void FieldItem::Render()
	{
		Item::Render();
	}
}