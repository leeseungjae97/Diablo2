#include "mFieldItem.h"

#include "../engine_source/mMeshRenderer.h"

namespace m
{
	FieldItem::FieldItem(eItem item)
		: Item(item)
	{
		ADD_COMP(this, MeshRenderer);
		ADD_COMP(this, Collider2D);

		SET_MESH(this, L"RectMesh");

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