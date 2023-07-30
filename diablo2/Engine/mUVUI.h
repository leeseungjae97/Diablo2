#pragma once
#include "../engine_source/mUI.h"
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

    private:
        float mUVCoord;
    };
}

