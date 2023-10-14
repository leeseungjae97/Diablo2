#pragma once
#include "ItemLookUpTables.h"
#include "mItemScript.h"
namespace m
{
    class PotionScript :
        public ItemScript
    {
    public:
        PotionScript();
        virtual ~PotionScript();

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

