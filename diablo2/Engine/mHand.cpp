#include "mHand.h"
namespace m
{
	Hand::Hand(GameObject* parent, bool _bRightHand)
		: mHandScript(nullptr)
		, bRightHand(_bRightHand)
	{
	}

	Hand::~Hand()
	{
	}

	void Hand::Update()
	{
		GameObject::Update();
	}

	void Hand::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void Hand::Render()
	{
		GameObject::Render();
	}

	void Hand::Initialize()
	{
		GameObject::Initialize();
	}
}
