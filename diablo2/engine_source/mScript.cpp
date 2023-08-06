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
		std::vector<Collider2D*> cols = GetOwner()->GetComponents<Collider2D>();
		for (Collider2D* col : cols)
		{
			const std::vector<Collider2D*> cos = col->GetCollidereds();

			if (!cos.empty())
			{
				col->SetColor(eColor::Red);
				col->SetEnter();
			}
			else
			{
				col->SetColor(eColor::Green);
				col->SetExit();
			}
		}
	}
	void Script::LateUpdate()
	{
	}
	void Script::Render()
	{
	}

	void Script::OnCollisionEnter(Collider2D* other)
	{
		std::vector<Collider2D*> cols = GetOwner()->GetComponents<Collider2D>();
		for (Collider2D* col : cols)
		{
			const std::vector<Collider2D*> cos = col->GetCollidereds();

			if (!cos.empty())
				col->SetColor(eColor::Red);
		}
	}
	void Script::OnCollisionStay(Collider2D* other)
	{
	}
	void Script::OnCollisionExit(Collider2D* other)
	{
		std::vector<Collider2D*> cols = GetOwner()->GetComponents<Collider2D>();
		for (Collider2D* col : cols)
		{
			const std::vector<Collider2D*> cos = col->GetCollidereds();

			if (cos.empty())
				col->SetColor(eColor::Green);
		}
	}
}