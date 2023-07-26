#pragma once
#include "..\engine_source\mUI.h"
#include "mInvenItem.h"
#include "mInven.h"
namespace m
{
    class Pocket :
        public UI
    {
    public:
        Pocket();
        virtual ~Pocket();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;

    private:
        std::vector<Inven*> defaultPocketInvens;
        std::vector<Inven*> exPocketInvens;
        bool bBelt;
    };
}


