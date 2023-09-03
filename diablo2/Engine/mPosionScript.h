#pragma once
#include "ItemLookUpTables.h"
#include "mItemScript.h"
namespace m
{
    class PosionScript :
        public ItemScript
    {
    public:
        PosionScript();
        virtual ~PosionScript();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;

        void SetOwnerState(GameObject::eState state) { mOwnerState = state; }
        void SetOwnerItem(eItem _item) { mOwnerItem = _item; }

    private:
        GameObject::eState mOwnerState;
        eItem mOwnerItem;
    };
}

