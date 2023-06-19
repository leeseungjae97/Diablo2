#pragma once
#include "mComponent.h"
#include "mMesh.h"
#include "mMaterial.h"
#include "mTransform.h"
#include "mRenderer.h"
#include "mGameObject.h"

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

		void SetMesh(Mesh* mesh) { mMesh = mesh; }
		void SetMaterial(Material* material) { mMaterial = material; }

	private:
		Mesh* mMesh;
		Material* mMaterial;
    };
}

