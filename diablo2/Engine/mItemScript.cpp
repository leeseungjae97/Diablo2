#include "mItemScript.h"

#include "../engine_source/mGameObject.h"

namespace m
{
	ItemScript::ItemScript()
	{
	}
	ItemScript::~ItemScript()
	{
	}
	void ItemScript::Initialize()
	{
	}
	void ItemScript::Update()
	{
	}
	void ItemScript::OnCollisionEnter(Collider2D* other)
	{
		GetOwner()->GetComponent<Collider2D>()->SetRectColor(eColor::Red);
	}
	void ItemScript::OnCollisionStay(Collider2D* other)
	{
		
	}
	void ItemScript::OnCollisionExit(Collider2D* other)
	{
		GetOwner()->GetComponent<Collider2D>()->SetRectColor(eColor::Green);
	}
}