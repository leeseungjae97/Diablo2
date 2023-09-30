#pragma once
#include "../engine_source/mGameObject.h"
#include "..\engine_source\mPathFinder.h"
#include "../engine_source/MoveAbleObjectAnimLookUpTables.h"

namespace m
{
    class ShadowObject;
    class UVUI;
	class MoveAbleObject :
		public GameObject
	{
	public:
		MoveAbleObject(Vector3 iniPos
					   , float speed = 300.f
					   , bool useHitArea = true
					   , bool useRange = true
					   , bool useTilePos = true
					   , bool useAstar = true
		);
		virtual ~MoveAbleObject();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void Hit(int damage, bool attackStun = true) = 0;
		bool Stop() { return fSpeed == 0.0f ? true : false; }
		bool StopF() { return fRemainDistance < fStartDistance ? false : true; }
		float GetRemainDistance() { return fRemainDistance; }
		float GetStartDistance() { return fStartDistance; }

		void SetInitializePosition(Vector3 initPos);

		void SetRemainDistance(float rd) { fRemainDistance = rd; }
		void SetStartDistance(float sd) { fStartDistance = sd; }

		Collider2D* GetRangeCollider() { return rangeCollider; }

		Vector3 GetPrevPosition() { return prevPosition; }
		Vector3 GetDestPosition() { return destPosition; }
		Vector3 GetDirection() { return vDirection; }

		void SetDestPosition(Vector3 dest) { destPosition = dest; }
		void SetPrevPosition(Vector3 prevPos) { prevPosition = prevPos; }
		void SetDirection(Vector3 direction) { vDirection = direction; }

		bool GetHit() { return bGetHit; }
		void SetHit(bool hit) { bGetHit = hit; }

		void SetSpeed(float speed) { fSpeed = speed; }
		float GetSpeed() { return fSpeed; }

		void SetNumericalAdjustmentSpeed(float speed, float time);
		float GetNumericalAdjustmentSpeed() { return fNumericalAdjustmentSpeed; }

		void SetCoord(Vector2 coord) { mCoord = coord; }
		Vector2 GetCoord() { return mCoord; }

		Collider2D* GetTilePositionCollider() { return tilePositionCollider; }
		Collider2D* GetHitAreaCollider() { return bodyBoxCollider; }

		void SetMadePath(bool madePath) { bMadePath = madePath; }
		void SetSixteenDirection(bool sixteenDirection) { bSixteenDirection = sixteenDirection; }

		void Addiction(int damage, float addictionTime, int tickCount);
		bool GetAddiction() { return bAddiction; }

		void Stun(float second);
		bool GetStun() { return bStun; }

		void SetAdjustmentDegree();
		void AdDegree() { bAdjustmentDegree = false; }

		virtual void TimeWaitAttack();
		virtual void AttackedAddition();
	private:
		void damagedDelay();
		void addZWeight();

	protected:
		ShadowObject* mShadow;

		Collider2D* rangeCollider;
		Collider2D* tilePositionCollider;
		Collider2D* bodyBoxCollider;

		Vector3 prevPosition;
		Vector3 destPosition;
		Vector3 initPosition;
		Vector3 vDirection;
		Vector3 vS;

		float fRemainDistance;
		float fStartDistance;
		float fSpeed;
		float fXAdjustSpeed;
		float fYAdjustSpeed;

		float fNumericalAdjustmentSpeed;
		float fNASAcc;
		bool bCallSetNumericalAdjustmentSpeed;
		
		bool bGetHit;

		bool bMove;

		PathFinder* mPathFinder;

		Vector2 mCoord;

		bool bMadePath;
		bool bSixteenDirection;

		bool bCanDamaged;
		float fCanDamagedDelay;

		bool bStun;
		float fAccStun;
		float fStunSecond;

		float fAccAddiction;
		bool bAddiction;
		float fAddictionTime;
		int fAddictionTickCount;
		int fAccDamage;
		int iAddictionDamage;

		bool bAdjustmentDegree;
	};
}

