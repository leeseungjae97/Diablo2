#pragma once
#include "mComponent.h"
#include "mMesh.h"
#include "mMaterial.h"
#include "mStructedBuffer.h"

namespace m
{
    class MeshRenderer :
        public Component
    {
	public:
		MeshRenderer();
		~MeshRenderer();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void SetMesh(std::shared_ptr<Mesh> mesh) { mMesh = mesh; }
		void SetMaterial(std::shared_ptr<Material> material) { mMaterial = material; }
		std::shared_ptr<Material> GetMaterial() { return mMaterial; }
		std::shared_ptr<Mesh> GetMesh() { return mMesh; }

		void AddTrappingColorBuffer();
		void AddSpriteOffSetCenterBuffer();
		void AddSpriteAlphaBuffer();
		void SetTrappingColor(Vector4 color) { mTrappingColor.color = color; }
		void SetSpriteOffsetCenter(Vector2 offset) { mSpriteOffsetCenter.offset = offset; }
		void SetSpriteAlpha(float alpha) { mSpriteAlpha.alpha = alpha; }
	private:
		std::shared_ptr<Mesh> mMesh;
		std::shared_ptr<Material> mMaterial;

		TrapColor mTrappingColor;
		SpriteOffsetCenter mSpriteOffsetCenter;
		SpriteAlpha mSpriteAlpha;
		graphics::StructuredBuffer* mTrappingColorBuffer;
		graphics::StructuredBuffer* mSpriteOffSetCenterBuffer;
		graphics::StructuredBuffer* mSpriteAlphaBuffer;
    };
}

