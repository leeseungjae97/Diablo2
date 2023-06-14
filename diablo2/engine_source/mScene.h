#pragma once
#include "mEntity.h"
#include "mLayer.h"
namespace m
{
	class Scene : public Entity
	{
	public:
		Scene();
		virtual ~Scene();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

	private:
		std::vector<Layer*> mLayers;
	};
}

