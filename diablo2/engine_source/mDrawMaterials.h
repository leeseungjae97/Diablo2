#pragma once
#include "mMeshRenderer.h"
#include "mStructedBuffer.h"
namespace m
{
    class DrawMaterials :
        public MeshRenderer
    {
    public:
        DrawMaterials();
        virtual ~DrawMaterials();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;

        void SetMaterials(std::vector < std::shared_ptr<Material>> _mats) { mats = _mats; }
        void SetMaterialsPos(std::vector<Vector2> _poss) { poss = _poss; }

    private:
        graphics::StructuredBuffer* mDrawMats;
        std::vector<std::shared_ptr<Material>> mats;
        std::vector<Vector2> poss;
    };
}

