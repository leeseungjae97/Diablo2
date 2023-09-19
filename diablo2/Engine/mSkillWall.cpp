#include "mSkillWall.h"

#include "../engine_source/mMouseManager.h"
#include "../engine_source/mSceneManager.h"

#include "mSkillFollower.h"
#include "mSkillStraight.h"
#include "mTileAffectOverlay.h"

namespace m
{
    SkillWall::SkillWall(eSkillType type, Vector3 initPos, Camera* camera, eLayerType ownerLayer)
        : Skill(type, initPos)
    {
        SET_MESH(this, L"PointMesh");
        SET_MATERIAL(this, L"noneRect");
        SetCamera(camera);
        skillOwnerType = ownerLayer;
        makeNormalVector(camera, initPos, type);
    }

    SkillWall::~SkillWall()
    {
    }

    void SkillWall::Initialize()
    {
        Skill::Initialize();
    }

    void SkillWall::Update()
    {
        Skill::Update();
    }

    void SkillWall::LateUpdate()
    {
        Skill::LateUpdate();
    }

    void SkillWall::Render()
    {
        Skill::Render();
    }

    void SkillWall::makeNormalVector(Camera* camera, Vector3 initPos, eSkillType type)
    {
        //ownerLayer;
        Vector3 targetPos;

        if(skillOwnerType == eLayerType::PlayerSkill)
        {
            Vector3 vMouseVector3 = MouseManager::UnprojectionMousePos(1.f, camera);
            vMouseVector3.z = 1.f;
            targetPos = vMouseVector3;
        }else
        {
            targetPos = TileManager::GetPlayerPosition();
        }

        Vector3 distanceVector = targetPos - initPos;

        Vector3 downNormalVector = Vector3(-distanceVector.y, distanceVector.x, 1.f);
        Vector3 downVector = Vector3(targetPos.x + downNormalVector.x
            , targetPos.y + downNormalVector.y,
            1.f
        );

        Vector3 upNormalVector = Vector3(distanceVector.y, -distanceVector.x, 1.f);
        Vector3 upVector = Vector3(targetPos.x + upNormalVector.x
            , targetPos.y + upNormalVector.y,
            1.f
        );

        TileAffectOverlay* mTAO = new TileAffectOverlay(targetPos, eAffectOverlayType::Fire2, skillOwnerType);
        mTAO->SetCamera(camera);
        mTAO->ActiveOverlay();

        SceneManager::GetActiveScene()->AddGameObject(skillOwnerType, mTAO);

        SkillFollower* sf1 = new SkillFollower(type, 10, targetPos, downVector);
        SkillFollower* sf2 = new SkillFollower(type, 10, targetPos, upVector);

        sf1->SetCamera(camera);
        sf2->SetCamera(camera);

        sf1->SetFollowerGenerateTime(0.08f);
        sf2->SetFollowerGenerateTime(0.08f);

        sf1->SetSkillOwnerLayer(skillOwnerType);
        sf2->SetSkillOwnerLayer(skillOwnerType);
        //sf->SetDestPosition(vMouseVector3);
        SceneManager::GetActiveScene()->AddGameObject(skillOwnerType, sf1);
        SceneManager::GetActiveScene()->AddGameObject(skillOwnerType, sf2);

        sf1->SetDestPosition(downVector);
        sf2->SetDestPosition(upVector);

        sf1->SkillFire();
        sf2->SkillFire();

        //    Vector3 downNormalVector = Vector3(-distanceVector.y, distanceVector.x, 1.f);
        //    Vector3 downVector = Vector3(vMouseVector3.x + downNormalVector.x
        //        , vMouseVector3.y + downNormalVector.y,
        //        1.f
        //    );

        //    Vector3 upNormalVector = Vector3(distanceVector.y, -distanceVector.x, 1.f);
        //    Vector3 upVector = Vector3(vMouseVector3.x + upNormalVector.x
        //        , vMouseVector3.y + upNormalVector.y,
        //        1.f
        //    );
        //    SkillStraight* sf = new SkillStraight(eSkillType::iceBolt, vMouseVector3, 300.f);
        //    sf->SetCamera(camera);
        //    sf->SetDestPosition(downVector);
        //    SceneManager::GetActiveScene()->AddGameObject(eLayerType::PlayerSkill, sf);
        //    sf->SkillFire();

        //    SkillStraight* sf1 = new SkillStraight(eSkillType::iceBolt, vMouseVector3, 300.f);
        //    sf1->SetCamera(camera);
        //    sf1->SetDestPosition(upVector);
        //    SceneManager::GetActiveScene()->AddGameObject(eLayerType::PlayerSkill, sf1);
        //    sf1->SkillFire();
    }
}
