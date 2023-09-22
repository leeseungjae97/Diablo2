#include "mSkillFollowing.h"

#include "../engine_source/mSceneManager.h"

#include "mPlayerManager.h"
#include "AffectOverlayLookUpTable.h"
#include "mPlayer.h"
#include "mSkillFollower.h"
#include "mTileAffectOverlay.h"

namespace m
{
    SkillFollowing::SkillFollowing(eSkillType type, GameObject* owner, int count, Vector3 initPos, Camera* camera)
        : Skill(type, initPos)
        , iFollowerCount(count)
        , iCurCount(0)
        , iFollowerLoopCount(0)
        , fFollowerGenerateTime(0.f)
        , fAcc(0.f)
        , mFollowing(owner)

    {
        SET_POS_VEC(this, initPos);
        SET_MESH(this, L"PointMesh");
        SET_MATERIAL(this, L"noneRect");
        SetCamera(camera);
    }

    SkillFollowing::~SkillFollowing()
    {
    }

    void SkillFollowing::Initialize()
    {
        Skill::Initialize();
        makeFollower();
    }

    void SkillFollowing::Update()
    {
        Skill::Update();
        //SET_POS_VEC(this, GET_POS(mFollowing));
        if (iFollowerCount <= iCurCount)
        {
            SetState(eState::Delete);
        }

        fAcc += Time::fDeltaTime();
        if (fAcc >= fFollowerGenerateTime)
        {
            generateFollower();
            fAcc = 0.f;
        }
    }

    void SkillFollowing::LateUpdate()
    {
        Skill::LateUpdate();
    }

    void SkillFollowing::Render()
    {
        Skill::Render();
    }
    void SkillFollowing::makeFollower()
    {
        Vector3 pos = GET_POS(this);
        for (int i = 0; i < iFollowerCount; ++i)
        {
            //int m = rand() % 3;
            TileAffectOverlay* mTAO = new TileAffectOverlay(pos, eAffectOverlayType::Fire2, skillOwnerType);
            mTAO->SetLoopCount(iFollowerLoopCount);
            mTAO->SetCamera(GetCamera());
            eLayerType mOverlayType;
            if (skillOwnerType == eLayerType::PlayerSkill) mOverlayType = eLayerType::PlayerOverlay;
            else mOverlayType = eLayerType::MonsterOverlay;
            SceneManager::GetActiveScene()->AddGameObject(mOverlayType, mTAO);
            followers.push_back(mTAO);
        }
    }
    void SkillFollowing::generateFollower()
    {
        if (iFollowerCount <= iCurCount) return;

        Vector3 pos =GET_POS(mFollowing);
        pos.y += GET_SCALE(mFollowing).y;

        SET_POS_VEC(followers[iCurCount], pos);
        followers[iCurCount]->SetCamera(GetCamera());
        followers[iCurCount]->ActiveOverlay();
        ++iCurCount;
    }
}
