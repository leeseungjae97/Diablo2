#pragma once
#include "../engine_source/mUI.h"

#include "mInvenItem.h"
#include "mEmptyRect.h"

namespace m
{
    class Button;
    class Inventory : public UI
    {
    public:
        Inventory(Camera* camera);
        virtual ~Inventory();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;

    private:
        Button* closeBtn;
    };
}

