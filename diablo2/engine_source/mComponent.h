#pragma once
#include "mEntity.h"
#include "mEnums.h"
namespace m
{
	using namespace m::enums;
	class Component : public Entity
	{
	public:
		Component();
		~Component();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

	private:
		const eComponentType mType;
	};

}

