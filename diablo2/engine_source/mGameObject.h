#pragma once
#include "mEntity.h"
#include "mMesh.h"
#include "mShader.h"
#include "mRenderer.h"

namespace m {
	class Scene;
    class GameObject : public Entity
    {
	public:
		enum eState
		{
			Active,
			Paused,
			Dead,
		};

		GameObject(Vector4 initPos, Vector4 initColor, enums::eGameObjectType objectType, float _iSize, Scene* scene);
		virtual ~GameObject();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		Vector4 GetPos() { return mVertexInfo.pos; }
		float GetSize() { return fSize; }

		void SetState(eState state) { mState = state; }
		eState GetState() { return mState; }
		enums::eGameObjectType GetGameObjectType() { return mObjectType; }
	private:
		eState mState;
		renderer::Vertex mVertexInfo;

		Mesh* mesh;

		float fSize;
		enums::eGameObjectType mObjectType;
		Scene* onwerScene;
		//std::vector<Component*> mComponents;
		//int y;
		//int x;
    };
}


