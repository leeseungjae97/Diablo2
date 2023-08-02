#include "mCollisionManager.h"
#include "mSceneManager.h"
#include "mMeshRenderer.h"

namespace m
{
	std::bitset<LAYER_MAX> CollisionManager::mMatrix[LAYER_MAX] = {};
	std::map<UINT64, bool> CollisionManager::mCollisionMap = {};

	void CollisionManager::Initialize()
	{

	}
	void CollisionManager::Update()
	{
		for (UINT col = 0; col < LAYER_MAX; ++col)
		{
			for (UINT row = 0; row < LAYER_MAX; ++row)
			{
				if (mMatrix[col][row] == true)
					LayerCollision((eLayerType)col, (eLayerType)row);
			}
		}
	}
	void CollisionManager::LayerCollision(eLayerType left, eLayerType right)
	{
		Scene* activeScene = SceneManager::GetActiveScene();

		const std::vector<GameObject*> lefts
			= activeScene->GetLayer(left).GetGameObjects();

		const std::vector<GameObject*> rights
			= activeScene->GetLayer(right).GetGameObjects();

		for (GameObject* leftObj : lefts)
		{
			//Collider2D* leftCol = leftObj->GetComponent<Collider2D>();
			//if (nullptr == leftCol) continue;
			if (leftObj->GetState() != GameObject::RenderUpdate) continue;
			const std::vector<Collider2D*> leftCols = leftObj->GetComponents<Collider2D>();
			if (!leftCols.empty())
			{
				for (Collider2D* leftCol : leftCols)
				{
					for (GameObject* rightObj : rights)
					{
						//Collider2D* rightCol = rightObj->GetComponent<Collider2D>();
						//if (nullptr == rightCol) continue;
						if (leftObj == rightObj) continue;
						if (rightObj->GetState() != GameObject::RenderUpdate) continue;
						const std::vector<Collider2D*> rightCols = rightObj->GetComponents<Collider2D>();
						if (!rightCols.empty())
						{
							for (Collider2D* rightCol : rightCols)
								ColliderCollision(leftCol, rightCol);
						}

					}
				}
			}

		}
	}
	void CollisionManager::ColliderCollision(Collider2D* left, Collider2D* right)
	{
		ColliderID id = {};
		id.left = left->GetColliderID();
		id.right = right->GetColliderID();

		std::map<UINT64, bool>::iterator iter
			= mCollisionMap.find(id.id);

		if (iter == mCollisionMap.end())
		{
			mCollisionMap.insert(std::make_pair(id.id, false));
			iter = mCollisionMap.find(id.id);
		}

		if (Intersect(left, right))
		{
			if (iter->second == false)
			{
				left->OnCollisionEnter(right);
				right->OnCollisionEnter(left);
			}
			else
			{
				left->OnCollisionStay(right);
				right->OnCollisionStay(left);
			}

			iter->second = true;
		}
		else
		{
			if (iter->second == true)
			{
				left->OnCollisionExit(right);
				right->OnCollisionExit(left);
			}

			iter->second = false;
		}
	}
	bool CollisionManager::Intersect(Collider2D* left, Collider2D* right)
	{
		eColliderType leftType = left->GetType();
		eColliderType rightType = right->GetType();
		if (leftType == eColliderType::Dot) leftType = eColliderType::Circle;
		if (rightType == eColliderType::Dot) rightType = eColliderType::Circle;

		Vector3 leftScale = left->GetScale();
		Vector3 rightScale = right->GetScale();

		Vector3 leftSize = left->GetSize();
		Vector3 rightSize = right->GetSize();

		Vector3 leftPos = left->GetPosition();
		Vector3 rightPos = right->GetPosition();

		Vector3 leftRotation = left->GetRotation();
		Vector3 rightRotation = right->GetRotation();

		// rect intersect
		if (leftType == eColliderType::Rect
			&& rightType == eColliderType::Rect)
		{
			if (leftRotation != Vector3::Zero
				|| rightRotation != Vector3::Zero)
			{
				std::vector<Vertex> leftVertexes =
					left->GetOwner()->GetComponent<MeshRenderer>()->GetMesh()->GetVertexes();
				std::vector<Vertex> rightVertexes =
					right->GetOwner()->GetComponent<MeshRenderer>()->GetMesh()->GetVertexes();

				Transform* leftTr = left->GetOwner()->GetComponent<Transform>();
				Transform* rightTr = right->GetOwner()->GetComponent<Transform>();

				Matrix leftScaleMatrix = Matrix::CreateScale(leftSize);
				Matrix rightScaleMatrix = Matrix::CreateScale(rightSize);

				Matrix leftMatrix = leftTr->GetWorld() * leftScaleMatrix;
				Matrix rightMatrix = rightTr->GetWorld() * rightScaleMatrix;

				std::vector<Vector3> axes;

				// leftMatrix의 축
				axes.push_back(Vector3(leftMatrix.m[0][0], leftMatrix.m[0][1], leftMatrix.m[0][2]));
				axes.push_back(Vector3(leftMatrix.m[1][0], leftMatrix.m[1][1], leftMatrix.m[1][2]));
				//axes.push_back(Vector3(leftMatrix.m[2][0], leftMatrix.m[2][1], leftMatrix.m[2][2]));

				// rightMatrix의 축
				axes.push_back(Vector3(rightMatrix.m[0][0], rightMatrix.m[0][1], rightMatrix.m[0][2]));
				axes.push_back(Vector3(rightMatrix.m[1][0], rightMatrix.m[1][1], rightMatrix.m[1][2]));
				//axes.push_back(Vector3(rightMatrix.m[2][0], rightMatrix.m[2][1], rightMatrix.m[2][2]));

				// 0 ~ 2 : left, 3 ~ 5 : right
				// cross product를 사용하여 추가 축 계산
				//axes.push_back(axes[0].Cross(axes[3]));
				//axes.push_back(axes[0].Cross(axes[4]));
				//axes.push_back(axes[0].Cross(axes[5]));
				//axes.push_back(axes[1].Cross(axes[3]));
				//axes.push_back(axes[1].Cross(axes[4]));
				//axes.push_back(axes[1].Cross(axes[5]));
				//axes.push_back(axes[2].Cross(axes[3]));
				//axes.push_back(axes[2].Cross(axes[4]));
				//axes.push_back(axes[2].Cross(axes[5]));

				// 축 정규화
				for (Vector3 axis : axes)
				{
					axis.Normalize();
				}

				// 충돌 감지 축 투영
				for (const Vector3& axis : axes)
				{
					// left OBB 투영
					float leftMin = FLT_MAX;
					float leftMax = -FLT_MAX;
					for (const Vertex& vertex : leftVertexes)
					{
						Vector3 worldpos = Vector3::Transform(vertex.pos, leftMatrix);

						float projection = worldpos.Dot(axis);
						leftMin = min(leftMin, projection);
						leftMax = max(leftMax, projection);
					}

					// right OBB 투영
					float rightMin = FLT_MAX;
					float rightMax = -FLT_MAX;
					for (const Vertex& vertex : rightVertexes)
					{
						Vector3 worldPos = Vector3::Transform(vertex.pos, rightMatrix);
						float projection = worldPos.Dot(axis);
						rightMin = min(rightMin, projection);
						rightMax = max(rightMax, projection);
					}

					// 축간 겹침 여부 확인
					if (rightMin - leftMax > 0 || leftMin - rightMax > 0)
					{
						// 축이 분리되어 충돌이 없음
						return false;
					}
				}
				// 모든 축에서 겹침이 있음
				return true;
			}
			else
			{
				if (fabs(leftPos.x - rightPos.x) < leftScale.x / 2.f + rightScale.x / 2.f
					&& fabs(leftPos.y - rightPos.y) < leftScale.y / 2.f + rightScale.y / 2.f)
				{
					return true;
				}
				return false;
			}
		}


		// circle intersect
		if (leftType == eColliderType::Circle
			&& rightType == eColliderType::Circle)
		{
			float dX = leftPos.x - rightPos.x;
			float dY = leftPos.y - rightPos.y;

			float length = sqrt(dX * dX + dY * dY);

			if (leftScale.x / 2.f + rightScale.x / 2.f >= length)
				return true;
		}

		if (leftType == eColliderType::Circle
			&& rightType == eColliderType::Rect)
		{
			Vector2 corner[4] = {
				Vector2(rightPos.x - rightScale.x / 2.f, rightPos.y + rightScale.y / 2.f),
				Vector2(rightPos.x + rightScale.x / 2.f, rightPos.y + rightScale.y / 2.f),
				Vector2(rightPos.x - rightScale.x / 2.f, rightPos.y - rightScale.y / 2.f),
				Vector2(rightPos.x + rightScale.x / 2.f, rightPos.y - rightScale.y / 2.f),
			};
			for (int i = 0; i < 4; ++i)
			{
				float dX = leftPos.x - corner[i].x;
				float dY = leftPos.y - corner[i].y;

				float length = fabs(sqrt(dX * dX + dY * dY));

				if (fabs(leftScale.x / 2.f) > length)
					return true;
			}
			if (Vector2::PointIntersectRect(GET_VEC2_F_VEC3_D(rightPos),
				Vector2(rightScale.x + leftScale.x / 2.f, rightScale.y + leftScale.x / 2.f),
				GET_VEC2_F_VEC3_D(leftPos)))
			{
				return true;
			}
		}

		if (leftType == eColliderType::Rect
			&& rightType == eColliderType::Circle)
		{
			Vector2 corner[4] = {
				Vector2(leftPos.x - leftScale.x / 2.f, leftPos.y + leftScale.y / 2.f),
				Vector2(leftPos.x + leftScale.x / 2.f, leftPos.y + leftScale.y / 2.f),
				Vector2(leftPos.x - leftScale.x / 2.f, leftPos.y - leftScale.y / 2.f),
				Vector2(leftPos.x + leftScale.x / 2.f, leftPos.y - leftScale.y / 2.f),
			};
			for (int i = 0; i < 4; ++i)
			{
				float dX = rightPos.x - corner[i].x;
				float dY = rightPos.y - corner[i].y;

				float length = fabs(sqrt(dX * dX + dY * dY));

				if (fabs(rightScale.x / 2.f) > length)
					return true;
			}
			if (Vector2::PointIntersectRect(GET_VEC2_F_VEC3_D(leftPos),
				Vector2(leftScale.x + rightScale.x / 2.f, leftScale.x + rightScale.y / 2.f),
				GET_VEC2_F_VEC3_D(rightPos)))
			{
				return true;
			}
		}
		return false;
	}
	void CollisionManager::SetLayer(eLayerType left, eLayerType right, bool enable)
	{
		UINT row = -1;
		UINT col = -1;

		UINT iLeft = (UINT)left;
		UINT iRight = (UINT)right;

		if (iLeft <= iRight)
		{
			row = iLeft;
			col = iRight;
		}
		else
		{
			row = iRight;
			col = iLeft;
		}

		mMatrix[col][row] = enable;
	}
	void CollisionManager::Clear()
	{
		mMatrix->reset();
		mCollisionMap.clear();
	}
}