#include "mSkillFollower.h"

#include "mSceneManager.h"
#include "mTileAffectOverlay.h"

namespace m
{
    SkillFollower::SkillFollower(eSkillType type, int count, Vector3 initPos, Vector3 _desPosition)
        : SkillStraight(type, initPos, 300.f, true, false)
        , iFollowerCount(count)
        , iCurCount(0)
        , fFollowerGenerateTime(0.f)
        , fAcc(0.f)
    {
        //SetDestPosition(_desPosition);
        //destPosition = _desPosition;
        makeFollower();
    }

    SkillFollower::~SkillFollower()
    {
    }

    void SkillFollower::Initialize()
    {
        SkillStraight::Initialize();
    }

    void SkillFollower::Update()
    {
        SkillStraight::Update();
        if (iFollowerCount <= iCurCount)
        {
            SetState(eState::Delete);
            bSkillFire = false;
        }

        fAcc += Time::fDeltaTime();
        if (fAcc >= fFollowerGenerateTime)
        {
            generateFollower();
            fAcc = 0.f;
        }
        
    }

    void SkillFollower::LateUpdate()
    {
        SkillStraight::LateUpdate();
    }

    void SkillFollower::Render()
    {
        SkillStraight::Render();
    }
    void SkillFollower::makeFollower()
    {
        Vector3 pos = GET_POS(this);
        for(int i =0  ; i < iFollowerCount; ++i)
        {
            //int m = rand() % 3;
            TileAffectOverlay* mTAO = new TileAffectOverlay(pos, eAffectOverlayType::Fire2, skillOwnerType);
            
            SceneManager::GetActiveScene()->AddGameObject(skillOwnerType, mTAO);
            followers.push_back(mTAO);
        }
    }
    void SkillFollower::generateFollower()
    {
        if (iFollowerCount <= iCurCount) return;
        
        SET_POS_VEC(followers[iCurCount], GET_POS(this));
        followers[iCurCount]->SetCamera(GetCamera());
        followers[iCurCount]->ActiveOverlay();
        ++iCurCount;
    }
}
