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

		const std::vector<GameObject*>& lefts 
			= activeScene->GetLayer(left).GetGameObjects();

		const std::vector<GameObject*>& rights 
			= activeScene->GetLayer(right).GetGameObjects();

		for (GameObject* leftObj : lefts)
		{
			Collider2D* leftCol = leftObj->GetComponent<Collider2D>();
			if (nullptr == leftCol) continue;
			if (leftObj->GetState() != GameObject::Active) continue;

			for (GameObject* rightObj : rights)
			{
				Collider2D* rightCol = rightObj->GetComponent<Collider2D>();
				if (nullptr == rightCol) continue;
				if (leftObj == rightObj) continue;
				if (rightObj->GetState() != GameObject::Active) continue;

				ColliderCollision(leftCol, rightCol);
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
			if(iter->second == true) 
			{
				left->OnCollisionExit(right);
				right->OnCollisionExit(left);
			}

			iter->second = false;
		}
	}
	bool CollisionManager::Intersect(Collider2D* left, Collider2D* right)
	{
		Vector3 leftScale = left->GetScale();
		Vector3 rightScale = right->GetScale();

		Vector3 leftPos = left->GetPosition();
		Vector3 rightPos = right->GetPosition();

		Vector3 leftSize = left->GetSize();
		Vector3 rightSize = right->GetSize();

		Vector3 leftRotation = left->GetRotation();
		Vector3 rightRotation = right->GetRotation();

		// rect intersect
		if (left->GetType() == eColliderType::Rect
			&& right->GetType() == eColliderType::Rect)
		{
			if (leftRotation != Vector3::Zero
				|| rightRotation != Vector3::Zero)
			{
				//Transform* leftTr = left->GetOwner()->GetComponent<Transform>();
				//Transform* rightTr = right->GetOwner()->GetComponent<Transform>();

				//std::vector<Vertex> leftVertexes =
				//	left->GetOwner()->GetComponent<MeshRenderer>()->GetMesh()->GetVertexes();
				//std::vector<Vertex> rightVertexes =
				//	right->GetOwner()->GetComponent<MeshRenderer>()->GetMesh()->GetVertexes();

				//Matrix leftScaleMatrix = Matrix::CreateScale(leftSize);
				//Matrix rightScaleMatrix = Matrix::CreateScale(rightSize);

				//Matrix leftMatrix = leftTr->GetWorld() * leftScaleMatrix;
				//Matrix rightMatrix = rightTr->GetWorld() * rightScaleMatrix;

				//Vector3 axises[4] = {};

				//axises[0] = Vector3::Transform(leftVertexes[1].pos, leftMatrix); // x
				//axises[0] -= Vector3::Transform(leftVertexes[0].pos, leftMatrix);

				//axises[1] = Vector3::Transform(leftVertexes[3].pos, leftMatrix); // y
				//axises[1] -= Vector3::Transform(leftVertexes[0].pos, leftMatrix);

				//axises[2] = Vector3::Transform(rightVertexes[1].pos, rightMatrix); // x
				//axises[2] -= Vector3::Transform(rightVertexes[0].pos, rightMatrix);

				//axises[3] = Vector3::Transform(rightVertexes[3].pos, rightMatrix); // y
				//axises[3] -= Vector3::Transform(rightVertexes[0].pos, rightMatrix);

				//Vector3 vDistance = leftPos - rightPos;
				//vDistance.z = leftVertexes[0].pos.z;

				//for (int i = 0; i < 4; ++i)
				//{
				//	Vector3 axis = axises[i];
				//	float sum = 0.f;
				//	for (int j = 0; j < 4; ++j)
				//		// vDistance가 위치의 중앙끼리에서 뺀 값으로
				//		// 전체 길이가 아닌 반으로 계산
				//		sum += fabs(axis.Dot(axises[j]) * 0.5f);

				//	if (sum < fabs(axis.Dot(vDistance)))
				//		return false;
				//}
				//return true;

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

				Vector3 axises[15];

				// leftMatrix의 축
				axises[0] = Vector3(leftMatrix._11, leftMatrix._12, leftMatrix._13);
				axises[1] = Vector3(leftMatrix._21, leftMatrix._22, leftMatrix._23);
				axises[2] = Vector3(leftMatrix._31, leftMatrix._32, leftMatrix._33);

				// rightMatrix의 축
				axises[3] = Vector3(rightMatrix._11, rightMatrix._12, rightMatrix._13);
				axises[4] = Vector3(rightMatrix._21, rightMatrix._22, rightMatrix._23);
				axises[5] = Vector3(rightMatrix._31, rightMatrix._32, rightMatrix._33);

				// cross product를 사용하여 추가 축 계산
				axises[6] = axises[0].Cross(axises[0]);
				axises[7] = axises[0].Cross(axises[0]);
				axises[8] = axises[0].Cross(axises[0]);
				axises[9] = axises[1].Cross(axises[1]);
				axises[10] = axises[1].Cross(axises[1]);
				axises[11] = axises[1].Cross(axises[1]);
				axises[12] = axises[2].Cross(axises[2]);
				axises[13] = axises[2].Cross(axises[2]);
				axises[14] = axises[2].Cross(axises[2]);

				// 축 정규화
				for (int i = 0; i < 15; ++i)
				{
					axises[i].Normalize();
				}

				// 충돌 감지 축 투영
				for (int i = 0; i < 15; ++i)
				{
					// left OBB 투영
					float leftMin = FLT_MAX;
					float leftMax = -FLT_MAX;
					for (const Vertex& vertex : leftVertexes)
					{
						float projection = vertex.pos.Dot(axises[i]);
						leftMin = min(leftMin, projection);
						leftMax = max(leftMax, projection);
					}

					// right OBB 투영
					float rightMin = FLT_MAX;
					float rightMax = -FLT_MAX;
					for (const Vertex& vertex : rightVertexes)
					{
						float projection = vertex.pos.Dot(axises[i]);
						rightMin = min(rightMin, projection);
						rightMax = max(rightMax, projection);
					}

					// 축간 겹침 여부 확인
					if (leftMax < rightMin || rightMax < leftMin)
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
					&& fabs(leftPos.y - rightPos.y) < leftScale.y / 2.f+ rightScale.y /2.f)
				{
					return true;
				}
			}
			
		}


		// circle intersect
		if (left->GetType() == eColliderType::Circle
			&& right->GetType() == eColliderType::Circle)
		{
			float dX = leftPos.x - rightPos.x;
			float dY = leftPos.y - rightPos.y;

			float length = sqrt(dX * dX + dY * dY);

			if (leftScale.x / 2.f + rightScale.x / 2.f>= length)
				return true;
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