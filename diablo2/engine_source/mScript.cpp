#include "mScript.h"
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
	}
	void Script::OnCollisionStay(Collider2D* other)
	{
	}
	void Script::OnCollisionExit(Collider2D* other)
	{
	}
}