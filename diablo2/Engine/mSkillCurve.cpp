#include "mSkillCurve.h"

#include "mStraightScript.h"

namespace m
{
	SkillCurve::SkillCurve(eSkillType type, Vector3 iniPos, float speed)
		: Skill(type, iniPos, false, true)
		, mOriginDegree(0.f)
		, mAddCurve(5.f)
		, macc(0.f)
	    , bLock(false)
	    , iLockCount(0)
    {
		bMadePath = true;


		SetSpeed(speed);
		SET_MESH(this, L"RectMesh");
		SET_MATERIAL(this, L"AnimationMaterial");
		SET_SCALE_XYZ(this, skillSizes[(int)type].x, skillSizes[(int)type].y, 1.f);
		ADD_COMP(this, Animator);

		ss = AddComponent<StraightScript>(skillAnimDirections[(int)type]);
		if (skillAnimDirections[(int)type] == 16)
		{
			rangeCollider->SetSize(Vector3(0.5f, 0.5f, 1.f));
			bSixteenDirection = false;
		}
		else
			bSixteenDirection = true;
		
    }

    SkillCurve::~SkillCurve()
    {
    }

    void SkillCurve::Initialize()
    {
        Skill::Initialize();
    }

    void SkillCurve::Update()
    {
        Skill::Update();
        moveCurve();
    }

    void SkillCurve::LateUpdate()
    {
		Skill::LateUpdate();
    }

    void SkillCurve::Render()
    {
		Skill::Render();
    }
    void SkillCurve::moveCurve()
    {
        Vector3 curPosition = GET_POS(this);
	
		if (bSkillFire)
		{
			ss->SkillFire();
			bSkillFire = false;
			bMove = true;

			prevPosition = GET_POS(this);

			vDirection = destPosition - prevPosition;
			mOriginDegree = RadianToDegree(atan2(vDirection.y, vDirection.x));

			vDirection.Normalize();
		}

		macc += Time::fDeltaTime();
		if(math::areAlmostEqual(macc, 0.2f, 0.1f) && !bLock)
		{
			++iLockCount;
			if(iLockCount >= 5) bLock = true;
			
			mOriginDegree -= mAddCurve;

			vDirection.x += cosf(DegreeToRadian(mOriginDegree));
			vDirection.y += sinf(DegreeToRadian(mOriginDegree));

			vDirection.Normalize();
		}
		
		if (bMove)
		{
			float fMoveX = curPosition.x + (vDirection.x * fXAdjustSpeed * Time::fDeltaTime());
			float fMoveY = curPosition.y + (vDirection.y * fYAdjustSpeed * Time::fDeltaTime());

			SET_POS_XYZ(this, fMoveX, fMoveY, curPosition.z);
		}
    }
}
