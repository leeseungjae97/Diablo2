#include "mItem.h"

namespace m
{
	Item::Item(eItemType type)
		: mType(type)
		, mInvenMaterial()
		, mFieldMaterial()
		, iInvenXSpace(0)
		, iInvenYSpace(0)
	{}
	Item::~Item()
	{}
	void Item::Initialize()
	{
		GameObject::Initialize();
	}
	void Item::Update()
	{
		GameObject::Update();
	}
	void Item::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Item::Render()
	{
		GameObject::Render();
	}
}