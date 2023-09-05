#include "mItem.h"

namespace m
{
	Item::Item(eItem type)
		: mType(itemTypeTable[(UINT)type])
		, mItem(type)
		, mInvenMaterial()
		, mFieldMaterial()
	    , mStashType(StashManager::eStashType::End)
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