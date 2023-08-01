#pragma once
#include "mEntity.h"
#include "mLayer.h"

namespace m
{
	class Camera;
	class Scene : public Entity
	{
	public:
		Scene();
		virtual ~Scene();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		virtual void OnExit();
		virtual void OnEnter();

		void AddGameObject(eLayerType type, GameObject* gameObj);
		Layer& GetGameObjects(eLayerType type);
		template <typename T>
		std::vector<T*>& FindObjectsOfType()
		{
			std::vector<T*> findObjs = {};
			for (Layer* layer : mLayers)
			{
				auto gameObjs = layer->GetGameObjects();
				for (GameObject* obj : gameObjs)
				{
					T* buff = dynamic_cast<T*>(obj);
					if (buff != nullptr)
						findObjs.push_back(buff);
				}
			}
			return findObjs;
		}
		Layer& GetLayer(eLayerType type) { return mLayers[(UINT)type]; }
		void SetSceneMainCamera(Camera* camera) { sceneMainCamera = camera; }
		Camera* GetSceneMainCamera() { return sceneMainCamera; }
	private:
		Camera* sceneMainCamera;
		std::vector<Layer> mLayers;
	};
}

