#pragma once
#include "mEntity.h"
#include "mEnums.h"
namespace m
{
	using namespace m::enums;
	using namespace m::math;
	class GameObject;
	class Component : public Entity
	{
	public:
		Component(eComponentType type);
		~Component();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		void SetOwner(GameObject* owner) { mOwner = owner; }
		GameObject* GetOwner() { return mOwner; }
	private:
		const eComponentType mType;
		GameObject* mOwner;
	};

}

