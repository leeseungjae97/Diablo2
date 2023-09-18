#pragma once
#include "../engine_source/mUI.h"

#include "../engine_source/mMaterial.h"

namespace m
{
    class UVUI :
        public UI
    {
    public:
        UVUI();
        virtual ~UVUI();

        virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

        void SetUVCoord(float uv) { mUVCoord = uv; }
        float GetUVCoord() { return mUVCoord; }

        void SetOriginMaterial(std::shared_ptr<graphics::Material> mat) { mOriginMaterial = mat; }
        void SetAddictionMaterial(std::shared_ptr<graphics::Material> mat) { mAddictionMaterial = mat; }

        void SetAddiction();
        void SetOrigin();

        void SetMType(int type) { mType = type; }
    private:
        float mUVCoord;
        int mType;
        std::shared_ptr<graphics::Material> mAddictionMaterial;
        std::shared_ptr<graphics::Material> mOriginMaterial;
    };
}

