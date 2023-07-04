#pragma once
#include "..\engine_source\mUI.h"
namespace m
{
    class InvenItem :
        public UI
    {
    public:
        InvenItem();
        virtual ~InvenItem();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;
    private:
        bool bSetMouseFollow;
    };
}

