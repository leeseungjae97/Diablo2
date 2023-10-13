#include "mSkillFollower.h"

#include "../engine_source/mSceneManager.h"

#include "mTileAffectOverlay.h"

namespace m
{
    SkillFollower::SkillFollower(eSkillType type, int count, Vector3 initPos, Vector3 _desPosition, Camera* camera)
        : SkillStraight(type, initPos, 300.f, true, false)
        , iFollowerCount(count)
        , iCurCount(0)
        , fFollowerGenerateTime(0.f)
        , fAcc(0.f)
        , iFollowerLoopCount(10)
    {
        //SetDestPosition(_desPosition);
        //destPosition = _desPosition;
        //SetLimitDistance(1000.f);
        SetCamera(camera);
    }

    SkillFollower::~SkillFollower()
    {
    }

    void SkillFollower::Initialize()
    {
        SkillStraight::Initialize();
        makeFollower();
    }

    void SkillFollower::Update()
    {
        SkillStraight::Update();
        if(GetSkillCrash())
        {
            for (int i = iCurCount; i < iFollowerCount; ++i)
            {
                TileAffectOverlay* mTAO = followers[i];

                if (mTAO)
                    mTAO->SetState(eState::Delete);
            }

            /*for(TileAffectOverlay* mTAO : followers)
            {
                if(mTAO)
                    mTAO->SetState(eState::Delete);
            }*/
            SetState(eState::Delete);
        }
        else
        {
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
            if (i + 1 == iFollowerCount)
            {
                ADD_COMP(mTAO, AudioSource);
            }
            mTAO->SetLoopCount(iFollowerLoopCount);
            mTAO->SetCamera(GetCamera());
            eLayerType mOverlayType;
            if (skillOwnerType == eLayerType::PlayerSkill) mOverlayType = eLayerType::PlayerOverlay;
            else mOverlayType = eLayerType::MonsterOverlay;
            SceneManager::GetActiveScene()->AddGameObject(mOverlayType, mTAO);
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
