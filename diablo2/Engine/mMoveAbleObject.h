#pragma once
#include "../engine_source/mGameObject.h"
#include "../engine_source/mAstar.h"
namespace m
{
	class UVUI;
	class MoveAbleObject :
		public GameObject
	{
	public:
		MoveAbleObject(Vector3 iniPos
					   , float speed
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

		virtual void Hit(int damage) = 0;
		bool Stop() { return fSpeed == 0.0f ? true : false; }
		bool StopF() { return fRemainDistance < fStartDistance ? false : true; }
		float GetRemainDistance() { return fRemainDistance; }
		float GetStartDistance() { return fStartDistance; }

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

		void SetCoord(Vector2 coord) { mCoord = coord; }
		Vector2 GetCoord() { return mCoord; }

		Collider2D* GetTilePositionCollider() { return tilePositionCollider; }
		Collider2D* GetHitAreaCollider() { return hitAreaCollider; }
	protected:
		Collider2D* rangeCollider;
		Collider2D* tilePositionCollider;
		Collider2D* hitAreaCollider;

		Vector3 prevPosition;
		Vector3 destPosition;
		Vector3 vDirection;
		Vector3 vS;

		float fRemainDistance;
		float fStartDistance;
		float fSpeed;

		bool bGetHit;

		Astar* mAstar;

		Vector2 mCoord;
	};
}

