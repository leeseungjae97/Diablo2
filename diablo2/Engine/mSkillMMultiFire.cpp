#include "mSkillMMultiFire.h"

#include "mSceneManager.h"
#include "mSkillMultiFire.h"
namespace m
{
    SkillMMultiFire::SkillMMultiFire(eSkillType type, Vector3 initPos
        , int count, eLayerType layerType, Camera* camera)
        : Skill(type, initPos)
    {
        for(int i = 0 ; i < count ; ++i )
        {
            SkillMultiFire* smf = new SkillMultiFire(initPos, type, 10
                , (int)SkillMultiFire::eFireType::RandomLinear
                , layerType, Vector2(0.f, 10.f));
            smf->SetCamera(camera);
            SceneManager::GetActiveScene()->AddGameObject(layerType, smf);
            skills.push_back(smf);

        }
    }

    SkillMMultiFire::~SkillMMultiFire()
    {
    }

    void SkillMMultiFire::Initialize()
    {
        Skill::Initialize();
    }

    void SkillMMultiFire::Update()
    {
        Skill::Update();
        if(bSkillFire)
        {
            for (SkillMultiFire* smf : skills) smf->SkillFire();
            bSkillFire = false;

            SetState(Delete);
        }
    }

    void SkillMMultiFire::LateUpdate()
    {
        Skill::LateUpdate();
    }

    void SkillMMultiFire::Render()
    {
        Skill::Render();
    }
}
