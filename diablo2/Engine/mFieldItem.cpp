#include "mFieldItem.h"

#include "../engine_source/mMeshRenderer.h"

namespace m
{
	FieldItem::FieldItem(eItem item, Vector3 initPos)
		: Item(item)
	{
		ADD_COMP(this, MeshRenderer);
		ADD_COMP(this, Collider2D);

		SET_MESH(this, L"RectMesh");
		SET_MATERIAL(this, fieldItemTable[(int)item]);

		MAKE_GET_TEX(this, tex);
		SET_SCALE_TEX_SIZE_WITH_RAT(this, tex, 1.f);

		SET_POS_VEC(this, initPos);
	}
	FieldItem::~FieldItem()
	{
	    
	}
	void FieldItem::Initialize()
	{}
	void FieldItem::Update()
	{}
	void FieldItem::LateUpdate()
	{}
	void FieldItem::Render()
	{}
}