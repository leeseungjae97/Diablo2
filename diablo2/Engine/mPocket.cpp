#include "mPocket.h"
namespace m
{
	Pocket::Pocket()
		:bBelt(false)
	{
		Scene* curScene = SceneManager::GetActiveScene();
		
		for (int i = 0; i < 4; ++i)
		{
			Inven* inven = new Inven();
			inven->SetState(eState::RenderUpdate);

			SET_SCALE_XYZ(inven, (288.f / 10.f) * Texture::GetWidRatio()
				, (114.f / 4.f) * Texture::GetHeiRatio(), 0.f);
			curScene->AddGameObject(eLayerType::UI, inven);
			defaultPocketInvens.push_back(inven);
		}
		for (int i = 0; i < 8; ++i)
		{
			Inven* inven = new Inven();
			inven->SetState(eState::NoRenderNoUpdate);
			curScene->AddGameObject(eLayerType::UI, inven);
			exPocketInvens.push_back(inven);
		}
	}
	Pocket::~Pocket()
	{
	}
	void Pocket::Initialize()
	{
	}
	void Pocket::Update()
	{
	}
	void Pocket::LateUpdate()
	{
	}
	void Pocket::Render()
	{
	}
}