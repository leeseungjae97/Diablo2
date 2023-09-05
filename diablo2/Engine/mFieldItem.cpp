#include "mFieldItem.h"

#include "../engine_source/mMeshRenderer.h"

namespace m
{
	FieldItem::FieldItem(eItem item, Vector3 initPos)
		: Item(item)
	{
		ADD_COMP(this, MeshRenderer);

		Animator* animator = ADD_COMP(this, Animator);

		SET_MESH(this, L"RectMesh");
		SET_MATERIAL(this, L"AnimationMaterial");
		SHARED_MAT mat = RESOURCE_FIND(Material, fieldItemAnimTable[(int)item]);

		animator->Create(
			fieldItemAnimTable[(int)item] + L"drop"
		    , mat->GetTexture()
			, Vector2::Zero
			, itemFieldAnimSpaceTable[(int)item]
			, 17
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
		animator->EndEvent(fieldItemAnimTable[(int)item] + L"drop") = [this]()
		{
			SET_MATERIAL(this, fieldItemTable[(int)mItem]);

            MAKE_GET_TEX(this, tex);
            SET_SCALE_TEX_SIZE(this, tex, 1.f);

			ADD_COMP(this, Collider2D);
		};
	}
	FieldItem::~FieldItem()
	{
	    
	}
	void FieldItem::Initialize()
	{
		Item::Initialize();
	}
	void FieldItem::Update()
	{
		Item::Update();
		if(GetHover())
		{
		    if(Input::GetKeyDown(eKeyCode::LBUTTON))
		    {
				StashManager::ChangeFieldItemToInvenItem(this);
		    }
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