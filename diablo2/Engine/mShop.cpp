#include "mShop.h"

#include "../engine_source/mStashManager.h"
#include "../engine_source/mSceneManager.h"
#include "../engine_source/mMeshRenderer.h"

#include "mButton.h"
#include "mInvenItem.h"
#include "mItemScript.h"

namespace m
{
    Shop::Shop(Camera* camera)
        : mButtonBuy(nullptr)
        , mButtonSell(nullptr)
    {
        SetCamera(camera);
        SetName(L"shop_invens");

        SET_MESH(this, L"RectMesh");
        SET_MATERIAL(this, L"shopInventory");

        MAKE_GET_TEX(this, tex);
        SET_SCALE_TEX_SIZE_WITH_RAT(this, tex, 0.f);
        SET_POS_XYZ(this, -(tex->GetMetaDataWidth() * Texture::GetWidRatio() / 2.f)
            , RESOL_H_HEI - tex->GetMetaDataHeight() * Texture::GetHeiRatio() / 2.f, -1.0f);

        Scene* curScene = SceneManager::GetActiveScene();
        curScene->AddGameObject(eLayerType::UI, this);

        SetState(NoRenderUpdate);
    }

    Shop::~Shop()
    {
    }

    void Shop::Initialize()
    {
        UI::Initialize();
    }

    void Shop::Update()
    {
        UI::Update();
        
        if(GetState() == RenderUpdate)
        {
            StashManager::SetCurRenderShop(this);
        }
        if (Input::GetKeyDown(eKeyCode::ESC))
        {
            SetState(eState::NoRenderUpdate);
        }

        StashManager::SetShopInventoryVisible(GetState());
    }

    void Shop::LateUpdate()
    {
        UI::LateUpdate();
    }

    void Shop::Render()
    {
        UI::Render();
    }

    void Shop::ItemInit(eNPCType type)
    {
        Scene* curScene = SceneManager::GetActiveScene();
        StashManager::ClearItems(StashManager::eStashType::Shop);
        if(type == eNPCType::ConsumNPC)
        {
            {
                InvenItem* hpPotion = new InvenItem(eItem::mpPotion1);

                hpPotion->SetCamera(GetCamera());
                hpPotion->SetState(GameObject::RenderUpdate);
                ADD_COMP(hpPotion, ItemScript);
                curScene->AddGameObject(eLayerType::Item, hpPotion);
                StashManager::AddItem(hpPotion, StashManager::eStashType::Shop);
            }
            {
                InvenItem* hpPotion = new InvenItem(eItem::hpPotion1);

                hpPotion->SetCamera(GetCamera());
                hpPotion->SetState(GameObject::RenderUpdate);
                ADD_COMP(hpPotion, ItemScript);
                curScene->AddGameObject(eLayerType::Item, hpPotion);
                StashManager::AddItem(hpPotion, StashManager::eStashType::Shop);
            }

        }else
        {
            {
                InvenItem* hpPotion = new InvenItem(eItem::jaredsStone);

                hpPotion->SetCamera(GetCamera());
                hpPotion->SetState(GameObject::RenderUpdate);
                ADD_COMP(hpPotion, ItemScript);
                curScene->AddGameObject(eLayerType::Item, hpPotion);
                StashManager::AddItem(hpPotion, StashManager::eStashType::Shop);
            }
            {
                InvenItem* hpPotion = new InvenItem(eItem::leaderArmor);

                hpPotion->SetCamera(GetCamera());
                hpPotion->SetState(GameObject::RenderUpdate);
                ADD_COMP(hpPotion, ItemScript);
                curScene->AddGameObject(eLayerType::Item, hpPotion);
                StashManager::AddItem(hpPotion, StashManager::eStashType::Shop);
            }
            {
                InvenItem* hpPotion = new InvenItem(eItem::cap);
                hpPotion->SetCamera(GetCamera());
                hpPotion->SetState(GameObject::RenderUpdate);
                ADD_COMP(hpPotion, ItemScript);
                curScene->AddGameObject(eLayerType::Item, hpPotion);
                StashManager::AddItem(hpPotion, StashManager::eStashType::Shop);
            }
        }

        StashManager::InitItems(StashManager::eStashType::Shop);
    }
}
