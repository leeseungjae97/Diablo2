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
		Vector3 leftHalfScale = left->GetScale() / 2.f;
		Vector3 rightHalfScale = right->GetScale() / 2.f;

		Vector3 leftPos = left->GetPosition();
		Vector3 rightPos = right->GetPosition();

		Vector3 leftScale = left->GetSize();
		Vector3 rightScale = right->GetSize();

		Vector3 leftRotation = left->GetRotation();
		Vector3 rightRotation = right->GetRotation();

		// rect intersect
		if (left->GetType() == eColliderType::Rect
			&& right->GetType() == eColliderType::Rect)
		{
			if (leftRotation != Vector3::Zero
				|| rightRotation != Vector3::Zero)
			{
				std::vector<Vertex> leftVertexes =
					left->GetOwner()->GetComponent<MeshRenderer>()->GetMesh()->GetVertexes();
				std::vector<Vertex> rightVertexes =
					right->GetOwner()->GetComponent<MeshRenderer>()->GetMesh()->GetVertexes();

				//Vector3 arrLocalPos[4] =
				//{
				//   Vector3{-0.5f, 0.5f, 0.0f}
				//   ,Vector3{0.5f, 0.5f, 0.0f}
				//   ,Vector3{0.5f, -0.5f, 0.0f}
				//   ,Vector3{-0.5f, -0.5f, 0.0f}
				//};

				Transform* leftTr = left->GetOwner()->GetComponent<Transform>();
				Transform* rightTr = right->GetOwner()->GetComponent<Transform>();

				Matrix leftScaleMatrix = Matrix::CreateScale(leftScale);
				Matrix rightScaleMatrix = Matrix::CreateScale(rightScale);

				Matrix leftMatrix = leftTr->GetWorld() * leftScaleMatrix;
				Matrix rightMatrix = rightTr->GetWorld() * rightScaleMatrix;

				//Vector3 Axis[4] = {};
				Vector3 leftAxis[2] = {};
				Vector3 rightAxis[2] = {};

				leftAxis[0] = Vector3::Transform(leftVertexes[1].pos, leftMatrix);
				//leftAxis[0] = Vector3(leftAxis[0].x, leftAxis[0].y, 0.0f);
				leftAxis[0] -= Vector3::Transform(leftVertexes[0].pos, leftMatrix);

				leftAxis[1] = Vector3::Transform(leftVertexes[3].pos, leftMatrix);
				//leftAxis[1] = Vector3(leftAxis[1].x, leftAxis[1].y, 0.0f);
				leftAxis[1] -= Vector3::Transform(leftVertexes[0].pos, leftMatrix);

				rightAxis[0] = Vector3::Transform(rightVertexes[1].pos, rightMatrix);
				//rightAxis[0] = Vector3(rightAxis[0].x, rightAxis[0].y, rightAxis[0].z);
				rightAxis[0] -= Vector3::Transform(rightVertexes[0].pos, rightMatrix);

				rightAxis[1] = Vector3::Transform(rightVertexes[3].pos, rightMatrix);
				//rightAxis[1] = Vector3(rightAxis[1].x, rightAxis[1].y, 0.0f);
				rightAxis[1] -= Vector3::Transform(rightVertexes[0].pos, rightMatrix);


				Vector3 vDistance = leftTr->GetPosition() - rightTr->GetPosition();
				vDistance.z = 0.0f;

				for (int i = 0; i < 2; i++)
				{
					Vector3 leftTransVertex = leftAxis[i];
					Vector3 rightTransVertex = rightAxis[i];

					float leftDist = 0.0f;
					float rightDist = 0.0f;
					for (int j = 0; j < 2; j++)
					{
						leftDist += fabs(leftAxis[j].Dot(leftTransVertex));
						rightDist += fabs(rightAxis[j].Dot(rightTransVertex));
					}

					if (leftDist + rightDist < fabs(vDistance.Dot(leftTransVertex))
						|| leftDist + rightDist < fabs(vDistance.Dot(rightTransVertex)))
						return false;
				}
				return true;
				/*leftPos *= leftRotation;
				rightPos *= rightRotation;

				std::vector<Vector2> vertex1;
				vertex1.resize(4);

				vertex1[0] = { leftPos.x, leftPos.y };
				vertex1[1] = { leftPos.x + leftScale.x, leftPos.y };
				vertex1[2] = { leftPos.x + leftScale.x, leftPos.y - leftScale.y };
				vertex1[3] = { leftPos.x, leftPos.y - leftScale.y };

				std::vector<Vector2> vertex2;
				vertex2.resize(4);
				vertex2[0] = { rightPos.x, rightPos.y };
				vertex2[1] = { rightPos.x + rightScale.x, rightPos.y };
				vertex2[2] = { rightPos.x + rightScale.x, rightPos.y - rightScale.y };
				vertex2[3] = { rightPos.x, rightPos.y - rightScale.y };

				Vector2 vOffset = { leftPos.x - rightPos.x, leftPos.y - rightPos.y };


				for (int i = 0; i < vertex1.size(); ++i)
				{

					Vector2 _axis = axisP(vertex1, i);

					MinMax _p1 = loop(_axis, vertex1);
					MinMax _p2 = loop(_axis, vertex2);

					float fOffset = _axis.Dot(vOffset);

					_p1.min += fOffset;
					_p1.max += fOffset;

					if (_p1.min - _p2.max > 0 || _p2.min - _p1.max > 0)
					{
						return false;
					}
				}
				return true;*/
			}
			else
			{
				if (fabs(leftPos.x - rightPos.x) < leftHalfScale.x + rightHalfScale.x
					&& fabs(leftPos.y - rightPos.y) < leftHalfScale.y + rightHalfScale.y)
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

			if (leftHalfScale.x + rightHalfScale.x >= length)
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