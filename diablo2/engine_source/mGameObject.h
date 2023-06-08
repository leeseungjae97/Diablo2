#pragma once
#include "mEntity.h"
#include "mConstantBuffer.h"
namespace m
{
    class GameObject :
        public Entity
    {
	public:
		struct Vertex
		{
			Vector4 pos;
			Vector4 color;
		};
		enum eState
		{
			Active,
			Paused,
			Dead,
		};

		GameObject(Vector4 initPos, Vector4 initColor, bool _moveable);
		virtual ~GameObject();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

	private:
		eState mState;
		m::graphics::ConstantBuffer* constantBuffer = nullptr;
		Vertex mVertexInfo;
		bool moveable;
		//std::vector<Component*> mComponents;
		//int y;
		//int x;
    };
}


