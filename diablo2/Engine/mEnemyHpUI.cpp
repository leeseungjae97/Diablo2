#include "mEnemyHpUI.h"

#include "mFontWrapper.h"
#include "mMonster.h"
#include "mMouseManager.h"

namespace m
{
    EnemyHpUI::EnemyHpUI(Vector3 initPos)
        : mHoverMonster(nullptr)
        , fFontSize(0.f)
    {
        SET_POS_XYZ(this, 0.f, RESOL_HEI, initPos.z);
        SET_MESH(this, L"RectMesh");
        SET_MATERIAL(this, L"enemyHp");
        SetMType(2);
        //SetState(eState::NoRenderUpdate);
    }

    EnemyHpUI::~EnemyHpUI()
    {
    }

    void EnemyHpUI::Initialize()
    {
        UVUI::Initialize();
    }

    void EnemyHpUI::Update()
    {
        UVUI::Update();
        makeEnemyHpUI();
    }

    void EnemyHpUI::LateUpdate()
    {
        UVUI::LateUpdate();
    }

    void EnemyHpUI::Render()
    {
        UVUI::Render();
        getHoveredMonsterInformation();
    }
    void EnemyHpUI::makeEnemyHpUI()
    {
        const int monsterId = MouseManager::GetMouseOnMonsterId();
        if (monsterId == -1)
        {
            SetState(eState::NoRenderUpdate);
            return;
        }

        SetState(eState::RenderUpdate);

        Monster* monster = MonsterManager::GetMonster(monsterId);
        if (nullptr == monster) return;

        const std::wstring name = monster->GetMonsterName();
        Vector2 fontSize = FontWrapper::GetTextSize(name.c_str(), fFontSize);

        Vector3 pos = Vector3(0.f, RESOL_H_HEI - fontSize.y, GET_POS(this).z);
        SET_POS_VEC(this, pos);
        SET_SCALE_XYZ(this, fontSize.x, fontSize.y, 1.f);

        float percent = monster->GetMonsterHpPercent();
        SetUVCoord(percent);
    }
    void EnemyHpUI::getHoveredMonsterInformation()
    {
        const int monsterId = MouseManager::GetMouseOnMonsterId();
        if (monsterId == -1)
        {
            return;
        }

        Monster* monster = MonsterManager::GetMonster(monsterId);
        if (nullptr == monster) return;

        const std::wstring name = monster->GetMonsterName();

        Vector2 fontSize = FontWrapper::GetTextSize(name.c_str(), fFontSize);

        Vector3 pos = GetComponent<Transform>()->ProjectionCetnerPosition(fontSize);
        FontWrapper::DrawFont(name.c_str(), pos.x, pos.y, fFontSize, FONT_RGBA(255.f, 255.f, 255.f, 255.f));
    }

}
