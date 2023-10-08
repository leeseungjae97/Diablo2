#include "mPlayerHand.h"
namespace m
{
    PlayerHand::PlayerHand(GameObject* parent, bool fh)
        : Hand(parent, fh)
    {
    }

    PlayerHand::~PlayerHand()
    {
    }

    void PlayerHand::Initialize()
    {
        Hand::Initialize();
    }

    void PlayerHand::Update()
    {
        Hand::Update();
    }

    void PlayerHand::LateUpdate()
    {
        Hand::LateUpdate();
    }

    void PlayerHand::Render()
    {
        Hand::Render();
    }
}
