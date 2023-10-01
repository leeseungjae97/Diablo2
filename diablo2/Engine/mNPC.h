#pragma once
#include "mMoveAbleObject.h"

#include "../engine_source/NPCLookUpTables.h"
namespace m
{
    class Button;
    class Shop;
    class InteractUI;

    class NPC :
        public MoveAbleObject
    {
    public:
        NPC(Vector3 initPos, eNPCType type);
        virtual ~NPC();

        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Initialize() override;
        virtual void Render() override;

        virtual void Hit(int damage, bool attackStun) override;

        void SetShop(Shop* shop);
    private:
        void makeUI();

    private:
        //std::vector<Button*> textes;
        InteractUI* mInteractUI;
        eNPCType mNPCType;
        Shop* mShop;
    };
}

