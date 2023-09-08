#include "mSkillCurve.h"

#include "mStraightScript.h"

namespace m
{
	SkillCurve::SkillCurve(eSkillType type, Vector3 iniPos, float speed)
		: Skill(type, iniPos, false, true)
		, mCurveDegree(0.f)
		, mCurveDistance(0.f)
		, mAccCurveTheta(0.f)
		, macc(0.f)
    {
		bMadePath = true;


		SetSpeed(speed);
		SET_MESH(this, L"RectMesh");
		SET_MATERIAL(this, L"AnimationMaterial");
		SET_SCALE_XYZ(this, skillSizes[(int)type].x, skillSizes[(int)type].y, 1.f);
		ADD_COMP(this, Animator);

		if (type >= eSkillType::DiabloLightning)
		{
			ss = AddComponent<StraightScript>(8);
			rangeCollider->SetSize(Vector3(0.5f, 0.5f, 1.f));
			bSixteenDirection = false;
		}
		else
		{
			ss = AddComponent<StraightScript>();
			bSixteenDirection = true;
		}
		mCurveDegree = 0.f;
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
	Vector2 SkillCurve::bezierInterpolate(Vector2 p0, Vector2 p1, Vector2 p2, float t)
	{
		float u = 1.0f - t;
		float tt = t * t;
		float uu = u * u;

		Vector2 p = uu * p0 + (2 * u * t) * p1 + tt * p2;
		return p;
	}
    void SkillCurve::moveCurve()
    {
        Vector3 curPosition = GET_POS(this);
	
		if (bSkillFire)
		{
			bSkillFire = false;
			bMove = true;

			prevPosition = GET_POS(this);

			vDirection = destPosition - prevPosition;
			vDirection.Normalize();
		}
		
		macc += Time::fDeltaTime();
		if(macc > 1.f)
		{
			mCurveDegree += 20.f;
			macc = 0.f;
			float theta = DegreeToRadian(mCurveDegree);
			XMVECTOR rotationQuaternion = XMQuaternionRotationAxis(XMVectorSet(0, 1, 0, 0), theta);
			vDirection = XMVector3Rotate(vDirection, rotationQuaternion);
		}
		
		if (bMove)
		{
			//float fMoveX = curPosition.x + (vDirection.x * sinf(mAccCurveTheta) * fAdjustSpeed * Time::fDeltaTime());
			//float fMoveY = curPosition.y + (vDirection.y * cosf(mAccCurveTheta) * fAdjustSpeed * Time::fDeltaTime());

			float fMoveX = curPosition.x + (vDirection.x * fAdjustSpeed * Time::fDeltaTime());
			float fMoveY = curPosition.y + (vDirection.y * fAdjustSpeed * Time::fDeltaTime());

			//float fMoveX = mp.x + (fAdjustSpeed * Time::fDeltaTime());
			//float fMoveY = mp.y + (fAdjustSpeed * Time::fDeltaTime());


			SET_POS_XYZ(this, fMoveX, fMoveY, curPosition.z);
		}
    }
}
