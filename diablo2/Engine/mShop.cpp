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

        {
            InvenItem* hpPosion = new InvenItem(eItem::mpPosion1);

            hpPosion->SetCamera(GetCamera());
            hpPosion->SetState(GameObject::RenderUpdate);
            ADD_COMP(hpPosion, ItemScript);
            curScene->AddGameObject(eLayerType::Item, hpPosion);
            StashManager::AddItem(hpPosion, StashManager::eStashType::Shop);
        }
        {
            InvenItem* hpPosion = new InvenItem(eItem::hpPosion1);

            hpPosion->SetCamera(GetCamera());
            hpPosion->SetState(GameObject::RenderUpdate);
            ADD_COMP(hpPosion, ItemScript);
            curScene->AddGameObject(eLayerType::Item, hpPosion);
            StashManager::AddItem(hpPosion, StashManager::eStashType::Shop);
        }
        {
            InvenItem* hpPosion = new InvenItem(eItem::jaredsStone);

            hpPosion->SetCamera(GetCamera());
            hpPosion->SetState(GameObject::RenderUpdate);
            ADD_COMP(hpPosion, ItemScript);
            curScene->AddGameObject(eLayerType::Item, hpPosion);
            StashManager::AddItem(hpPosion, StashManager::eStashType::Shop);
        }

        StashManager::InitItems(StashManager::eStashType::Shop);
        SetState(NoRenderUpdate);
        //std::wstring buttonNames[4] = {
        //    L"shopInvenTab0Click",
        //    L"shopInvenTab1Click",
        //    L"shopInvenTab2Click",
        //    L"shopInvenTab3Click"
        //};
        
        //for(int i = 0; i < 4; ++i)
        //{
        //    SHARED_MAT mat = RESOURCE_FIND(Material, buttonNames[i]);
        //    if (nullptr == mat) continue;

        //    Button* tab = new Button();

        //    tab->SetCamera(camera);

        //    SET_MESH(tab, L"RectMesh");
        //    SET_MATERIAL_D(tab, mat);

        //    MAKE_GET_TEX(tab, tex);
        //    SET_SCALE_TEX_SIZE_WITH_RAT(tab, tex, 1.f);
        //    Vector3 scale = GET_SCALE(tab);
        //    SET_POS_XYZ(tab, 
        //        -RESOL_H_WID + 80.f * Texture::GetWidRatio() + (scale.x / 2.f) + ((scale.x + 1.f) * i),
        //        RESOL_H_HEI - 64.f * Texture::GetHeiRatio() + (-scale.y / 2.f)
        //        , -1.f);

        //    SceneManager::GetActiveScene()->AddGameObject(eLayerType::UI, tab);

        //    shopTabs.push_back(tab);
        //}
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
        //if (nullptr == tests[0]->GetCamera()) for (GameObject* t : tests) t->SetCamera(GetCamera());
        if(GetState() == RenderUpdate)
        {
            StashManager::SetCurRenderShop(this);
        }
        if (Input::GetKeyDown(eKeyCode::ESC))
        {
            SetState(eState::NoRenderUpdate);
        }

        //if(StashManager::GetInventoryState() == eState::NoRenderUpdate)
        //{
        //    StashManager::SetShopInventoryVisible(NoRenderUpdate);
        //}

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
}
