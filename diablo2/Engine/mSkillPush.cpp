#include "mSkillPush.h"

#include "../engine_source/mMonsterManager.h"
#include "../engine_source/mMouseManager.h"

namespace m
{
    void SkillPush::Push(Vector3 initPos, Camera* camera)
    {
        const int monsterId = MouseManager::GetMouseOnMonsterId();
        if (monsterId == -1)
        {
            return;
        }

        Monster* monster = MonsterManager::GetMonster(monsterId);
        if (nullptr == monster) return;

        Vector3 unprojMousePos = MouseManager::UnprojectionMousePos(initPos.z, camera);
        unprojMousePos.z = initPos.z;

        Vector3 vDirection;
        vDirection = unprojMousePos - initPos;
        vDirection.Normalize();

        Vector3 monsterPos = GET_POS(monster);
        float addX = 20.f;
        float addY = 20.f;
        if (vDirection.x < 0.f) addX *= -1.f;
        if (vDirection.y < 0.f)addY *= -1.f;
        monsterPos.x += addX;
        monsterPos.y += addY;
        SET_POS_VEC(monster, monsterPos);

        monster->Hit(10.f);
    }
}
