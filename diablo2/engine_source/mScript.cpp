#include "mScript.h"
#include "../engine_source/mGameObject.h"

namespace m
{
	Script::Script()
		:Component(enums::eComponentType::Script)
	{
	}
	Script::~Script()
	{
	}
	void Script::Initialize()
	{
	}
	void Script::Update()
	{
	}
	void Script::LateUpdate()
	{
	}
	void Script::Render()
	{
	}

	void Script::OnCollisionEnter(Collider2D* other)
	{
		int intersectNum = GetOwner()->GetComponent<Collider2D>()->GetInsertsectColliderNumber();
		if (intersectNum > 0)
			GetOwner()->GetComponent<Collider2D>()->SetRectColor(eColor::Red);
	}
	void Script::OnCollisionStay(Collider2D* other)
	{
	}
	void Script::OnCollisionExit(Collider2D* other)
	{
		int intersectNum = GetOwner()->GetComponent<Collider2D>()->GetInsertsectColliderNumber();
		if (intersectNum == 0)
			GetOwner()->GetComponent<Collider2D>()->SetRectColor(eColor::Green);
	}
}