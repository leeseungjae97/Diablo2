#include "mMonsterScript.h"

namespace m
{
	template <typename T>
	MonsterScript<T>::MonsterScript()
	{
		T* t = {};
		mAnimator = GetOwner()->GetComponent<Animator>();
		//GET_COMP(GetOwner(), mAnimator, Animator);

		for (int i = 0; i < (UINT)T::eAnimationType::End; ++i)
		{
			SHARED_MAT mat;
			mat = RESOURCE_FIND(Material, t->textureString[i]);
		}


		for (int i = 0; i < (UINT)eMonsterDirection::End; ++i)
		{

		}
		T::eAnimationType::Attack1;
	}
	template <typename T>
	MonsterScript<T>::~MonsterScript()
	{
	}
	template <typename T>
	void MonsterScript<T>::Initialize()
	{
	}
	template <typename T>
	void MonsterScript<T>::Update()
	{
	}
	template <typename T>
	void MonsterScript<T>::LateUpdate()
	{
	}
	template <typename T>
	void MonsterScript<T>::Render()
	{
	}

}