#include "mHand.h"
namespace m
{
	Hand::Hand(GameObject* parent, bool fh)
		: mHandScript(nullptr)
		, mAnimator(nullptr)
		, bRightHand(fh)
	{
		Transform* fr = GET_COMP(this, Transform);
		fr->SetParent(GET_COMP(parent, Transform));

		mAnimator =ADD_COMP(this, Animator);
		ADD_COMP(this, MeshRenderer);

		SET_MESH(this, L"RectMesh");
		SET_MATERIAL(this, L"AnimationMaterial");
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
