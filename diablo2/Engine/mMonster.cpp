#include "mMonster.h"
namespace m
{
	Monster::Monster(Vector3 iniPos)
	{
		GetComponent<Transform>()->SetPosition(iniPos);
	}
	Monster::~Monster()
	{}
	void Monster::Initialize()
	{
		GameObject::Initialize();
	}
	void Monster::Update()
	{
		GameObject::Update();
	}
	void Monster::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Monster::Render()
	{
		GameObject::Render();
	}
}